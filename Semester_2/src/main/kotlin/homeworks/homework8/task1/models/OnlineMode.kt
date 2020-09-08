package homeworks.homework8.task1.models

import homeworks.homework8.task1.TicTacToeApp.Companion.SECOND_PLAYER_SIGN
import io.ktor.client.HttpClient
import io.ktor.client.features.websocket.WebSockets
import io.ktor.client.features.websocket.ws
import io.ktor.http.HttpMethod
import io.ktor.http.cio.websocket.Frame
import io.ktor.http.cio.websocket.WebSocketSession
import io.ktor.http.cio.websocket.close
import io.ktor.http.cio.websocket.readText
import io.ktor.util.KtorExperimentalAPI
import javafx.application.Platform
import kotlinx.coroutines.isActive
import kotlinx.coroutines.runBlocking
import java.util.concurrent.atomic.AtomicBoolean

class OnlineMode(private val gameModel: GameModel) : Thread() {
    private companion object {
        const val SLEEP_TIME = 1000L
    }

    private val isNeededToSend = AtomicBoolean(false)
    private var moveToSend = ""
    private var isStarted = AtomicBoolean(false)
    private val isNeededToReceiveMove = AtomicBoolean(false)

    private fun waitBit() = sleep(SLEEP_TIME)

    fun sendMove(selectedRow: Int, selectedColumn: Int) {
        moveToSend = "$selectedRow:$selectedColumn"
        isNeededToSend.set(true)
    }

    private suspend fun sendMoveHandling(socket: WebSocketSession) {
        if (isNeededToSend.getAndSet(false)) {
            socket.send(Frame.Text(moveToSend))
            isNeededToReceiveMove.set(true)
            gameModel.isWaiting = true
        }
    }

    private fun receivedMoveHandling(move: String) {
        val move1 = move.split(":")
        Platform.runLater { gameModel.handleOnlineOpponentMove(move1[0].toInt(), move1[1].toInt()) }
    }

    suspend fun handleReceiveMessage(message: String, socket: WebSocketSession) {
        when {
            message == "start" -> onStart()
            message == "opponent left" -> {
                gameModel.isAbnormalOnlineTermination = true
                socket.close()
            }
            isStarted.get() -> {
                receivedMoveHandling(message)
                gameModel.isWaiting = false
                if (gameModel.winner != "") {
                    socket.close()
                }
            }
        }
    }

    private suspend fun getAndHandleReceivedMessage(socket: WebSocketSession) {
        if (isNeededToReceiveMove.getAndSet(false)) {
            when (val frame = socket.incoming.receive()) {
                is Frame.Text -> {
                    val message = frame.readText()
                    handleReceiveMessage(message, socket)
                }
            }
        }
    }

    private fun onStart() {
        isStarted.set(true)
        val isSecondPlayer = gameModel.playerSign == SECOND_PLAYER_SIGN
        gameModel.isWaiting = isSecondPlayer
        isNeededToReceiveMove.set(isSecondPlayer)
    }

    @KtorExperimentalAPI
    override fun run() {
        val client = HttpClient {
            install(WebSockets)
        }

        runBlocking {
            client.ws(method = HttpMethod.Get, port = 8080, host = "127.0.0.1", path = "/") {
                send(Frame.Text(gameModel.playerSign))
                when (val frame = incoming.receive()) {
                    is Frame.Text -> {
                        val text = frame.readText()
                        if (text == "start") {
                            onStart()
                        } else if (text == "wait") {
                            gameModel.isWaiting = true
                            isNeededToReceiveMove.set(true)
                        }
                    }
                }

                while (isActive) {
                    sendMoveHandling(this)
                    getAndHandleReceivedMessage(this)
                    waitBit()
                }
            }
        }
    }
}

package homeworks.homework8.task1

import io.ktor.application.Application
import io.ktor.application.call
import io.ktor.application.install
import io.ktor.http.cio.websocket.Frame
import io.ktor.http.cio.websocket.WebSocketSession
import io.ktor.http.cio.websocket.readText
import io.ktor.response.respondText
import io.ktor.routing.get
import io.ktor.routing.routing
import io.ktor.server.engine.embeddedServer
import io.ktor.server.netty.Netty
import io.ktor.util.KtorExperimentalAPI
import io.ktor.websocket.WebSockets
import io.ktor.websocket.webSocket
import java.util.Collections
import java.util.LinkedList
import java.util.concurrent.atomic.AtomicInteger

@ExperimentalStdlibApi
@KtorExperimentalAPI
fun main() {
    val server = embeddedServer(Netty, port = 8080) {
        mainModule()
    }
    server.start(wait = true)
}

private class Player(val session: WebSocketSession) {
    companion object {
        var lastId = AtomicInteger(0)
    }

    override fun toString() = "$name-$sign: $opponentName"

    private val id = lastId.getAndIncrement()
    var opponentName = ""
    var sign = ""
    val name: String
        get() = id.toString()
}

@ExperimentalStdlibApi
@KtorExperimentalAPI
private fun Application.mainModule() {

    install(WebSockets)
    routing {
        val players = Collections.synchronizedSet(LinkedHashSet<Player>())
        val playersWithOneSign = Collections.synchronizedList(LinkedList<Player>())
        get("/") {
            call.respondText("$players")
        }
        webSocket("/") {
            val player = Player(this)
            players += player
            when (val frame = incoming.receive()) {
                is Frame.Text -> {
                    player.sign = frame.readText()
                    if (playersWithOneSign.isEmpty() || playersWithOneSign[0].sign == player.sign) {
                        player.session.outgoing.send(Frame.Text("wait"))
                        playersWithOneSign.add(player)
                    } else {
                        val opponent = playersWithOneSign.removeFirst()
                        player.opponentName = opponent.name
                        opponent.opponentName = player.name
                        player.session.outgoing.send(Frame.Text("start"))
                        opponent.session.outgoing.send(Frame.Text("start"))
                    }
                }
            }

            try {
                while (true) {
                    var playerMove = ""
                    when (val frame = incoming.receive()) {
                        is Frame.Text -> {
                            playerMove = frame.readText()
                            players.find { it.name == player.opponentName }?.session?.outgoing?.send(
                                Frame.Text(playerMove)
                            )
                        }
                    }
                }
            } finally {
                players.find { it.name == player.opponentName }?.session?.outgoing?.send(Frame.Text("opponent left"))
                players -= player
            }
        }
    }
}

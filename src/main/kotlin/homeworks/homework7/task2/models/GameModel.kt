package homeworks.homework7.task2.models

import homeworks.homework7.task2.TicTacToeApp.Companion.FIELD_SIZE
import homeworks.homework7.task2.TicTacToeApp.Companion.SIGN_OF_ABSENCE
import homeworks.homework7.task2.TicTacToeApp.Companion.SECOND_PLAYER_SIGN
import homeworks.homework7.task2.TicTacToeApp.Companion.FIRST_PLAYER_SIGN
import homeworks.homework7.task2.bots.BotMoveHandler
import javafx.beans.property.SimpleBooleanProperty
import javafx.beans.property.SimpleStringProperty
import tornadofx.getValue
import tornadofx.setValue

class GameModel {
    private companion object {
        const val INITIAL_MOVE = FIRST_PLAYER_SIGN
        const val DEFAULT_OPPONENT = "friend"
    }

    var humanSign: String = FIRST_PLAYER_SIGN
    var botSign: String = SECOND_PLAYER_SIGN

    var opponent = DEFAULT_OPPONENT
        set(value) {
            if (value != "hardBot" &&
                value != "mediumBot" &&
                value != "easyBot" &&
                value != "friend"
            ) {
                throw IllegalStateException("Opponent is not defined")
            }
            field = value
        }

    private val botMoveHandler = BotMoveHandler()
    private val gameStateChecker = GameStateChecker()
    val field = MutableList(FIELD_SIZE) { MutableList(FIELD_SIZE) { SimpleStringProperty(SIGN_OF_ABSENCE) } }

    val isDrawProperty = SimpleBooleanProperty(false)
    var isDraw by isDrawProperty

    val winnerProperty = SimpleStringProperty(SIGN_OF_ABSENCE)
    var winner: String by winnerProperty

    val currentPlayerProperty = SimpleStringProperty(INITIAL_MOVE)
    private var currentPlayer: String by currentPlayerProperty

    fun setInitialState() {
        for (row in 0 until FIELD_SIZE) {
            for (column in 0 until FIELD_SIZE) {
                field[row][column].set(SIGN_OF_ABSENCE)
            }
        }
        currentPlayer = INITIAL_MOVE
        winner = SIGN_OF_ABSENCE
        isDraw = false
        if (opponent != "friend" && botSign == FIRST_PLAYER_SIGN) {
            handleBotMove()
        }
    }

    fun getAnotherPlayerSign(player: String): String {
        return if (player == FIRST_PLAYER_SIGN) {
            SECOND_PLAYER_SIGN
        } else {
            FIRST_PLAYER_SIGN
        }
    }

    fun handleHumanMove(selectedRow: Int, selectedColumn: Int) {
        handleMove(selectedRow, selectedColumn)
        if (opponent != "friend" && winner == SIGN_OF_ABSENCE) {
            handleBotMove()
        }
    }

    private fun handleBotMove() {
        val fieldWithString = field.map { it -> it.map { it.value }.toMutableList() }.toMutableList()
        val botMove = botMoveHandler.getMove(fieldWithString, botSign, humanSign, opponent)
        if (botMove == Pair(-1, -1)) {
            return
        }
        handleMove(botMove.first, botMove.second)
    }

    private fun handleMove(selectedRow: Int, selectedColumn: Int) {
        field[selectedRow][selectedColumn].set(currentPlayer)
        val fieldWithString = field.map { it -> it.map { it.value } }
        winner = gameStateChecker.getWinner(fieldWithString)
        if (winner == SIGN_OF_ABSENCE) {
            isDraw = gameStateChecker.isFieldFilled(fieldWithString)
            if (!isDraw) {
                currentPlayer = getAnotherPlayerSign(currentPlayer)
            }
        }
    }
}

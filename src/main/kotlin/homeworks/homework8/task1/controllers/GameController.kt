package homeworks.homework8.task1.controllers

import homeworks.homework8.task1.models.GameModel
import homeworks.homework8.task1.TicTacToeApp.Companion.SIGN_OF_ABSENCE
import javafx.beans.property.SimpleStringProperty
import tornadofx.Controller
import tornadofx.booleanBinding
import tornadofx.stringBinding

class GameController : Controller() {
    private val gameModel = GameModel()
    private val isWaiting = booleanBinding(gameModel.isWaitingProperty) { value }
    val endOfGameProperty = booleanBinding(gameModel.isDrawProperty, gameModel.winnerProperty) {
        gameModel.isDrawProperty.value || gameModel.winnerProperty.value != SIGN_OF_ABSENCE
    }

    val gameStatusProperty =
        stringBinding(
            gameModel.isDrawProperty,
            gameModel.winnerProperty,
            gameModel.currentPlayerProperty,
            gameModel.isAbnormalOnlineTerminationProperty
        ) {
            when {
                gameModel.isAbnormalOnlineTerminationProperty.value -> "Opponent left the game"
                gameModel.isDrawProperty.value -> "It's a draw!"
                gameModel.winnerProperty.value != SIGN_OF_ABSENCE -> {
                    when {
                        gameModel.opponent == "friend" -> "Player ${gameModel.winnerProperty.value} was win!"
                        gameModel.winner == gameModel.playerSign -> "You won!"
                        else -> "Opponent won"
                    }
                }
                gameModel.opponent == "friend" -> "Current player: ${gameModel.currentPlayerProperty.value}"
                else -> "Your sign: ${gameModel.playerSign}"
            }
        }

    fun setInitialState() {
        gameModel.setInitialState()
    }

    fun setPlayerSign(playerSign: String) {
        gameModel.playerSign = playerSign
        gameModel.opponentSign = gameModel.getAnotherPlayerSign(playerSign)
    }

    fun setOpponent(opponent: String) {
        gameModel.opponent = opponent
    }

    fun onButtonPressed(row: Int, column: Int) {
        gameModel.handleHumanMove(row, column)
    }

    val buttonsData = gameModel.field.map { it -> it.map { ButtonData(it) } }

    inner class ButtonData(valueOnButton: SimpleStringProperty) {
        val text = stringBinding(valueOnButton) { value }
        val isDisable = booleanBinding(valueOnButton, endOfGameProperty, isWaiting) {
            valueOnButton.value != SIGN_OF_ABSENCE || endOfGameProperty.value || isWaiting.value
        }
    }
}

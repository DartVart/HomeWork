package homeworks.homework7.task2.controllers

import homeworks.homework7.task2.models.GameModel
import homeworks.homework7.task2.TicTacToeApp.Companion.SIGN_OF_ABSENCE
import javafx.beans.property.SimpleStringProperty
import tornadofx.Controller
import tornadofx.booleanBinding
import tornadofx.stringBinding

class GameController : Controller() {
    private val gameModel = GameModel()
    val endOfGameProperty = booleanBinding(gameModel.isDrawProperty, gameModel.winnerProperty) {
        gameModel.isDrawProperty.value || gameModel.winnerProperty.value != SIGN_OF_ABSENCE
    }

    val gameStatusProperty =
        stringBinding(gameModel.isDrawProperty, gameModel.winnerProperty, gameModel.currentPlayerProperty) {
            when {
                gameModel.isDrawProperty.value -> "It's a draw!"
                gameModel.winnerProperty.value != SIGN_OF_ABSENCE -> {
                    when {
                        gameModel.opponent == "friend" -> "Player ${gameModel.winnerProperty.value} was win!"
                        gameModel.winner == gameModel.humanSign -> "You won!"
                        else -> "Bot won"
                    }
                }
                gameModel.opponent == "friend" -> "Current player: ${gameModel.currentPlayerProperty.value}"
                else -> "Your sign: ${gameModel.humanSign}"
            }
        }

    fun setInitialState() {
        gameModel.setInitialState()
    }

    fun setPlayerSign(humanSign: String) {
        gameModel.humanSign = humanSign
        gameModel.botSign = gameModel.getAnotherPlayerSign(humanSign)
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
        val isDisable = booleanBinding(valueOnButton, endOfGameProperty) {
            valueOnButton.value != SIGN_OF_ABSENCE || endOfGameProperty.value
        }
    }
}

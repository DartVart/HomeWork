package homeworks.homework7.task2.views

import homeworks.homework7.task2.TicTacToeApp.Companion.FIELD_SIZE
import homeworks.homework7.task2.controllers.GameController
import homeworks.homework7.task2.stylesheets.GameFieldStylesheet
import tornadofx.View
import tornadofx.vbox
import tornadofx.addClass
import tornadofx.button
import tornadofx.hbox
import tornadofx.onChange
import tornadofx.plusAssign
import tornadofx.action

class GameFieldView : View() {
    private val controller: GameController by inject()

    private fun renderButtonsRow(buttonsData: List<List<GameController.ButtonData>>, row: Int) = hbox {
        addClass(GameFieldStylesheet.buttonsRow)
        for (column in 0 until FIELD_SIZE) {
            this += button(buttonsData[row][column].text) {
                addClass(GameFieldStylesheet.gameButton)
                action {
                    controller.onButtonPressed(row, column)
                }
                isDisable = buttonsData[row][column].isDisable.value
                buttonsData[row][column].isDisable.onChange {
                    isDisable = it
                }
            }
        }
    }

    private fun renderButtons(buttonsData: List<List<GameController.ButtonData>>) = vbox {
        addClass(GameFieldStylesheet.buttonsColumn)
        for (row in 0 until FIELD_SIZE) {
            this += renderButtonsRow(buttonsData, row)
        }
    }

    override val root = renderButtons(controller.buttonsData)
}

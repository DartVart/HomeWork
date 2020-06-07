package homeworks.homework7.task2.views

import homeworks.homework7.task2.TicTacToeApp.Companion.SECOND_PLAYER_SIGN
import homeworks.homework7.task2.TicTacToeApp.Companion.FIRST_PLAYER_SIGN
import homeworks.homework7.task2.controllers.GameController
import homeworks.homework7.task2.stylesheets.MenuStylesheet
import tornadofx.View
import tornadofx.vbox
import tornadofx.addClass
import tornadofx.button
import tornadofx.label
import tornadofx.action

class SignSelectionMenu : View("Sign selection") {
    private val controller: GameController by inject()
    override val root = vbox {
        addClass(MenuStylesheet.mainVbox)
        label("Choose the sign you'll play with") { addClass(MenuStylesheet.descriptionLabel) }
        label("(\"$FIRST_PLAYER_SIGN\" starts the game)") { addClass(MenuStylesheet.smallDescriptionLabel) }
        button(FIRST_PLAYER_SIGN) {
            action {
                replaceWithGameView(FIRST_PLAYER_SIGN)
            }
        }
        button(SECOND_PLAYER_SIGN) {
            action {
                replaceWithGameView(SECOND_PLAYER_SIGN)
            }
        }
    }

    private fun replaceWithGameView(humanSign: String) {
        controller.setPlayerSign(humanSign)
        replaceWith<GameView>()
    }
}

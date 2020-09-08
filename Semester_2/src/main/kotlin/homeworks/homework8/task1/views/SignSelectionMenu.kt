package homeworks.homework8.task1.views

import homeworks.homework8.task1.TicTacToeApp.Companion.SECOND_PLAYER_SIGN
import homeworks.homework8.task1.TicTacToeApp.Companion.FIRST_PLAYER_SIGN
import homeworks.homework8.task1.controllers.GameController
import homeworks.homework8.task1.stylesheets.MenuStylesheet
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

    private fun replaceWithGameView(playerSign: String) {
        controller.setPlayerSign(playerSign)
        replaceWith<GameView>()
    }
}

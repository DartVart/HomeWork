package homeworks.homework8.task1.views

import homeworks.homework8.task1.controllers.GameController
import homeworks.homework8.task1.stylesheets.MenuStylesheet
import tornadofx.View
import tornadofx.vbox
import tornadofx.addClass
import tornadofx.button
import tornadofx.action
import tornadofx.label

class MainMenu : View("Menu") {
    private val controller: GameController by inject()
    override val root = vbox {
        addClass(MenuStylesheet.mainVbox)
        label("Tic Tac Toe") { addClass(MenuStylesheet.gameTitle) }
        button("Play with friend") {
            action {
                controller.setOpponent("friend")
                replaceWith<GameView>()
            }
        }

        button("Play with bot") {
            action {
                replaceWith<BotSelectionMenu>()
            }
        }

        button("Multiplayer") {
            action {
                controller.setOpponent("onlineOpponent")
                replaceWith<SignSelectionMenu>()
            }
        }
    }
}

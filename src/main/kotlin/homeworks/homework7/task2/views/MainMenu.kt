package homeworks.homework7.task2.views

import homeworks.homework7.task2.controllers.GameController
import homeworks.homework7.task2.stylesheets.MenuStylesheet
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
    }
}

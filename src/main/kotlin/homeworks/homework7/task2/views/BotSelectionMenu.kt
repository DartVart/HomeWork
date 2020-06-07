package homeworks.homework7.task2.views

import homeworks.homework7.task2.controllers.GameController
import homeworks.homework7.task2.stylesheets.MenuStylesheet
import tornadofx.View
import tornadofx.vbox
import tornadofx.addClass
import tornadofx.button
import tornadofx.label
import tornadofx.action

class BotSelectionMenu : View("Bot selection") {
    private val controller: GameController by inject()
    override val root = vbox {
        addClass(MenuStylesheet.mainVbox)
        label("Select bot level") { addClass(MenuStylesheet.descriptionLabel) }
        button("Easy") {
            action {
                replaceWithSignSelectionMenu("easyBot")
            }
        }

        button("Medium") {
            action {
                replaceWithSignSelectionMenu("mediumBot")
            }
        }

        button("Hard") {
            action {
                replaceWithSignSelectionMenu("hardBot")
            }
        }
    }

    private fun replaceWithSignSelectionMenu(botType: String) {
        controller.setOpponent(botType)
        replaceWith<SignSelectionMenu>()
    }
}

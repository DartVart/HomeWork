package homeworks.homework8.task1

import homeworks.homework8.task1.stylesheets.GameFieldStylesheet
import homeworks.homework8.task1.stylesheets.MenuStylesheet
import homeworks.homework8.task1.views.MainMenu
import javafx.stage.Stage
import tornadofx.App
import tornadofx.launch

class TicTacToeApp : App(MainMenu::class, MenuStylesheet::class, GameFieldStylesheet::class) {
    companion object {
        const val FIELD_SIZE = 3
        const val APP_HEIGHT = 450.0
        const val APP_WIDTH = 450.0
        const val SIGN_OF_ABSENCE = ""
        const val FIRST_PLAYER_SIGN = "O"
        const val SECOND_PLAYER_SIGN = "X"
    }

    override fun start(stage: Stage) {
        stage.width = APP_WIDTH
        stage.height = APP_HEIGHT
        stage.isResizable = false
        super.start(stage)
    }
}

fun main() {
    launch<TicTacToeApp>()
}

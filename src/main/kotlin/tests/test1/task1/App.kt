package homeworks.homework8.task1

import javafx.stage.Stage
import tornadofx.App
import tornadofx.launch
import tornadofx.Controller
import java.awt.MouseInfo
import tornadofx.View
import tornadofx.button
import tornadofx.hbox

private const val STAGE_HEIGHT = 400.0
private const val STAGE_WIDTH = 400.0

class ButtonApp : App(GameField::class) {
    override fun start(stage: Stage) {
        stage.height = STAGE_HEIGHT
        stage.width = STAGE_WIDTH
        stage.isResizable = false
        super.start(stage)
    }
}

class GameFieldController : Controller() {
    fun startGame() {
        while (true) {
            println("${MouseInfo.getPointerInfo().location.x}")
        }
    }
}

fun main() {
    launch<myApp>()
}

class GameField : View() {
    val controller: GameFieldController by inject()

    override fun onDock() {
        super.onDock()
        controller.startGame()
    }

    override val root = hbox {
        button("") {
            id = "simpleButton"
        }
    }
}

package homeworks.homework7.task2.stylesheets

import javafx.geometry.Pos
import javafx.scene.paint.Color
import javafx.scene.text.Font
import javafx.scene.text.FontWeight
import tornadofx.Stylesheet
import tornadofx.cssclass
import tornadofx.mm
import tornadofx.px

class GameFieldStylesheet : Stylesheet() {
    companion object {
        val statusTitle by cssclass()
        private const val GAME_TITLE_FONT_SIZE = 25.0
        private val LABEL_COLOR = Color.SALMON

        val backButton by cssclass()
        private const val BACK_BUTTON_FONT_SIZE = 15.0
        private val BACK_BUTTON_TEXT_COLOR = Color.WHITE
        private val BACK_BUTTON_BACKGROUND_COLOR = Color.SALMON

        val gameButton by cssclass()
        private const val GAME_BUTTON_FONT_SIZE = 30.0
        private val GAME_BUTTON_TEXT_COLOR = Color.GOLD
        private val GAME_BUTTON_BACKGROUND_COLOR = Color.GRAY
        private const val GAME_BUTTON_SIZE = 90.0

        val mainBox by cssclass()
        private const val MAIN_VBOX_SPACING = 5

        val buttonsRow by cssclass()
        private const val BUTTONS_ROW_SPACING = 1

        val buttonsColumn by cssclass()
        private const val BUTTONS_COLUMN_SPACING = 1
    }

    init {
        statusTitle {
            font = Font.font(GAME_TITLE_FONT_SIZE)
            textFill = LABEL_COLOR
            fontWeight = FontWeight.BOLD
        }

        mainBox {
            spacing = MAIN_VBOX_SPACING.mm
            alignment = Pos.CENTER
        }

        backButton {
            font = Font.font(BACK_BUTTON_FONT_SIZE)
            textFill = BACK_BUTTON_TEXT_COLOR
            backgroundColor += BACK_BUTTON_BACKGROUND_COLOR
        }

        gameButton {
            minWidth = GAME_BUTTON_SIZE.px
            minHeight = GAME_BUTTON_SIZE.px
            font = Font.font(GAME_BUTTON_FONT_SIZE)
            textFill = GAME_BUTTON_TEXT_COLOR
            backgroundColor += GAME_BUTTON_BACKGROUND_COLOR
        }

        buttonsRow {
            alignment = Pos.CENTER
            spacing = BUTTONS_ROW_SPACING.mm
        }

        buttonsColumn {
            alignment = Pos.CENTER
            spacing = BUTTONS_COLUMN_SPACING.mm
        }
    }
}

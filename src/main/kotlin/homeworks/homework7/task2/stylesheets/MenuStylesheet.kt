package homeworks.homework7.task2.stylesheets

import javafx.geometry.Pos
import javafx.scene.paint.Color
import javafx.scene.text.Font
import javafx.scene.text.FontWeight
import tornadofx.Stylesheet
import tornadofx.cssclass
import tornadofx.mm
import tornadofx.px

class MenuStylesheet : Stylesheet() {
    companion object {
        val gameTitle by cssclass()
        private const val GAME_TITLE_FONT_SIZE = 30.0

        val descriptionLabel by cssclass()
        private const val DESCRIPTION_LABEL_FONT_SIZE = 17.0

        val smallDescriptionLabel by cssclass()
        private const val SMALL_DESCRIPTION_LABEL_FONT_SIZE = 14.0

        private val LABEL_COLOR = Color.SALMON

        val button by cssclass()
        private const val BUTTON_FONT_SIZE = 15.0
        private const val BUTTON_WIDTH = 200.0
        private val BUTTON_TEXT_COLOR = Color.WHITE
        private val BUTTON_BACKGROUND_COLOR = Color.SALMON

        val mainVbox by cssclass()
        private const val MAIN_VBOX_SPACING = 5
    }

    init {
        gameTitle {
            font = Font.font(GAME_TITLE_FONT_SIZE)
        }

        descriptionLabel {
            font = Font.font(DESCRIPTION_LABEL_FONT_SIZE)
        }

        smallDescriptionLabel {
            font = Font.font(SMALL_DESCRIPTION_LABEL_FONT_SIZE)
        }

        mainVbox {
            label {
                textFill = LABEL_COLOR
                fontWeight = FontWeight.BOLD
            }
            spacing = MAIN_VBOX_SPACING.mm
            button {
                font = Font.font(BUTTON_FONT_SIZE)
                textFill = BUTTON_TEXT_COLOR
                backgroundColor += BUTTON_BACKGROUND_COLOR
                minWidth = BUTTON_WIDTH.px
            }
            alignment = Pos.CENTER
        }
    }
}

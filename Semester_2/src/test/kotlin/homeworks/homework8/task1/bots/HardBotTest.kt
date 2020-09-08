package homeworks.homework8.task1.bots

import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions.assertEquals

internal class HardBotTest {
    val hardBot = HardBot()

    @Nested
    inner class Check_getMove {
        @Test
        fun winningMove_row1_MustWork() {
            val field = mutableListOf(
                mutableListOf("X", "", "X"),
                mutableListOf("", "", ""),
                mutableListOf("", "O", "")
            )
            assertEquals(hardBot.getMove(field, "X", "O"), Pair(0, 1))
        }

        @Test
        fun winningMove_mainDiagonal_MustWork() {
            val field = mutableListOf(
                mutableListOf("", "", "O"),
                mutableListOf("", "X", ""),
                mutableListOf("", "O", "X")
            )
            assertEquals(hardBot.getMove(field, "X", "O"), Pair(0, 0))
        }

        @Test
        fun winningMove_secondDiagonal_MustWork() {
            val field = mutableListOf(
                mutableListOf("O", "X", "O"),
                mutableListOf("X", "", ""),
                mutableListOf("O", "", "X")
            )
            assertEquals(hardBot.getMove(field, "O", "X"), Pair(1, 1))
        }

        @Test
        fun winningMove_column1_MustWork() {
            val field = mutableListOf(
                mutableListOf("O", "", ""),
                mutableListOf("O", "", ""),
                mutableListOf("", "X", "X")
            )
            assertEquals(hardBot.getMove(field, "O", "X"), Pair(2, 0))
        }

        @Test
        fun doNotLetHumanWin_column2_MustWork() {
            val field = mutableListOf(
                mutableListOf("", "O", ""),
                mutableListOf("", "", "X"),
                mutableListOf("", "O", "")
            )
            assertEquals(hardBot.getMove(field, "X", "O"), Pair(1, 1))
        }

        @Test
        fun doNotLetHumanWin_column3_MustWork() {
            val field = mutableListOf(
                mutableListOf("", "", "O"),
                mutableListOf("", "X", ""),
                mutableListOf("", "", "O")
            )
            assertEquals(hardBot.getMove(field, "X", "O"), Pair(1, 2))
        }

        @Test
        fun doNotLetHumanWin_row2_MustWork() {
            val field = mutableListOf(
                mutableListOf("", "", ""),
                mutableListOf("O", "", "O"),
                mutableListOf("", "X", "")
            )
            assertEquals(hardBot.getMove(field, "X", "O"), Pair(1, 1))
        }

        @Test
        fun doNotLetHumanWin_row3_MustWork() {
            val field = mutableListOf(
                mutableListOf("", "X", ""),
                mutableListOf("", "", ""),
                mutableListOf("", "O", "O")
            )
            assertEquals(hardBot.getMove(field, "X", "O"), Pair(2, 0))
        }

        @Test
        fun doNotLetHumanWin_almostFilled_MustWork() {
            val field = mutableListOf(
                mutableListOf("X", "O", ""),
                mutableListOf("X", "", "O"),
                mutableListOf("O", "X", "O")
            )
            assertEquals(hardBot.getMove(field, "X", "O"), Pair(0, 2))
        }

        @Test
        fun winningMove_almostFilled_MustWork() {
            val field = mutableListOf(
                mutableListOf("O", "", "O"),
                mutableListOf("O", "O", "X"),
                mutableListOf("X", "", "X")
            )
            assertEquals(hardBot.getMove(field, "X", "O"), Pair(2, 1))
        }
    }
}

package homeworks.homework7.task2.models

import org.junit.jupiter.api.Test

import org.junit.jupiter.api.Assertions.*
import org.junit.jupiter.api.Nested

internal class GameStateCheckerTest {
    val gameStateChecker = GameStateChecker()

    @Nested
    inner class Check_getWinner {
        @Test
        fun emptyField_HasWinner_MustWork() {
            val field = listOf(
                listOf("", "", ""),
                listOf("", "", ""),
                listOf("", "", "")
            )
            assertEquals("", gameStateChecker.getWinner(field))
        }

        @Test
        fun mainDiagonal_HasWinner_MustWork() {
            val field = listOf(
                listOf("O", "X", ""),
                listOf("X", "O", ""),
                listOf("", "X", "O")
            )
            assertEquals("O", gameStateChecker.getWinner(field))
        }

        @Test
        fun secondDiagonal_HasWinner_MustWork() {
            val field = listOf(
                listOf("", "O", "X"),
                listOf("", "X", "O"),
                listOf("X", "O", "")
            )
            assertEquals("X", gameStateChecker.getWinner(field))
        }

        @Test
        fun row1_HasWinner_MustWork() {
            val field = listOf(
                listOf("X", "X", "X"),
                listOf("", "O", "O"),
                listOf("", "O", "")
            )
            assertEquals("X", gameStateChecker.getWinner(field))
        }

        @Test
        fun row2_HasWinner_MustWork() {
            val field = listOf(
                listOf("O", "", "O"),
                listOf("X", "X", "X"),
                listOf("", "O", "")
            )
            assertEquals("X", gameStateChecker.getWinner(field))
        }

        @Test
        fun row3_HasWinner_MustWork() {
            val field = listOf(
                listOf("", "O", ""),
                listOf("", "O", "O"),
                listOf("X", "X", "X")
            )
            assertEquals("X", gameStateChecker.getWinner(field))
        }

        @Test
        fun column1_HasWinner_MustWork() {
            val field = listOf(
                listOf("X", "", ""),
                listOf("X", "", "O"),
                listOf("X", "O", "O")
            )
            assertEquals("X", gameStateChecker.getWinner(field))
        }

        @Test
        fun column2_HasWinner_MustWork() {
            val field = listOf(
                listOf("", "O", ""),
                listOf("X", "O", "X"),
                listOf("", "O", "X")
            )
            assertEquals("O", gameStateChecker.getWinner(field))
        }

        @Test
        fun column3_HasWinner_MustWork() {
            val field = listOf(
                listOf("O", "", "X"),
                listOf("O", "", "X"),
                listOf("", "O", "X")
            )
            assertEquals("X", gameStateChecker.getWinner(field))
        }

        @Test
        fun oneFilledColumn_DoesNotHasWinner_MustWork() {
            val field = listOf(
                listOf("", "O", ""),
                listOf("", "O", ""),
                listOf("", "X", "")
            )
            assertEquals("", gameStateChecker.getWinner(field))
        }

        @Test
        fun oneFilledRow_DoesNotHasWinner_MustWork() {
            val field = listOf(
                listOf("", "", ""),
                listOf("O", "X", "O"),
                listOf("", "", "")
            )
            assertEquals("", gameStateChecker.getWinner(field))
        }

        @Test
        fun singleElement_DoesNotHasWinner_MustWork() {
            val field = listOf(
                listOf("", "", ""),
                listOf("", "X", ""),
                listOf("", "", "")
            )
            assertEquals("", gameStateChecker.getWinner(field))
        }

        @Test
        fun almostFilled1_DoesNotHasWinner_MustWork() {
            val field = listOf(
                listOf("O", "X", "O"),
                listOf("", "X", "O"),
                listOf("", "O", "X")
            )
            assertEquals("", gameStateChecker.getWinner(field))
        }

        @Test
        fun almostFilled2_DoesNotHasWinner_MustWork() {
            val field = listOf(
                listOf("", "O", "X"),
                listOf("O", "X", "O"),
                listOf("", "O", "X")
            )
            assertEquals("", gameStateChecker.getWinner(field))
        }

        @Test
        fun almostFilled3_DoesNotHasWinner_MustWork() {
            val field = listOf(
                listOf("O", "O", "X"),
                listOf("X", "", "O"),
                listOf("", "O", "X")
            )
            assertEquals("", gameStateChecker.getWinner(field))
        }
    }

    @Nested
    inner class Check_isFieldFilled {
        @Test
        fun notFilled1_MustWork() {
            val field = listOf(
                listOf("O", "O", "X"),
                listOf("X", "", "O"),
                listOf("", "O", "X")
            )
            assertFalse(gameStateChecker.isFieldFilled(field))
        }

        @Test
        fun emptyField_MustWork() {
            val field = listOf(
                listOf("", "", ""),
                listOf("", "", ""),
                listOf("", "", "")
            )
            assertFalse(gameStateChecker.isFieldFilled(field))
        }

        @Test
        fun filled_MustWork() {
            val field = listOf(
                listOf("O", "O", "X"),
                listOf("X", "O", "O"),
                listOf("O", "X", "X")
            )
            assertTrue(gameStateChecker.isFieldFilled(field))
        }
    }
}

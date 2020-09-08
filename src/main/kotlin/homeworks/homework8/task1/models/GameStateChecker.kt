package homeworks.homework8.task1.models

import homeworks.homework8.task1.TicTacToeApp.Companion.SIGN_OF_ABSENCE

class GameStateChecker {
    fun isFieldFilled(field: List<List<String>>): Boolean {
        for (row in 0..2) {
            for (column in 0..2) {
                if (field[row][column] == SIGN_OF_ABSENCE) {
                    return false
                }
            }
        }
        return true
    }

    /**
     * Returns the [SIGN_OF_ABSENCE] if there is no winner
     * */
    fun getWinner(field: List<List<String>>): String {
        var result = getWinnerFromColumns(field)
        if (result == SIGN_OF_ABSENCE) {
            result = getWinnerFromRows(field)
            if (result == SIGN_OF_ABSENCE) {
                return getWinnerFromDiagonals(field)
            }
        }
        return result
    }

    private fun isEqual(a: String, b: String, c: String) = a == b && b == c

    private fun getWinnerFromRows(field: List<List<String>>): String {
        for (row in 0..2) {
            if (isEqual(field[row][0], field[row][1], field[row][2]) && field[row][0] != SIGN_OF_ABSENCE) {
                return field[row][0]
            }
        }
        return SIGN_OF_ABSENCE
    }

    private fun getWinnerFromColumns(field: List<List<String>>): String {
        for (column in 0..2) {
            if (isEqual(
                    field[0][column],
                    field[1][column],
                    field[2][column]
                ) && field[0][column] != SIGN_OF_ABSENCE
            ) {
                return field[0][column]
            }
        }
        return SIGN_OF_ABSENCE
    }

    private fun getWinnerFromDiagonals(field: List<List<String>>): String {
        return when {
            (isEqual(field[0][0], field[1][1], field[2][2]) && field[0][0] != SIGN_OF_ABSENCE) -> {
                field[0][0]
            }
            (isEqual(field[0][2], field[1][1], field[2][0]) && field[0][2] != SIGN_OF_ABSENCE) -> {
                field[0][2]
            }
            else -> SIGN_OF_ABSENCE
        }
    }
}

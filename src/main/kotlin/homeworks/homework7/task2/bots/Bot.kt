package homeworks.homework7.task2.bots

import homeworks.homework7.task2.TicTacToeApp.Companion.FIELD_SIZE
import homeworks.homework7.task2.TicTacToeApp.Companion.SIGN_OF_ABSENCE

abstract class Bot {
    abstract fun getMove(field: MutableList<MutableList<String>>, botSign: String, humanSign: String): Pair<Int, Int>

    fun getFreePositions(field: List<List<String>>): List<Pair<Int, Int>> {
        val result = mutableListOf<Pair<Int, Int>>()
        for (row in 0 until FIELD_SIZE) {
            for (column in 0 until FIELD_SIZE) {
                if (field[row][column] == SIGN_OF_ABSENCE) {
                    result.add(Pair(row, column))
                }
            }
        }
        return result
    }
}

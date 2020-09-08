package homeworks.homework8.task1.bots

import homeworks.homework8.task1.models.GameStateChecker
import homeworks.homework8.task1.TicTacToeApp.Companion.SIGN_OF_ABSENCE

class HardBot : Bot() {
    private companion object {
        const val MIN_PIECE_OF_SCORE = 10
        const val MIN_SCORE = -1000
        const val MAX_SCORE = 1000
    }

    override fun getMove(field: MutableList<MutableList<String>>, botSign: String, humanSign: String): Pair<Int, Int> {
        var bestScore = MIN_SCORE
        var bestMove = Pair(-1, -1)
        var currentMoveScore: Int
        getFreePositions(field).forEach {
            field[it.first][it.second] = botSign
            currentMoveScore = minimax(field, false, botSign, humanSign)
            field[it.first][it.second] = SIGN_OF_ABSENCE
            if (bestScore < currentMoveScore) {
                bestMove = it
                bestScore = currentMoveScore
            }
        }
        return bestMove
    }

    private val gameStateChecker = GameStateChecker()

    private fun minimax(
        field: MutableList<MutableList<String>>,
        isBotMove: Boolean,
        botSign: String,
        humanSign: String
    ): Int {
        val winner = gameStateChecker.getWinner(field)
        return when {
            winner == botSign -> MIN_PIECE_OF_SCORE
            winner == humanSign -> -MIN_PIECE_OF_SCORE
            gameStateChecker.isFieldFilled(field) -> 0
            isBotMove -> getScoreWithBotMove(field, botSign, humanSign)
            else -> getScoreWithHumanMove(field, botSign, humanSign)
        }
    }

    private fun getScoreWithBotMove(field: MutableList<MutableList<String>>, botSign: String, humanSign: String): Int {
        var highestScore = MIN_SCORE
        var currentMoveScore: Int
        getFreePositions(field).forEach {
            field[it.first][it.second] = botSign
            currentMoveScore = minimax(field, false, botSign, humanSign)
            if (currentMoveScore > highestScore) {
                highestScore = currentMoveScore
            }
            field[it.first][it.second] = SIGN_OF_ABSENCE
        }
        return highestScore
    }

    private fun getScoreWithHumanMove(
        field: MutableList<MutableList<String>>,
        botSign: String,
        humanSign: String
    ): Int {
        var smallestScore = MAX_SCORE
        var currentMoveScore: Int
        getFreePositions(field).forEach {
            field[it.first][it.second] = humanSign
            currentMoveScore = minimax(field, true, botSign, humanSign)
            if (currentMoveScore < smallestScore) {
                smallestScore = currentMoveScore
            }
            field[it.first][it.second] = SIGN_OF_ABSENCE
        }
        return smallestScore
    }
}

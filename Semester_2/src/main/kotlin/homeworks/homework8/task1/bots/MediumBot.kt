package homeworks.homework8.task1.bots

import kotlin.random.Random

class MediumBot : Bot() {
    private companion object {
        const val CHANCE_OF_MOVE_OF_HARD_BOT = 0.6
    }

    private val easyBot = EasyBot()
    private val hardBot = HardBot()

    override fun getMove(field: MutableList<MutableList<String>>, botSign: String, humanSign: String): Pair<Int, Int> {
        return if (Random.nextDouble(0.0, 1.0) < CHANCE_OF_MOVE_OF_HARD_BOT) {
            hardBot.getMove(field, botSign, humanSign)
        } else {
            easyBot.getMove(field, botSign, humanSign)
        }
    }
}

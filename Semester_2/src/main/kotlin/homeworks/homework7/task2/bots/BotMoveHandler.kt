package homeworks.homework7.task2.bots

import java.lang.IllegalArgumentException

class BotMoveHandler {
    var easyBot = EasyBot()
    var mediumBot = MediumBot()
    var hardBot = HardBot()

    fun getMove(
        field: MutableList<MutableList<String>>,
        botSign: String,
        humanSign: String,
        botType: String
    ): Pair<Int, Int> {
        return when (botType) {
            "easyBot" -> easyBot.getMove(field, botSign, humanSign)
            "mediumBot" -> mediumBot.getMove(field, botSign, humanSign)
            "hardBot" -> hardBot.getMove(field, botSign, humanSign)
            else -> throw IllegalArgumentException("Difficulty level not defined")
        }
    }
}

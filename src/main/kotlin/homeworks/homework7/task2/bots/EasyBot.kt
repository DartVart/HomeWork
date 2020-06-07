package homeworks.homework7.task2.bots

import kotlin.random.Random

class EasyBot : Bot() {
    override fun getMove(field: MutableList<MutableList<String>>, botSign: String, humanSign: String): Pair<Int, Int> {
        val freePositions = getFreePositions(field)
        return if (freePositions.isNotEmpty()) {
            val randomIndex = Random.nextInt(0, freePositions.size)
            freePositions[randomIndex]
        } else {
            Pair(-1, -1)
        }
    }
}

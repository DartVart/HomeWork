package homeworks.homework4.task2

import java.io.InputStream

class ParsingTree(inputStream: InputStream) {
    private val root: ArithmeticExpressionElement
    init {
        val streamParser = StreamParser()
        root = streamParser.parseStream(inputStream)
    }

    fun calculate() = root.calculate()

    override fun toString() = root.toString()
}

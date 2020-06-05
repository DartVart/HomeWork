package homeworks.homework4.task2

import java.io.InputStream
import java.lang.IllegalStateException

class ParsingTree {
    private var root: ArithmeticExpressionElement? = null
    private val streamParser = StreamParser()

    /**
     * If the tree is not initialized, [IllegalStateException] will be thrown
     * */
    fun calculate() = root?.calculate() ?: throw IllegalStateException("The tree is not initialized")

    /**
     * If the stream is blank or line reading returned null, [IllegalStateException] will be thrown
     * */
    fun setExpressionFromStream(inputStream: InputStream) {
        root = streamParser.parseStream(inputStream)
    }

    /**
     * If the tree is not initialized, [IllegalStateException] will be thrown
     * */
    override fun toString(): String = root?.toString() ?: throw IllegalStateException("The tree is not initialized")
}

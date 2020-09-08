package homeworks.homework4.task2

import java.io.InputStream
import java.lang.IllegalStateException
import java.util.LinkedList

class StreamParser {
    private val tokens = LinkedList<String>()

    private fun getArithmeticExpressionTreeByString(inputString: String): ArithmeticExpressionElement {
        setTokens(inputString)
        return getNode()
    }

    private fun setTokens(inputString: String) {
        inputString.split(" ").forEach { it ->
            when {
                it[0] == '(' -> {
                    it.forEach { tokens.add(it.toString()) }
                }
                it.last() == ')' -> {
                    val pairOfNumberAndBrackets = it.partition { it != ')' }
                    tokens.add(pairOfNumberAndBrackets.first)
                    pairOfNumberAndBrackets.second.forEach {
                        tokens.add(it.toString())
                    }
                }
                else -> tokens.add(it)
            }
        }
    }

    private fun getNode(): ArithmeticExpressionElement {
        val currentToken = tokens.pop()
        val resultNode: ArithmeticExpressionElement
        if (currentToken == "(") {
            resultNode = Operator(tokens.pop(), getNode(), getNode())
            tokens.pop() // remove ")"
        } else {
            resultNode = Operand(currentToken.toInt())
        }
        return resultNode
    }

    /**
     * If the stream is blank or line reading returned null, [IllegalStateException] will be thrown
     * */
    fun parseStream(inputStream: InputStream): ArithmeticExpressionElement {
        val inputString = inputStream.bufferedReader().readLine()
        check(!inputString.isNullOrBlank()) { "Arithmetic expression not found." }
        return getArithmeticExpressionTreeByString(inputString)
    }
}

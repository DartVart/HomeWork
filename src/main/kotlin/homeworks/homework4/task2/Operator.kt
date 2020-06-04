package homeworks.homework4.task2

class Operator(
    var sign: String,
    var leftChild: ArithmeticExpressionElement,
    var rightChild: ArithmeticExpressionElement
) : ArithmeticExpressionElement {
    private companion object {
        val supportedOperators = listOf(
            Pair("+", { a: Double, b: Double -> a + b }),
            Pair("-", { a: Double, b: Double -> a - b }),
            Pair("/", { a: Double, b: Double -> a / b }),
            Pair("*", { a: Double, b: Double -> a * b })
        )
    }

    private fun isSupportedOperator(sign: String): Boolean = sign in supportedOperators.map { it.first }

    init {
        require(isSupportedOperator(sign)) { "'$sign' is not supported as an operator." }
    }

    override fun toString() = "($sign $leftChild $rightChild)"

    override fun calculate(): Double {
        val suitableArithmeticFunction = supportedOperators.find { it.first == sign }?.second
        check(suitableArithmeticFunction != null) { "Operation with sign '$sign' not found." }
        return suitableArithmeticFunction(leftChild.calculate(), rightChild.calculate())
    }
}

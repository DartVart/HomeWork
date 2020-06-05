package homeworks.homework4.task2

class Operator(
    private val sign: String,
    private val leftChild: ArithmeticExpressionElement,
    private val rightChild: ArithmeticExpressionElement
) : ArithmeticExpressionElement {
    private companion object {
        val supportedOperators = listOf(
            Operation("+") { a: Double, b: Double -> a + b },
            Operation("-") { a: Double, b: Double -> a - b },
            Operation("/") { a: Double, b: Double -> a / b },
            Operation("*") { a: Double, b: Double -> a * b }
        )
    }

    private val operation: (Double, Double) -> Double

    init {
        operation = supportedOperators.find { it.sign == sign }?.operation
            ?: throw IllegalStateException("Operation with sign '$sign' not found.")
    }

    override fun toString() = "($sign $leftChild $rightChild)"

    override fun calculate() = operation(leftChild.calculate(), rightChild.calculate())
}

package homeworks.homework4.task2

class Operand(private val value: Int) : ArithmeticExpressionElement {
    override fun toString() = value.toString()
    override fun calculate() = value.toDouble()
}

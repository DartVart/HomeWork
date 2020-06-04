package homeworks.homework4.task2

class Operand(var value: Int) : ArithmeticExpressionElement {
    override fun toString() = value.toString()
    override fun calculate() = value.toDouble()
}

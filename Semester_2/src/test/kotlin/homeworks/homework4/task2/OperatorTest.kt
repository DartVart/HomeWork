package homeworks.homework4.task2

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertThrows
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Test
import java.lang.IllegalArgumentException

internal class OperatorTest {

    fun getSimpleOperator(sign: String, leftOperandValue: Int, rightOperandValue: Int) =
        Operator(sign, Operand(leftOperandValue), Operand(rightOperandValue))

    @Nested
    inner class Check_toString {
        @Test
        fun twoOperands_MustWork() {
            val actual = getSimpleOperator("+", 2, 3).toString()
            val expected = "(+ 2 3)"
            assertEquals(expected, actual)
        }

        @Test
        fun operatorsAsChildren1_MustWork() {
            val leftChild = getSimpleOperator("-", 1, -3)
            val rightChild = getSimpleOperator("*", 0, -100)
            val root = Operator("+", leftChild, rightChild)
            val actual = root.toString()
            val expected = "(+ (- 1 -3) (* 0 -100))"
            assertEquals(expected, actual)
        }

        @Test
        fun operatorsAsChildren2_MustWork() {
            val leftChild = Operator("-", getSimpleOperator("*", -1, -8), Operand(-3))
            val rightChild = Operator("*", Operand(3), getSimpleOperator("-", 303, 2))
            val root = Operator("+", leftChild, rightChild)
            val actual = root.toString()
            val expected = "(+ (- (* -1 -8) -3) (* 3 (- 303 2)))"
            assertEquals(expected, actual)
        }
    }

    @Nested
    inner class Check_calculate {
        @Test
        fun operatorsAsChildren1_MustWork() {
            val leftChild = getSimpleOperator("-", 1, -3)
            val rightChild = getSimpleOperator("*", 0, -100)
            val root = Operator("+", leftChild, rightChild)
            assertEquals(4.0, root.calculate())
        }

        @Test
        fun operatorsAsChildren2_MustWork() {
            val leftChild = Operator("-", getSimpleOperator("*", -1, -8), Operand(-3))
            val rightChild = Operator("*", Operand(3), getSimpleOperator("-", 303, 2))
            val root = Operator("+", leftChild, rightChild)
            assertEquals(914.0, root.calculate())
        }

        @Test
        fun checkAddition_MustWork() {
            assertEquals(5.0, getSimpleOperator("+", 2, 3).calculate())
        }

        @Test
        fun checkSubtraction_MustWork() {
            assertEquals(18.0, getSimpleOperator("-", 10, -8).calculate())
        }

        @Test
        fun checkDivision_MustWork() {
            assertEquals(100.toDouble() / 3, getSimpleOperator("/", 100, 3).calculate())
        }

        @Test
        fun checkMultiplication_MustWork() {
            assertEquals(100.0, getSimpleOperator("*", 25, 4).calculate())
        }
    }

    @Nested
    inner class Check_initialization {
        @Test
        fun initialization_UnsupportedOperator_ThrowsException() {
            assertThrows(IllegalArgumentException::class.java) {
                Operator("?", Operand(2), Operand(3))
            }
        }
    }
}

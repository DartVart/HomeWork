package homeworks.homework4.task2

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertThrows
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Test
import java.io.ByteArrayInputStream
import java.io.File
import java.io.InputStream
import java.lang.IllegalStateException

const val PATH_TO_TEXT_FILE = "./src/test/resources/homeworks/homework4/task2/expression.txt"

internal class ParsingTreeTest {
    private fun getStreamFromString(string: String) = ByteArrayInputStream(string.toByteArray())

    val twoOperands = getStreamFromString("(+ 90 1)")
    val operandThenOperatorAsChildren = getStreamFromString("(* 90 (- 0 3))")
    val operatorThenOperandAsChildren = getStreamFromString("(/ (- 30 -34) 8)")
    val twoOperandsAsChildren = getStreamFromString("(- (- 100 100) (- 100 100))")
    val onlyOneOperand = getStreamFromString("4")
    val complexExpression1 = getStreamFromString("(+ (- 0 10) (/ (+ 90 80) (- 8 4)))")
    val complexExpression2 = getStreamFromString("(+ (- 0 (+ 5 5)) (/ (+ (+ 34 8) (- 3 4)) (- (* 9 3) (/ 4 2))))")
    val manyClosingBracketsNext = getStreamFromString("(+ 3 (- 4 (+ 9 (* 8 (+ 10 (- -90 (- 78 9)))))))")

    @Nested
    inner class Check_toString {
        @Test
        fun twoOperands_MustWork() {
            val actual = ParsingTree(twoOperands).toString()
            val expected = "(+ 90 1)"
            assertEquals(expected, actual)
        }

        @Test
        fun operandThenOperatorAsChildren_MustWork() {
            val actual = ParsingTree(operandThenOperatorAsChildren).toString()
            val expected = "(* 90 (- 0 3))"
            assertEquals(expected, actual)
        }

        @Test
        fun operatorThenOperandAsChildren_MustWork() {
            val actual = ParsingTree(operatorThenOperandAsChildren).toString()
            val expected = "(/ (- 30 -34) 8)"
            assertEquals(expected, actual)
        }

        @Test
        fun twoOperandsAsChildren_MustWork() {
            val actual = ParsingTree(twoOperandsAsChildren).toString()
            val expected = "(- (- 100 100) (- 100 100))"
            assertEquals(expected, actual)
        }

        @Test
        fun onlyOneOperand_MustWork() {
            val actual = ParsingTree(onlyOneOperand).toString()
            val expected = "4"
            assertEquals(expected, actual)
        }

        @Test
        fun complexExpression1_MustWork() {
            val actual = ParsingTree(complexExpression1).toString()
            val expected = "(+ (- 0 10) (/ (+ 90 80) (- 8 4)))"
            assertEquals(expected, actual)
        }

        @Test
        fun complexExpression2_MustWork() {
            val actual = ParsingTree(complexExpression2).toString()
            val expected = "(+ (- 0 (+ 5 5)) (/ (+ (+ 34 8) (- 3 4)) (- (* 9 3) (/ 4 2))))"
            assertEquals(expected, actual)
        }

        @Test
        fun manyClosingBracketsNext_MustWork() {
            val actual = ParsingTree(manyClosingBracketsNext).toString()
            val expected = "(+ 3 (- 4 (+ 9 (* 8 (+ 10 (- -90 (- 78 9)))))))"
            assertEquals(expected, actual)
        }
    }

    @Nested
    inner class Check_calculate {
        @Test
        fun twoOperands_MustWork() {
            val actual = ParsingTree(twoOperands).calculate()
            val expected = 91.0
            assertEquals(expected, actual)
        }

        @Test
        fun operandThenOperatorAsChildren_MustWork() {
            val actual = ParsingTree(operandThenOperatorAsChildren).calculate()
            val expected = -270.0
            assertEquals(expected, actual)
        }

        @Test
        fun operatorThenOperandAsChildren_MustWork() {
            val actual = ParsingTree(operatorThenOperandAsChildren).calculate()
            val expected = 8.0
            assertEquals(expected, actual)
        }

        @Test
        fun twoOperandsAsChildren_MustWork() {
            val actual = ParsingTree(twoOperandsAsChildren).calculate()
            val expected = 0.0
            assertEquals(expected, actual)
        }

        @Test
        fun onlyOneOperand_MustWork() {
            val actual = ParsingTree(onlyOneOperand).calculate()
            val expected = 4.0
            assertEquals(expected, actual)
        }

        @Test
        fun complexExpression1_MustWork() {
            val actual = ParsingTree(complexExpression1).calculate()
            val expected = 32.5
            assertEquals(expected, actual)
        }

        @Test
        fun complexExpression2_MustWork() {
            val actual = ParsingTree(complexExpression2).calculate()
            val expected = -8.36
            assertEquals(expected, actual)
        }

        @Test
        fun manyClosingBracketsNext_MustWork() {
            val actual = ParsingTree(manyClosingBracketsNext).calculate()
            val expected = 1190.0
            assertEquals(expected, actual)
        }
    }

    @Nested
    inner class Check_setExpressionFromStream {
        @Test
        fun streamFromFile_MustWork() {
            val inputFile = File(PATH_TO_TEXT_FILE)
            val tree = ParsingTree(inputFile.inputStream())
            assertEquals(9.8, tree.calculate())
        }

        @Test
        fun emptyStream_ThrowsException() {
            val emptyStream = ByteArrayInputStream("    ".toByteArray())
            assertThrows(IllegalStateException::class.java) {
                ParsingTree(emptyStream)
            }
        }
    }
}

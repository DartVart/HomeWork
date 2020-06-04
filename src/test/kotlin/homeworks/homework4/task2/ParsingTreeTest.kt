package homeworks.homework4.task2

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertThrows
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Test
import java.io.File
import java.io.FileNotFoundException
import java.lang.IllegalStateException

const val PATH_TO_DIRECTORY_WITH_TEXTS = "./src/test/resources/homeworks/homework4/task2"

internal class ParsingTreeTest {

    fun getTreeFromFile(fileName: String): ParsingTree {
        val parsingTree = ParsingTree()
        val inputFile = File("$PATH_TO_DIRECTORY_WITH_TEXTS/$fileName")
        parsingTree.setExpressionFromFile(inputFile)
        return parsingTree
    }

    @Nested
    inner class Check_toString {
        @Test
        fun twoOperands_MustWork() {
            val actual = getTreeFromFile("twoOperands.txt").toString()
            val expected = "(+ 90 1)"
            assertEquals(expected, actual)
        }

        @Test
        fun operandThenOperatorAsChildren_MustWork() {
            val actual = getTreeFromFile("operandThenOperatorAsChildren.txt").toString()
            val expected = "(* 90 (- 0 3))"
            assertEquals(expected, actual)
        }

        @Test
        fun operatorThenOperandAsChildren_MustWork() {
            val actual = getTreeFromFile("operatorThenOperandAsChildren.txt").toString()
            val expected = "(/ (- 30 -34) 8)"
            assertEquals(expected, actual)
        }

        @Test
        fun twoOperandsAsChildren_MustWork() {
            val actual = getTreeFromFile("twoOperandsAsChildren.txt").toString()
            val expected = "(- (- 100 100) (- 100 100))"
            assertEquals(expected, actual)
        }

        @Test
        fun onlyOneOperand_MustWork() {
            val actual = getTreeFromFile("onlyOneOperand.txt").toString()
            val expected = "4"
            assertEquals(expected, actual)
        }

        @Test
        fun complexTree1_MustWork() {
            val actual = getTreeFromFile("complexTree1.txt").toString()
            val expected = "(+ (- 0 10) (/ (+ 90 80) (- 8 4)))"
            assertEquals(expected, actual)
        }

        @Test
        fun complexTree2_MustWork() {
            val actual = getTreeFromFile("complexTree2.txt").toString()
            val expected = "(+ (- 0 (+ 5 5)) (/ (+ (+ 34 8) (- 3 4)) (- (* 9 3) (/ 4 2))))"
            assertEquals(expected, actual)
        }

        @Test
        fun manyClosingBracketsNext_MustWork() {
            val actual = getTreeFromFile("manyClosingBracketsNext.txt").toString()
            val expected = "(+ 3 (- 4 (+ 9 (* 8 (+ 10 (- -90 (- 78 9)))))))"
            assertEquals(expected, actual)
        }

        @Test
        fun parsingFromMoreThanOneFile_MustWork() {
            val tree = getTreeFromFile("complexTree1.txt")
            val secondFile = File("$PATH_TO_DIRECTORY_WITH_TEXTS/complexTree2.txt")
            tree.setExpressionFromFile(secondFile)
            val actual = tree.toString()
            val expected = "(+ (- 0 (+ 5 5)) (/ (+ (+ 34 8) (- 3 4)) (- (* 9 3) (/ 4 2))))"
            assertEquals(expected, actual)
        }

        @Test
        fun uninitializedTree_ThrowsException() {
            assertThrows(IllegalStateException::class.java) {
                ParsingTree().toString()
            }
        }
    }

    @Nested
    inner class Check_calculate {
        @Test
        fun twoOperands_MustWork() {
            val actual = getTreeFromFile("twoOperands.txt").calculate()
            val expected = 91.0
            assertEquals(expected, actual)
        }

        @Test
        fun operandThenOperatorAsChildren_MustWork() {
            val actual = getTreeFromFile("operandThenOperatorAsChildren.txt").calculate()
            val expected = -270.0
            assertEquals(expected, actual)
        }

        @Test
        fun operatorThenOperandAsChildren_MustWork() {
            val actual = getTreeFromFile("operatorThenOperandAsChildren.txt").calculate()
            val expected = 8.0
            assertEquals(expected, actual)
        }

        @Test
        fun twoOperandsAsChildren_MustWork() {
            val actual = getTreeFromFile("twoOperandsAsChildren.txt").calculate()
            val expected = 0.0
            assertEquals(expected, actual)
        }

        @Test
        fun onlyOneOperand_MustWork() {
            val actual = getTreeFromFile("onlyOneOperand.txt").calculate()
            val expected = 4.0
            assertEquals(expected, actual)
        }

        @Test
        fun complexTree1_MustWork() {
            val actual = getTreeFromFile("complexTree1.txt").calculate()
            val expected = 32.5
            assertEquals(expected, actual)
        }

        @Test
        fun complexTree2_MustWork() {
            val actual = getTreeFromFile("complexTree2.txt").calculate()
            val expected = -8.36
            assertEquals(expected, actual)
        }

        @Test
        fun manyClosingBracketsNext_MustWork() {
            val actual = getTreeFromFile("manyClosingBracketsNext.txt").calculate()
            val expected = 1190.0
            assertEquals(expected, actual)
        }

        @Test
        fun parsingFromMoreThanOneFile_MustWork() {
            val tree = getTreeFromFile("complexTree1.txt")
            val secondFile = File("$PATH_TO_DIRECTORY_WITH_TEXTS/complexTree2.txt")
            tree.setExpressionFromFile(secondFile)
            val actual = tree.calculate()
            val expected = -8.36
            assertEquals(expected, actual)
        }

        @Test
        fun uninitializedTree_ThrowsException() {
            assertThrows(IllegalStateException::class.java) {
                ParsingTree().calculate()
            }
        }
    }

    @Nested
    inner class Check_setExpressionFromFile {
        @Test
        fun nonexistentFile_ThrowsException() {
            val tree = ParsingTree()
            val nonexistentFile = File("nonexistentFile.txt")
            assertThrows(FileNotFoundException::class.java) {
                tree.setExpressionFromFile(nonexistentFile)
            }
        }

        @Test
        fun emptyFile_ThrowsException() {
            val tree = ParsingTree()
            val emptyFile = File("$PATH_TO_DIRECTORY_WITH_TEXTS/empty.txt")
            assertThrows(IllegalStateException::class.java) {
                tree.setExpressionFromFile(emptyFile)
            }
        }
    }
}

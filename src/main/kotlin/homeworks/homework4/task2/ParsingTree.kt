package homeworks.homework4.task2

import java.io.File
import java.io.FileNotFoundException
import java.lang.IllegalStateException

class ParsingTree {
    private var root: ArithmeticExpressionElement? = null
    private val fileParser = FileParser()

    /**
     * If the tree is not initialized, [IllegalStateException] will be thrown
     * */
    fun calculate() = root?.calculate() ?: throw IllegalStateException("The tree is not initialized")

    /**
     * If the file is not found, [FileNotFoundException] will be thrown
     * if the file is empty, [IllegalStateException] will be thrown
     * */
    fun setExpressionFromFile(inputFile: File) {
        if (!inputFile.exists()) {
            throw FileNotFoundException("File \"${inputFile.path}\" not found.")
        }
        root = fileParser.parseFile(inputFile)
    }

    /**
     * If the tree is not initialized, [IllegalStateException] will be thrown
     * */
    override fun toString(): String = root?.toString() ?: throw IllegalStateException("The tree is not initialized")
}

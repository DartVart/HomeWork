package homeworks.homework1.task5

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertThrows
import java.io.FileNotFoundException
import java.io.File

internal class Task5KtTest {

    private val pathToFolderWithTexts = "./src/test/resources/homeworks/homework1/task5"

    @Test
    fun countNonEmptyLines_NonEmpty1_MustWork() {
        val inputFile = File("${pathToFolderWithTexts}/nonEmpty1.txt")
        assertEquals(24, countNonBlankLines(inputFile))
    }

    @Test
    fun countNonEmptyLines_NonEmpty2_MustWork() {
        val inputFile = File("${pathToFolderWithTexts}/nonEmpty2.txt")
        assertEquals(7, countNonBlankLines(inputFile))
    }

    @Test
    fun countNonEmptyLines_NonEmpty3_MustWork() {
        val inputFile = File("${pathToFolderWithTexts}/nonEmpty3.txt")
        assertEquals(2, countNonBlankLines(inputFile))
    }

    @Test
    fun countNonEmptyLines_EmptyFile_MustWork() {
        val inputFile = File("${pathToFolderWithTexts}/empty.txt")
        assertEquals(0, countNonBlankLines(inputFile))
    }

    @Test
    fun countNonEmptyLines_BlankFile_MustWork() {
        val inputFile = File("${pathToFolderWithTexts}/blank.txt")
        assertEquals(0, countNonBlankLines(inputFile))
    }

    @Test
    fun countNonEmptyLines_OneNonEmptyLine_MustWork() {
        val inputFile = File("${pathToFolderWithTexts}/oneNonEmptyLine.txt")
        assertEquals(1, countNonBlankLines(inputFile))
    }

    @Test
    fun countNonEmptyLines_WithoutBlankLines_MustWork() {
        val inputFile = File("${pathToFolderWithTexts}/withoutBlankLines.txt")
        assertEquals(10, countNonBlankLines(inputFile))
    }

    @Test
    fun countNonEmptyLines_FileDoesNotExist_ThrowsException() {
        val inputFile = File("${pathToFolderWithTexts}/nonexistentFile.txt")
        assertThrows(FileNotFoundException::class.java) { countNonBlankLines(inputFile) }
    }
}

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions.*
import java.io.File
import java.io.FileNotFoundException

internal class Task5KtTest {

    @Test
    fun CountNonEmptyLines_NonEmty1_MustWork(){
        val inputFile = File("./src/test/resources/nonEmpty1.txt")
        assertEquals(24, countNonBlankLines(inputFile))
    }

    @Test
    fun CountNonEmptyLines_NonEmty2_MustWork(){
        val inputFile = File("./src/test/resources/nonEmpty2.txt")
        assertEquals(7, countNonBlankLines(inputFile))
    }

    @Test
    fun CountNonEmptyLines_NonEmty3_MustWork(){
        val inputFile = File("./src/test/resources/nonEmpty3.txt")
        assertEquals(24, countNonBlankLines(inputFile))
    }

    @Test
    fun CountNonEmptyLines_EmptyFile_MustWork(){
        val inputFile = File("./src/test/resources/empty.txt")
        assertEquals(0, countNonBlankLines(inputFile))
    }
    @Test
    fun CountNonEmptyLines_BlankFile_MustWork(){
        val inputFile = File("./src/test/resources/blank.txt")
        assertEquals(0, countNonBlankLines(inputFile))
    }

    @Test
    fun CountNonEmptyLines_OneNonEmptyLine_MustWork(){
        val inputFile = File("./src/test/resources/oneNonEmptyLine.txt")
        assertEquals(1, countNonBlankLines(inputFile))
    }

    @Test
    fun CountNonEmptyLines_WithoutBlankLines_MustWork(){
        val inputFile = File("./src/test/resources/withoutBlankLines.txt")
        assertEquals(10, countNonBlankLines(inputFile))
    }

    @Test
    fun CountNonEmptyLines_FileDoesNotExist_ThrowsException(){
        val inputFile = File("./src/test/resources/nonexistentFile.txt")
        assertThrows(FileNotFoundException::class.java) {countNonBlankLines(inputFile)}
    }
}
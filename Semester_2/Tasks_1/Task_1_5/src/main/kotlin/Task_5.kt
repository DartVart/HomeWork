import java.io.File
import java.io.FileNotFoundException

fun countNonBlankLines(inputFile: File): Long {
    if (!inputFile.exists()) {
        throw FileNotFoundException("File \"${inputFile.path}\" not found")
    }
    val inputFileStream = inputFile.inputStream()
    val answer = inputFileStream
        .bufferedReader()
        .lines()
        .filter { line -> line.isNotBlank() }
        .count()

    inputFileStream.close()
    return answer
}

fun main() {
    val inputFile = File("./src/main/resources/input.txt")
    try {
        val numberOfNonBlankLines = countNonBlankLines(inputFile)
        println("Number of non-empty lines in the file \"${inputFile.path}\": $numberOfNonBlankLines")
    } catch (e: FileNotFoundException) {
        println(e.message)
    } catch (e: Exception) {
        throw e
    }
}
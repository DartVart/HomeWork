package homeworks.homework1.task3

import java.lang.IllegalArgumentException
import java.util.Scanner

fun getNumberOfSubstrings(string: String, substring: String): Int {
    if (substring.isEmpty()) {
        throw IllegalArgumentException("Substring cannot be empty")
    }

    val maximumCheckedIndex = string.length - substring.length
    var numberOfSubstrings = 0
    for (i in 0..maximumCheckedIndex) {
        if (string.substring(i, i + substring.length) == substring) {
            numberOfSubstrings++
        }
    }
    return numberOfSubstrings
}

fun main() {
    val scan = Scanner(System.`in`)

    println("Enter a string:")
    val inputString = scan.nextLine()

    println("Enter a substring:")
    val substring = scan.nextLine()

    try {
        val numberOfSubstrings = getNumberOfSubstrings(inputString, substring)
        println("The number of occurrences of the substring \"$substring\": $numberOfSubstrings")
    } catch (exception: IllegalArgumentException) {
        println("Error: ${exception.message}")
    }
}

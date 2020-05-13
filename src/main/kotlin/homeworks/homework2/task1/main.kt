package homeworks.homework2.task1

import java.util.Scanner

/**
 * Counts how many characters 'x' should be removed so that [sourceString] doesn't contain "xxx"
 * */
fun countCharactersToBeDeleted(sourceString: String): Int {
    return Regex("xxx+")
        .findAll(sourceString)
        .fold(0) { total, matchResult ->
            total + matchResult.value.length - 2
        }
}

fun main() {
    val scan = Scanner(System.`in`)

    println("Enter a string:")
    val inputString = scan.nextLine()

    println("Minimum number of characters 'x' to be deleted: ${countCharactersToBeDeleted(inputString)}")
}

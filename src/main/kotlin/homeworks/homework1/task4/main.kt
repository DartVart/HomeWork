package homeworks.homework1.task4

import java.util.Scanner

fun isPalindrome(checkingString: String): Boolean {
    val length = checkingString.length
    val indexOfCenter = length / 2
    for (i in 0 until indexOfCenter) {
        if (checkingString[i] != checkingString[length - 1 - i]) {
            return false
        }
    }
    return true
}

fun main() {
    val scan = Scanner(System.`in`)
    println("Enter a string:")
    val inputString = scan.nextLine()

    if (isPalindrome(inputString)) {
        println("It's a palindrome")
    } else {
        println("It's not a palindrome")
    }
}

import java.util.*

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
    println(if (isPalindrome(inputString)) "It's a palindrome" else "It's not a palindrome")
}
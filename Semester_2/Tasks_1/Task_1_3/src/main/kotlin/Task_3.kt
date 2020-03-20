import java.util.*

fun getNumberOfSubstrings(string: String, substring: String): Int {
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

    print("The number of occurrences of the substring \"$substring\": ")
    println(getNumberOfSubstrings(inputString, substring))
}
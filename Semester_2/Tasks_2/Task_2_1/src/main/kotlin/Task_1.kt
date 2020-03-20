import java.util.*

fun countCharactersToBeDeleted(string: String): Int {
    return Regex("xxx+")
        .findAll(string)
        .fold(0) { total, matchResult ->
            total + matchResult.value.length - 2
        }
}

fun main(){
    val scan = Scanner(System.`in`)

    println("Enter a string:")
    val inputString = scan.nextLine()

    println("Minimum number of characters to be deleted: ${countCharactersToBeDeleted(inputString)}")
}
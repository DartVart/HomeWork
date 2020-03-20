import java.util.*

fun scanNonNegativeInteger(): Int {
    val scan = Scanner(System.`in`)
    var number = scan.nextInt()
    while (number < 0) {
        println("Please, enter a non-negative integer.")
        number = scan.nextInt()
    }
    return number
}

fun getRecursiveFactorial(number: Int): Int {
    if (number < 0) {
        throw IllegalArgumentException("The number must be non-negative")
    }
    return if (number == 0) 1 else getRecursiveFactorial(number - 1) * number
}

fun getIterativeFactorial(number: Int): Int {
    if (number < 0) {
        throw IllegalArgumentException("The number must be non-negative")
    }
    var result = 1
    for (i in 2..number) {
        result *= i
    }
    return result
}

fun main() {
    println("Enter a non-negative number:")
    val inputNumber = scanNonNegativeInteger()

    println("Result:")
    println("$inputNumber! = ${getRecursiveFactorial(inputNumber)} (recursive)")
    println("$inputNumber! = ${getIterativeFactorial(inputNumber)} (iterative)")
}
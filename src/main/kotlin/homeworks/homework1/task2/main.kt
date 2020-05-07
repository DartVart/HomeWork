package homeworks.homework1.task2

import java.util.Scanner

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
    require(number >= 0) {
        "The number must be non-negative"
    }

    return if (number == 0) 1 else getRecursiveFactorial(number - 1) * number
}

fun getIterativeFactorial(number: Int): Int {
    require(number >= 0) {
        "The number must be non-negative"
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

    try {
        println("Factorial of $inputNumber: ${getRecursiveFactorial(inputNumber)} (recursive)")
        println("Factorial of $inputNumber: ${getIterativeFactorial(inputNumber)} (iterative)")
    } catch (exception: IllegalArgumentException) {
        println("Error: ${exception.message}")
    }
}

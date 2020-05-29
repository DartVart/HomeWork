package homeworks.homework1.task2

/**
 * Tries to read a non-negative integer from the console until the integer is entered correctly
 * */
fun scanNonNegativeInteger(): Int {
    var number: Int? = null
    while (number == null || number < 0) {
        try {
            number = readLine()?.toInt()
        } catch (exception: NumberFormatException) {
            println("Please, enter a single integer.")
            continue
        }

        when {
            number == null -> {
                println("Please, try to enter an integer again.")
            }
            number < 0 -> {
                println("Please, enter a non-negative integer.")
            }
        }
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

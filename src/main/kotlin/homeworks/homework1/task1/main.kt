package homeworks.homework1.task1

import java.lang.IllegalArgumentException
import java.lang.IllegalStateException

/**
 * Tries to read an non-negative integer from the console until the integer is entered correctly
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
                println("Please, try to enter the integer again.")
            }
            number < 0 -> {
                println("Please, enter the non-negative integer.")
            }
        }
    }
    return number
}

/**
 * Tries to read an list from the console until the list is entered correctly
 * */
fun scanIntList(delimiters: Regex = Regex(" +")): List<Int> {
    var scannedList: List<Int>? = null
    while (scannedList == null) {
        try {
            scannedList = readLine()?.trim()?.split(delimiters)?.map { it.toInt() }
        } catch (exception: NumberFormatException) {
            println("Please, enter a string of integers only.")
            continue
        }

        if (scannedList == null) {
            println("Please, try to enter the string of integers again.")
        }
    }
    return scannedList
}

fun scanInputData(): Triple<Int, Int, MutableList<Int>> {
    println("Enter the number of elements in the first part of the array:")
    val firstPartLength = scanNonNegativeInteger()

    println("Enter the number of elements in the second part of the array:")
    val secondPartLength = scanNonNegativeInteger()

    println("Enter the array:")
    val list = scanIntList().toMutableList()

    check(secondPartLength + firstPartLength == list.size) {
        "The list size doesn't equal to the sum of its parts"
    }

    return Triple(firstPartLength, secondPartLength, list)
}

fun changePartsOfList(firstPartLength: Int, secondPartLength: Int, list: MutableList<Int>) {
    require(secondPartLength + firstPartLength == list.size) {
        "The list size doesn't equal to the sum of its parts"
    }

    list.subList(0, firstPartLength).reverse()
    list.subList(firstPartLength, firstPartLength + secondPartLength).reverse()
    list.reverse()
}

fun main() {
    try {
        val (sizeOfFirstPart, sizeOfSecondPart, inputList) = scanInputData()
        changePartsOfList(sizeOfFirstPart, sizeOfSecondPart, inputList)
        println("Array with moved parts: ${inputList.joinToString(", ", "[", "]")}")
    } catch (exception: IllegalStateException) {
        println("Error: ${exception.message}")
    } catch (exception: IllegalArgumentException) {
        println("Error: ${exception.message}")
    }
}

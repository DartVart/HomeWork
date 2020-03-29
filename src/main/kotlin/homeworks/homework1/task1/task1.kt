package homeworks.homework1.task1

import java.lang.IndexOutOfBoundsException
import java.util.Scanner

fun scanPositiveInteger(): Int {
    val scan = Scanner(System.`in`)
    var number = scan.nextInt()
    while (number < 0) {
        println("Please, enter a non-negative integer.")
        number = scan.nextInt()
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

fun changePartOfList(firstPartLength: Int, secondPartLength: Int, list: MutableList<Int>) {
    val listSize = firstPartLength + secondPartLength
    when {
        firstPartLength < 0 || secondPartLength < 0 -> {
            throw IndexOutOfBoundsException("The size of the list part is negative")
        }
        listSize != list.size -> {
            throw IndexOutOfBoundsException("The list size doesn't equal to the sum of its parts")
        }
    }

    list.subList(0, firstPartLength).reverse()
    list.subList(firstPartLength, listSize).reverse()
    list.reverse()
}

fun main() {
    println("Enter the number of elements in the first part of the array:")
    val sizeOfFirstPart = scanPositiveInteger()

    println("Enter the number of elements in the second part of the array:")
    val sizeOfSecondPart = scanPositiveInteger()

    println("Enter the array:")
    val inputList: MutableList<Int> = scanIntList().toMutableList()

    try {
        changePartOfList(sizeOfFirstPart, sizeOfSecondPart, inputList)
        println("Array with moved parts: ${inputList.joinToString(", ", "[", "]")}")
    } catch (exception: IndexOutOfBoundsException) {
        println("Error: ${exception.message}")
    }
}

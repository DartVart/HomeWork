package homeworks.homework1.task1

import java.lang.IndexOutOfBoundsException
import java.util.Scanner

fun scanPositiveInteger(): Int {
    val scan = Scanner(System.`in`)
    var number = scan.nextInt()
    while (number < 1) {
        println("Please, enter a positive integer.")
        number = scan.nextInt()
    }
    return number
}

/**
 * Tries to read an array from the console until the array is entered correctly
 * */
fun scanIntList(delimiters: Regex = Regex(" +")): List<Int> {
    var scannedArray: List<Int>? = null
    while (scannedArray == null) {
        try {
            scannedArray = readLine()?.trim()?.split(delimiters)?.map { it.toInt() }
        } catch (exception: NumberFormatException) {
            println("Please, enter a string of integers only.")
            continue
        }
        if (scannedArray == null) {
            println("Please, try to enter the string of integers again.")
        }
    }
    return scannedArray
}

fun changePartOfList(firstPartLength: Int, secondPartLength: Int, list: MutableList<Int>) {
    when {
        firstPartLength < 0 || secondPartLength < 0 -> {
            throw IndexOutOfBoundsException("The size of the list part is negative")
        }
        firstPartLength + secondPartLength != list.size -> {
            throw IndexOutOfBoundsException("The list size doesn't equal to the sum of its parts")
        }
    }

    list.subList(0, firstPartLength).reverse()
    list.subList(firstPartLength, list.size).reverse()
    list.subList(0, list.size).reverse()
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

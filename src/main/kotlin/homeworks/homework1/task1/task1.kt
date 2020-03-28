package homeworks.homework1.task1

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

fun scanIntegerArray(size: Int): IntArray {
    val scan = Scanner(System.`in`)
    return IntArray(size) { scan.nextInt() }
}

/**
 * Reverses part of an array including elements with indices [startIndex] and [endIndex]
 * */
fun reversePartOfArray(startIndex: Int, endIndex: Int, array: IntArray) {
    var leftIndex = when {
        (startIndex < 0) -> 0
        (startIndex >= array.size) -> array.size - 1
        else -> startIndex
    }
    var rightIndex = when {
        endIndex < leftIndex -> leftIndex
        (endIndex >= array.size) -> array.size - 1
        else -> endIndex
    }

    val numberOfSwapping = (rightIndex - leftIndex + 1) / 2
    repeat(numberOfSwapping) {
        array[leftIndex] = array[rightIndex].also { array[rightIndex] = array[leftIndex] }
        rightIndex--
        leftIndex++
    }
}

fun changePartOfArray(firstPartLength: Int, array: IntArray) {
    val safeFirstPartLength = when {
        firstPartLength > array.size -> array.size
        firstPartLength < 0 -> 0
        else -> firstPartLength
    }

    reversePartOfArray(0, safeFirstPartLength - 1, array)
    reversePartOfArray(safeFirstPartLength, array.size - 1, array)
    reversePartOfArray(0, array.size - 1, array)
}

fun main() {
    println("Enter the number of elements in the first part of the array:")
    val sizeOfFirstPart = scanPositiveInteger()

    println("Enter the number of elements in the second part of the array:")
    val sizeOfSecondPart = scanPositiveInteger()

    val sizeOfArray = sizeOfFirstPart + sizeOfSecondPart
    println("Enter the array:")
    val inputArray: IntArray = scanIntegerArray(sizeOfArray)

    changePartOfArray(sizeOfFirstPart, inputArray)
    println("Array with moved parts: ${inputArray.joinToString(", ", "[", "]")}")
}

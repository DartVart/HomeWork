package homeworks.homework6.task1

import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import kotlin.system.measureTimeMillis

/**
 * Elements will be in ascending order.
 * */
suspend fun <T> asyncQuickSort(
    list: MutableList<T>,
    leftElement: Int = 0,
    rightElement: Int = list.lastIndex
) where T : Comparable<T> {
    if (rightElement - leftElement < 1) {
        return
    }

    var upIterator = leftElement
    var downIterator = rightElement
    val middleIndex = (leftElement + rightElement) / 2
    val middleValue = list[middleIndex]

    while (upIterator < downIterator) {
        while (list[upIterator] < middleValue) {
            upIterator++
        }

        while (list[downIterator] > middleValue) {
            downIterator--
        }

        if (upIterator <= downIterator) {
            list[upIterator] = list[downIterator].also { list[downIterator] = list[upIterator] }
            upIterator++
            downIterator--
        }
    }

    asyncQuickSort(list, upIterator, rightElement)
    asyncQuickSort(list, leftElement, downIterator)
}

/**
 * Elements will be in ascending order.
 * */
fun <T> usualQuickSort(
    list: MutableList<T>,
    leftElement: Int = 0,
    rightElement: Int = list.lastIndex
) where T : Comparable<T> {
    if (rightElement - leftElement < 1) {
        return
    }

    var upIterator = leftElement
    var downIterator = rightElement
    val middleIndex = (leftElement + rightElement) / 2
    val middleValue = list[middleIndex]

    while (upIterator < downIterator) {
        while (list[upIterator] < middleValue) {
            upIterator++
        }

        while (list[downIterator] > middleValue) {
            downIterator--
        }

        if (upIterator <= downIterator) {
            list[upIterator] = list[downIterator].also { list[downIterator] = list[upIterator] }
            upIterator++
            downIterator--
        }
    }

    usualQuickSort(list, upIterator, rightElement)
    usualQuickSort(list, leftElement, downIterator)
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
            println("Please, try to enter a string of integers again.")
        }
    }
    return scannedList
}

fun main() {
    println("Enter the array:")
    val listForAsyncSorting = scanIntList().toMutableList()
    val listForUsualSorting = listForAsyncSorting.toMutableList()

    val timeOfAsyncSorting = measureTimeMillis {
        runBlocking {
            launch {
                asyncQuickSort(listForAsyncSorting)
            }
        }
    }

    val timeOfUsualSorting = measureTimeMillis {
        usualQuickSort(listForUsualSorting)
    }

    println("Sorted array: ${listForAsyncSorting.joinToString(", ", "[", "]")}")
    println("Time of async sorting: $timeOfAsyncSorting")
    println("Time of usual sorting: $timeOfUsualSorting")
}

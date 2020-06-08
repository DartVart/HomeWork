package homeworks.homework6.task1

import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import kotlin.system.measureTimeMillis

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
    val quickSort = QuickSort<Int>()
    println("Enter the array:")
    val listForAsyncSorting = scanIntList().toMutableList()
    val listForUsualSorting = listForAsyncSorting.toMutableList()

    val timeOfAsyncSorting = measureTimeMillis {
        runBlocking {
            launch {
                quickSort.asyncQuickSort(listForAsyncSorting)
            }
        }
    }

    val timeOfUsualSorting = measureTimeMillis {
        quickSort.usualQuickSort(listForUsualSorting)
    }

    println("Sorted array: ${listForAsyncSorting.joinToString(", ", "[", "]")}")
    println("Time of async sorting: $timeOfAsyncSorting")
    println("Time of usual sorting: $timeOfUsualSorting")
}

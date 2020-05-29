package tests.test2.task1

fun <T> bubbleSort(array: Array<T>, comparator: Comparator<T>) {
    for (i in array.indices) {
        for (j in 0 until (array.size - 1)) {
            if (comparator.compare(array[j], array[j + 1]) > 0) {
                array[j] = array[j + 1].also { array[j + 1] = array[j] }
            }
        }
    }
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
    val inputArray = scanIntList().toTypedArray()
    bubbleSort(inputArray, IntComparator())
    println("Sorted array: ${inputArray.joinToString(", ", "[", "]")}")
}

package homeworks.homework2.task2

/**
 * Leaves only the right entry
 * */
inline fun <reified T> getArrayWithoutDuplicateItems(array: Array<T>): Array<T> {
    return array
        .reversed()
        .toSet()
        .reversed()
        .toTypedArray()
}

/**
 * Tries to read an array from the console until the array is entered correctly
 * */
fun scanStringArray(delimiters: Regex = Regex(" +")): Array<String> {
    var scannedArray: Array<String>? = null
    while (scannedArray == null) {
        scannedArray = readLine()?.trim()?.split(delimiters)?.toTypedArray()
        if (scannedArray == null) {
            println("Please, try to enter the array of strings again.")
        }
    }
    return scannedArray
}

fun main() {
    println("Enter the array of strings:")
    val inputArray: Array<String> = scanStringArray()
    val arrayWithRemovedItems: Array<String> = getArrayWithoutDuplicateItems(inputArray)

    print("Array after removing duplicate elements: ${arrayWithRemovedItems.joinToString(", ", "[", "]")}")
}

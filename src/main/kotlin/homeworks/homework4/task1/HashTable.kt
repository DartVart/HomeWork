package homeworks.homework4.task1

import java.io.File
import java.io.FileNotFoundException
import kotlin.math.abs

class HashTable<K, V>(
    private var size: Int = 20,
    private val maxLoadFactor: Double = 0.9,
    private var hashFunction: (K) -> Int
) {
    private var arrayOfBuckets = Array(size) { Bucket<K, V>() }
    private var numberOfConflicts = 0
    var numberOfEntries = 0
        private set

    var loadFactor = 0.0
        private set
        get() = numberOfEntries.toDouble() / size

    private val maxLengthOfListInConflictingBuckets: Int
        get() = arrayOfBuckets.filter { it.size > 1 }.maxBy { it.size }?.size ?: 0

    val fileParser = FileParser()

    /**
     * This only changes [size]
     * */
    private fun increaseSize() {
        size *= 2
    }

    private fun rebuild() {
        numberOfEntries = 0
        numberOfConflicts = 0
        val oldArrayOfBuckets = arrayOfBuckets
        arrayOfBuckets = Array(size) { Bucket<K, V>() }
        oldArrayOfBuckets.forEach { it ->
            it.listOfEntries.forEach {
                add(it.first, it.second)
            }
        }
    }

    private fun getIndexByHashFunction(key: K) = abs(hashFunction(key)) % size

    fun add(key: K, value: V): Boolean {
        val requiredBucketIndex = getIndexByHashFunction(key)
        val sizeBeforeAdding = arrayOfBuckets[requiredBucketIndex].size
        val isAdded = arrayOfBuckets[requiredBucketIndex].add(key, value)
        if (isAdded && sizeBeforeAdding != arrayOfBuckets[requiredBucketIndex].size) {
            numberOfEntries++
            if (arrayOfBuckets[requiredBucketIndex].size >= 2) {
                numberOfConflicts++
            }
        }

        if (loadFactor > maxLoadFactor) {
            increaseSize()
            rebuild()
        }
        return isAdded
    }

    fun remove(key: K): Boolean {
        val requiredBucketIndex = getIndexByHashFunction(key)
        val isDeleted = arrayOfBuckets[requiredBucketIndex].remove(key)
        if (isDeleted) {
            numberOfEntries--
            if (arrayOfBuckets[requiredBucketIndex].size >= 1) {
                numberOfConflicts--
            }
        }
        return isDeleted
    }

    /**
     * If nothing is found, null will be returned
     * */
    fun find(key: K): V? = arrayOfBuckets[getIndexByHashFunction(key)].getPairByKey(key)?.second

    /**
     * Functions that give a negative result may be accepted.
     * In this case, the absolute value will be taken.
     * */
    fun setHashFunction(hashFunction: (K) -> Int) {
        this.hashFunction = hashFunction
        rebuild()
    }

    fun printStatistics() {
        println("Hash table statistics:")
        println("Hash table size: $size")
        println("Total number of entries: $numberOfEntries")
        println("Load factor: $loadFactor")
        println("Number of conflicts: $numberOfConflicts")
        println("Maximum list length in conflicting buckets: $maxLengthOfListInConflictingBuckets")
    }

    fun isEmpty() = numberOfEntries == 0

    inner class FileParser {
        /**
         * This lambda function is needed to read entries from a file.
         * */
        var stringToKey: ((String) -> K)? = null

        /**
         * This lambda function is needed to read entries from a file.
         * */
        var stringToValue: ((String) -> V)? = null

        /**
         * This function reads entries of the form "key:value".
         * If entries are incorrect, an [IllegalStateException] will be thrown.
         * If functions [stringToKey] and [stringToKey] are not added,
         * [NullPointerException] will be thrown.
         * If the file is not found, an [FileNotFoundException] will be thrown
         * */
        fun fillFromFile(inputFile: File) {
            if (!inputFile.exists()) {
                throw FileNotFoundException("File \"${inputFile.path}\" not found.")
            }
            if (stringToKey == null) {
                throw NullPointerException("A function that translates a string to a K value is not initialized.")
            }
            if (stringToValue == null) {
                throw NullPointerException("A function that translates a string to a V value is not initialized.")
            }

            val regex = Regex("""\S+:\S+""")
            val inputFileStream = inputFile.inputStream()
            inputFileStream.bufferedReader().lines().forEach { it ->
                regex.findAll(it).forEach {
                    val entryAsPair = parseStringToEntry(it.value)
                    val key = entryAsPair.first
                    val value = entryAsPair.second
                    if (key != null && value != null) {
                        add(key, value)
                    }
                }
            }

            inputFileStream.close()
        }

        private fun parseStringToEntry(inputString: String): Pair<K?, V?> {
            val entryAsStringList = inputString.split(':')
            check(entryAsStringList.size == 2) { "The string is incorrect." }
            val keyAsString = entryAsStringList[0]
            val valueAsString = entryAsStringList[1]
            return Pair(stringToKey?.let { it(keyAsString) }, stringToValue?.let { it(valueAsString) })
        }
    }
}

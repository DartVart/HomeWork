package homeworks.homework4.task1

import homeworks.homework4.task1.hashFunctions.HashFunction
import java.io.File
import java.io.FileNotFoundException
import kotlin.math.abs

class HashTable<K, V>(
    private var size: Int = 20,
    private var hashFunction: HashFunction<K>,
    private val stringToKey: ((String) -> K),
    private val stringToValue: ((String) -> V),
    private val maxLoadFactor: Double = 0.9
) {
    private var arrayOfBuckets = Array(size) { Bucket<K, V>() }
    private var numberOfConflicts = 0
    var numberOfEntries = 0
        private set

    private val loadFactor: Double
        get() = numberOfEntries.toDouble() / size

    private val maxLengthOfListInConflictingBuckets: Int
        get() = arrayOfBuckets.map { it.size }.filter { it > 1 }.max() ?: 0

    val fileParser = FileParser(stringToKey, stringToValue)

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
                add(it.key, it.value)
            }
        }
    }

    private fun getIndexByHashFunction(key: K) = abs(hashFunction.getHash(key)) % size

    fun add(key: K, value: V): Boolean {
        val requiredBucketIndex = getIndexByHashFunction(key)
        val sizeBeforeAdding = arrayOfBuckets[requiredBucketIndex].size
        val isAdded = arrayOfBuckets[requiredBucketIndex].add(key, value)
        if (isAdded && sizeBeforeAdding != arrayOfBuckets[requiredBucketIndex].size) {
            numberOfEntries++
            if (arrayOfBuckets[requiredBucketIndex].size >= 2) {
                numberOfConflicts++
            }
            if (loadFactor > maxLoadFactor) {
                increaseSize()
                rebuild()
            }
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
    fun find(key: K): V? = arrayOfBuckets[getIndexByHashFunction(key)].getPairByKey(key)?.value

    /**
     * Functions that give a negative result may be accepted.
     * In this case, the absolute value will be taken.
     * */
    fun setHashFunction(hashFunction: HashFunction<K>) {
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

    inner class FileParser(private val stringToKey: ((String) -> K), private val stringToValue: ((String) -> V)) {

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

            val regex = Regex("""\S+:\S+""")
            val inputFileStream = inputFile.inputStream()
            inputFileStream.bufferedReader().lines().forEach { it ->
                regex.findAll(it).forEach {
                    val match = Regex("(.+):(.+)").find(it.value)
                    check(match != null) { "The string is incorrect" }
                    val (keyAsString, valueAsString) = match.destructured
                    add(stringToKey(keyAsString), stringToValue(valueAsString))
                }
            }
            inputFileStream.close()
        }
    }
}

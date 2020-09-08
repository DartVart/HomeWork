package homeworks.homework4.task1.hashFunctions

interface HashFunction<K> {
    fun getHash(key: K): Int
}

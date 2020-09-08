package homeworks.homework4.task1

class Bucket<K, V> {
    val listOfEntries = mutableListOf<HashTableEntry<K, V>>()

    val size: Int
        get() = listOfEntries.size

    fun getPairByKey(key: K) = listOfEntries.find { key == it.key }

    fun add(key: K, value: V): Boolean {
        val checkingPair = getPairByKey(key)
        return when {
            checkingPair == null -> {
                listOfEntries.add(HashTableEntry(key, value))
                true
            }
            checkingPair.value != value -> {
                checkingPair.value = value
                true
            }
            else -> false
        }
    }

    fun remove(key: K) = listOfEntries.removeIf { it.key == key }
}

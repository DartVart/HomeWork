package homeworks.homework4.task1

class Bucket<K, V> {
    val listOfEntries = mutableListOf<MutablePair<K, V>>()

    val size: Int
        get() = listOfEntries.size

    fun getPairByKey(key: K) = listOfEntries.find { key == it.first }

    fun add(key: K, value: V): Boolean {
        val checkingPair = getPairByKey(key)
        return when {
            checkingPair == null -> {
                listOfEntries.add(MutablePair(key, value))
                true
            }
            checkingPair.second != value -> {
                checkingPair.second = value
                true
            }
            else -> false
        }
    }

    fun remove(key: K) = listOfEntries.removeIf { it.first == key }
}

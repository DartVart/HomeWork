package homeworks.homework4.task1.hashFunctions

class SimpleHashFunction : HashFunction<String> {
    override fun getHash(key: String): Int {
        return key.fold(0) { total, currentChar ->
            total + currentChar.toInt()
        }
    }
}

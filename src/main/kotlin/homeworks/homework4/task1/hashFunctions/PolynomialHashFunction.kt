package homeworks.homework4.task1.hashFunctions

class PolynomialHashFunction : HashFunction<String> {
    companion object {
        const val POLYNOMIAL_HASH_MODULO = 2147483647
        const val PRIME_NUMBER = 17
    }

    override fun getHash(key: String): Int {
        var primeRaisedToCurrentPower = 1
        return key.fold(0) { total, currentChar ->
            primeRaisedToCurrentPower = (primeRaisedToCurrentPower * PRIME_NUMBER) % POLYNOMIAL_HASH_MODULO
            total + (currentChar.toInt() * primeRaisedToCurrentPower) % POLYNOMIAL_HASH_MODULO
        }
    }
}

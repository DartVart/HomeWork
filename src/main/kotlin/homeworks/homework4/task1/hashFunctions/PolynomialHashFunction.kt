package homeworks.homework4.task1.hashFunctions

/**
 * @param primeNumber is a number that will be raised to a power
 * */
class PolynomialHashFunction(private val hashModulo: Int = 2147483647, private val primeNumber: Int = 17) :
    HashFunction<String> {
    override fun getHash(key: String): Int {
        var primeRaisedToCurrentPower = 1
        return key.fold(0) { total, currentChar ->
            primeRaisedToCurrentPower = (primeRaisedToCurrentPower * primeNumber) % hashModulo
            total + (currentChar.toInt() * primeRaisedToCurrentPower) % hashModulo
        }
    }
}

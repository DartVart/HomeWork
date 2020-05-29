package tests.test2.task1

class IntComparator: Comparator<Int> {
    override fun compare(firstInteger: Int?, secondInteger: Int?): Int {
        if (firstInteger != null && secondInteger != null) {
            return when {
                firstInteger > secondInteger -> 1
                firstInteger < secondInteger -> -1
                else -> 0
            }
        } else {
            throw NullPointerException("null values cannot be compared")
        }
    }
}

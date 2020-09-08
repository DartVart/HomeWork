package tests.test2.task1

import org.junit.jupiter.api.Test

import org.junit.jupiter.api.Assertions.assertArrayEquals

class StringComparator : Comparator<String> {
    override fun compare(a: String?, b: String?): Int {
        if (a != null && b != null) {
            return when {
                a > b -> 1
                b < a -> -1
                else -> 0
            }
        } else {
            throw NullPointerException("null values cannot be compared")
        }
    }
}

internal class MainKtTest {
    val intComparator = IntComparator()
    val stringComparator = StringComparator()

    @Test
    fun bubbleSort_emptyIntArray_MustWork() {
        val actual = intArrayOf().toTypedArray()
        bubbleSort(actual, intComparator)
        assertArrayEquals(intArrayOf().toTypedArray(), actual)
    }

    @Test
    fun bubbleSort_simpleIntArray_MustWork() {
        val actual = intArrayOf(2, 5, 4).toTypedArray()
        bubbleSort(actual, intComparator)
        val expected = intArrayOf(2, 4, 5).toTypedArray()
        assertArrayEquals(expected, actual)
    }

    @Test
    fun bubbleSort_identicalElementsStringArray_MustWork() {
        val actual = Array(10) { "a" }
        bubbleSort(actual, stringComparator)
        val expected = Array(10) {"a"}
        assertArrayEquals(expected, actual)
    }

    @Test
    fun bubbleSort_singleElementStringArray_MustWork() {
        val actual = Array(1) { "a" }
        bubbleSort(actual, stringComparator)
        val expected = Array(1) { "a" }
        assertArrayEquals(expected, actual)
    }

    @Test
    fun bubbleSort_simpleStringArray_MustWork() {
        val actual = arrayOf("b", "c", "a")
        bubbleSort(actual, stringComparator)
        val expected =  arrayOf("a", "b", "c")
        assertArrayEquals(expected, actual)
    }
}

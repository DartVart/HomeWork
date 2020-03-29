package homeworks.homework1.task1

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions.assertIterableEquals
import org.junit.jupiter.api.Assertions.assertThrows
import java.lang.IndexOutOfBoundsException

internal class Task1KtTest {

    @Test
    fun changePartOfList_EmptyList_MustWork() {
        val expected: List<Int> = listOf()
        val actual: MutableList<Int> = mutableListOf()
        changePartOfList(0, 0, actual)
        assertIterableEquals(expected, actual)
    }

    @Test
    fun changePartOfList_SingleElementList_MustWork() {
        val expected: List<Int> = listOf(1)
        val actual: MutableList<Int> = mutableListOf(1)
        changePartOfList(1, 0, actual)
        assertIterableEquals(expected, actual)
    }

    @Test
    fun changePartOfList_SimpleList_MustWork() {
        val expected: List<Int> = listOf(9, 10, 6, 7, 8)
        val actual: MutableList<Int> = mutableListOf(6, 7, 8, 9, 10)
        changePartOfList(3, 2, actual)
        assertIterableEquals(expected, actual)
    }

    @Test
    fun changePartOfList_LargeList_MustWork() {
        val expected: MutableList<Int> = MutableList(4999) { it }
        expected.add(0, 4999)

        val actual: MutableList<Int> = MutableList(5000) { it }
        changePartOfList(4999, 1, actual)
        assertIterableEquals(expected, actual)
    }

    @Test
    fun changePartOfList_ZeroSizeOfFirstPart_MustWork() {
        val expected: List<Int> = listOf(1, 2, 3, 4, 5)
        val actual: MutableList<Int> = mutableListOf(1, 2, 3, 4, 5)
        changePartOfList(0, 5, actual)
        assertIterableEquals(expected, actual)
    }

    @Test
    fun changePartOfList_ZeroSizeOfSecondPart_MustWork() {
        val expected: List<Int> = listOf(1, 2, 3, 4, 5)
        val actual: MutableList<Int> = mutableListOf(1, 2, 3, 4, 5)
        changePartOfList(5, 0, actual)
        assertIterableEquals(expected, actual)
    }

    @Test
    fun changePartOfList_SumOfPartsIsBiggerThanListSize_ThrowsException() {
        val actual: MutableList<Int> = mutableListOf(1, 2, 3, 4, 5)
        assertThrows(IndexOutOfBoundsException::class.java) {
            changePartOfList(3, 4, actual)
        }
    }

    @Test
    fun changePartOfList_FirstPartLengthLessThanZero_ThrowsException() {
        val actual: MutableList<Int> = mutableListOf(5, 6, 7, 8, 9)
        assertThrows(IndexOutOfBoundsException::class.java) {
            changePartOfList(-1, 1, actual)
        }
    }

    @Test
    fun changePartOfList_SecondPartLengthLessThanZero_ThrowsException() {
        val actual: MutableList<Int> = mutableListOf(5, 6, 7, 8, 9)
        assertThrows(IndexOutOfBoundsException::class.java) {
            changePartOfList(1, -1, actual)
        }
    }
}

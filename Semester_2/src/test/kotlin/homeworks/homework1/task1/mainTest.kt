package homeworks.homework1.task1

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions.assertIterableEquals
import org.junit.jupiter.api.Assertions.assertThrows
import java.lang.IllegalArgumentException

internal class Task1KtTest {

    @Test
    fun changePartsOfList_EmptyList_MustWork() {
        val expected: List<Int> = listOf()
        val actual: MutableList<Int> = mutableListOf()
        changePartsOfList(0, 0, actual)
        assertIterableEquals(expected, actual)
    }

    @Test
    fun changePartsOfList_SingleElementList_MustWork() {
        val expected: List<Int> = listOf(1)
        val actual: MutableList<Int> = mutableListOf(1)
        changePartsOfList(1, 0, actual)
        assertIterableEquals(expected, actual)
    }

    @Test
    fun changePartsOfList_SimpleList_MustWork() {
        val expected: List<Int> = listOf(9, 10, 6, 7, 8)
        val actual: MutableList<Int> = mutableListOf(6, 7, 8, 9, 10)
        changePartsOfList(3, 2, actual)
        assertIterableEquals(expected, actual)
    }

    @Test
    fun changePartsOfList_LargeList_MustWork() {
        val expected: MutableList<Int> = MutableList(4999) { it }
        expected.add(0, 4999)

        val actual: MutableList<Int> = MutableList(5000) { it }
        changePartsOfList(4999, 1, actual)
        assertIterableEquals(expected, actual)
    }

    @Test
    fun changePartsOfList_ZeroSizeOfFirstPart_MustWork() {
        val expected: List<Int> = listOf(1, 2, 3, 4, 5)
        val actual: MutableList<Int> = mutableListOf(1, 2, 3, 4, 5)
        changePartsOfList(0, 5, actual)
        assertIterableEquals(expected, actual)
    }

    @Test
    fun changePartsOfList_ZeroSizeOfSecondPart_MustWork() {
        val expected: List<Int> = listOf(1, 2, 3, 4, 5)
        val actual: MutableList<Int> = mutableListOf(1, 2, 3, 4, 5)
        changePartsOfList(5, 0, actual)
        assertIterableEquals(expected, actual)
    }

    @Test
    fun changePartsOfList_SumOfPartsIsBiggerThanListSize_ThrowsException() {
        val actual: MutableList<Int> = mutableListOf(1, 2, 3, 4, 5)
        assertThrows(IllegalArgumentException::class.java) {
            changePartsOfList(3, 4, actual)
        }
    }
}

package homeworks.homework6.task1

import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import org.junit.jupiter.api.Assertions.assertIterableEquals
import org.junit.jupiter.api.Test
import kotlin.random.Random

internal class MainKtTest {
    @Test
    fun asyncQuickSorting_SimpleList_MustWork() {
        val expected: List<Int> = listOf(0, 1, 1, 2, 3, 3, 4, 7, 8)
        val actual: MutableList<Int> = mutableListOf(4, 3, 1, 3, 2, 1, 8, 0, 7)
        runBlocking {
            launch {
                asyncQuickSort(actual)
            }
        }
        assertIterableEquals(expected, actual)
    }

    @Test
    fun asyncQuickSorting_StringList_MustWork() {
        val actual: MutableList<String> = mutableListOf("John", "Marina", "Victor", "Elena", "Mark")
        val expected: List<String> = mutableListOf("Elena", "John", "Marina", "Mark", "Victor")
        runBlocking {
            launch {
                asyncQuickSort(actual)
            }
        }
        assertIterableEquals(expected, actual)
    }

    @Test
    fun asyncQuickSorting_DoubleList_MustWork() {
        val actual: MutableList<Double> = MutableList(1000) { Random.nextDouble(-1.0, 1.0) }
        val expected: List<Double> = actual.sorted()
        runBlocking {
            launch {
                asyncQuickSort(actual)
            }
        }
        assertIterableEquals(expected, actual)
    }

    @Test
    fun asyncQuickSorting_ListWithIncreasingElements_MustWork() {
        val actual: MutableList<Int> = MutableList(1000) { it * 2 }

        // asyncQuickSorting will leave elements in ascending order.
        val expected: List<Int> = actual.toMutableList()
        runBlocking {
            launch {
                asyncQuickSort(actual)
            }
        }
        assertIterableEquals(expected, actual)
    }

    @Test
    fun asyncQuickSorting_ListWithDecreasingElements_MustWork() {
        val actual: MutableList<Int> = MutableList(1000) { 1000 - it }

        // asyncQuickSorting should sort elements in ascending order
        val expected: List<Int> = actual.reversed()
        runBlocking {
            launch {
                asyncQuickSort(actual)
            }
        }
        assertIterableEquals(expected, actual)
    }

    @Test
    fun asyncQuickSorting_SingleElementList_MustWork() {
        val actual: MutableList<Int> = mutableListOf(2)
        val expected: List<Int> = mutableListOf(2)
        runBlocking {
            launch {
                asyncQuickSort(actual)
            }
        }
        assertIterableEquals(expected, actual)
    }

    @Test
    fun asyncQuickSorting_EmptyList_MustWork() {
        val actual: MutableList<Int> = mutableListOf()
        val expected: List<Int> = mutableListOf()
        runBlocking {
            launch {
                asyncQuickSort(actual)
            }
        }
        assertIterableEquals(expected, actual)
    }

    @Test
    fun asyncQuickSorting_ListWithIdenticalElements_MustWork() {
        val actual: MutableList<Int> = MutableList(100) { 1 }
        val expected: List<Int> = MutableList(100) { 1 }
        runBlocking {
            launch {
                asyncQuickSort(actual)
            }
        }
        assertIterableEquals(expected, actual)
    }

    @Test
    fun asyncQuickSorting_BigList_MustWork() {
        val actual: MutableList<Int> = MutableList(1000000) { Random.nextInt(-1000, 1000) }
        val expected: List<Int> = actual.sorted()
        runBlocking {
            launch {
                asyncQuickSort(actual)
            }
        }
        assertIterableEquals(expected, actual)
    }
}

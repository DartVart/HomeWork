package homeworks.homework2.task2

import org.junit.jupiter.api.Assertions.assertArrayEquals
import org.junit.jupiter.api.Test

/**
 * Implementation of a class having overridden [equals] functions and, accordingly, [hashCode].
 * The comparison takes place directly by [comparisonValue].
 * */
class SomeEqualityOverridingClass(private val comparisonValue: Int) {
    override fun equals(other: Any?): Boolean {
        return if (other != null && other is SomeEqualityOverridingClass) {
            comparisonValue == other.comparisonValue
        } else {
            false
        }
    }

    override fun hashCode(): Int {
        return comparisonValue
    }
}

internal class Test1KtTest {
    @Test
    fun getArrayWithoutDuplicateItems_IntegerArray_MustWork() {
        val expected: Array<Int> = arrayOf(3, 2, 1)
        var actual: Array<Int> = arrayOf(2, 1, 3, 2, 1, 2, 1)
        actual = getArrayWithoutDuplicateItems(actual)
        assertArrayEquals(expected, actual)
    }

    @Test
    fun getArrayWithoutDuplicateItems_StringArray_MustWork() {
        val expected: Array<String> = arrayOf("XV", "BOB", "A", "DOK")
        var actual: Array<String> = arrayOf("A", "BOB", "BOB", "XV", "A", "BOB", "DOK", "A", "DOK")
        actual = getArrayWithoutDuplicateItems(actual)
        assertArrayEquals(expected, actual)
    }

    @Test
    fun getArrayWithoutDuplicateItems_DoubleArray_MustWork() {
        val expected: Array<Double> = arrayOf(-10.0, 1.24, 1.3)
        var actual: Array<Double> = arrayOf(1.24, 1.3, 1.3, -10.0, 1.24, 1.3)
        actual = getArrayWithoutDuplicateItems(actual)
        assertArrayEquals(expected, actual)
    }

    @Test
    fun getArrayWithoutDuplicateItems_BooleanArray_MustWork() {
        val expected: Array<Boolean> = arrayOf(true, false)
        var actual: Array<Boolean> = arrayOf(true, true, false, true, false, false)
        actual = getArrayWithoutDuplicateItems(actual)
        assertArrayEquals(expected, actual)
    }

    @Test
    fun getArrayWithoutDuplicateItems_SomeEqualityOverridingClass_MustWork() {
        val classA = SomeEqualityOverridingClass(0)
        val classB = SomeEqualityOverridingClass(-2)

        // The following two classes are equal, since their comparisonValues ​​are equal
        val classC1 = SomeEqualityOverridingClass(1)
        val classC2 = SomeEqualityOverridingClass(1)

        val expected: Array<SomeEqualityOverridingClass> = arrayOf(classA, classC1, classB)
        var actual: Array<SomeEqualityOverridingClass> =
            arrayOf(classC2, classA, classC1, classA, classB, classC2, classB)

        actual = getArrayWithoutDuplicateItems(actual)
        assertArrayEquals(expected, actual)
    }

    @Test
    fun getArrayWithoutDuplicateItems_EmptyArray_MustWork() {
        val expected: Array<Any> = arrayOf()
        var actual: Array<Any> = arrayOf()
        actual = getArrayWithoutDuplicateItems(actual)
        assertArrayEquals(expected, actual)
    }

    @Test
    fun getArrayWithoutDuplicateItems_SingleElementArray_MustWork() {
        val expected: Array<Int> = arrayOf(1)
        var actual: Array<Int> = arrayOf(1)
        actual = getArrayWithoutDuplicateItems(actual)
        assertArrayEquals(expected, actual)
    }

    @Test
    fun getArrayWithoutDuplicateItems_ArrayWithSingleRepeatingItem_MustWork() {
        val expected: Array<Int> = arrayOf(2)
        var actual: Array<Int> = arrayOf(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2)
        actual = getArrayWithoutDuplicateItems(actual)
        assertArrayEquals(expected, actual)
    }

    @Test
    fun getArrayWithoutDuplicateItems_LargeArray_MustWork() {
        val expected: Array<Int> = arrayOf(0, 1)
        var actual: Array<Int> = Array(5000) { it % 2 }
        actual = getArrayWithoutDuplicateItems(actual)
        assertArrayEquals(expected, actual)
    }
}

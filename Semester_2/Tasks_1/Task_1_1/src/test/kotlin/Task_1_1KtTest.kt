import org.junit.jupiter.api.*
import org.junit.jupiter.api.Assertions.assertArrayEquals

internal class Task_1_1KtTest {

    @Nested
    inner class Check_ReversePartOfArray {

        @Test
        fun SimpleArray1_MustWork() {
            val expected: Array<Int> = arrayOf(0, 5, 4, 3, 2, 1)
            val actual: Array<Int> = arrayOf(0, 1, 2, 3, 4, 5)
            reversePartOfArray(1, 5, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun SimpleArray2_MustWork() {
            val expected: Array<Int> = arrayOf(4, 5, 3, 2, 1)
            val actual: Array<Int> = arrayOf(5, 4, 3, 2, 1)
            reversePartOfArray(0, 1, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun SingleElementArray_MustWork() {
            val expected: Array<Int> = arrayOf(9)
            val actual: Array<Int> = arrayOf(9)
            reversePartOfArray(0, 0, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun EmptyArray_MustWork() {
            val expected: Array<Int> = arrayOf()
            val actual: Array<Int> = arrayOf()
            reversePartOfArray(0, 0, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun EndIndexBiggerThanSize_MustWork() {
            val expected: Array<Int> = arrayOf(1, 2, 5, 4, 3)
            val actual: Array<Int> = arrayOf(1, 2, 3, 4, 5)
            reversePartOfArray(2, 10, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun StartIndexLessThanZero_MustWork() {
            val expected: Array<Int> = arrayOf(3, 2, 1, 4, 5)
            val actual: Array<Int> = arrayOf(1, 2, 3, 4, 5)
            reversePartOfArray(-10, 2, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun EndIndexLessThanStart_MustWork() {
            val expected: Array<Int> = arrayOf(0, 2, 3, 1)
            val actual: Array<Int> = arrayOf(0, 2, 3, 1)
            reversePartOfArray(3, 2, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun EndIndexLessThanZero_MustWork() {
            val expected: Array<Int> = arrayOf(5, 4, 3, 2)
            val actual: Array<Int> = arrayOf(5, 4, 3, 2)
            reversePartOfArray(0, -9, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun StartIndexBiggerThanSize_MustWork() {
            val expected: Array<Int> = arrayOf(5, 4, 3, 2)
            val actual: Array<Int> = arrayOf(5, 4, 3, 2)
            reversePartOfArray(100, 3, actual)
            assertArrayEquals(expected, actual)
        }

    }

    @Nested
    inner class Check_ChangePartOfArray {
        @Test
        fun EmptyArray_MustWork() {
            val expected: Array<Int> = arrayOf()
            val actual: Array<Int> = arrayOf()
            changePartOfArray(0, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun SingleElementArray_MustWork() {
            val expected: Array<Int> = arrayOf(1)
            val actual: Array<Int> = arrayOf(1)
            changePartOfArray(1, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun PartLengthMoreThanSize_MustWork() {
            val expected: Array<Int> = arrayOf(1, 2, 3, 4, 5)
            val actual: Array<Int> = arrayOf(1, 2, 3, 4, 5)
            changePartOfArray(100, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun PartLengthLessThanZero_MustWork() {
            val expected: Array<Int> = arrayOf(6, 7, 8, 9)
            val actual: Array<Int> = arrayOf(6, 7, 8, 9)
            changePartOfArray(-1, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun SimpleArray1_MustWork() {
            val expected: Array<Int> = arrayOf(9, 10, 6, 7, 8)
            val actual: Array<Int> = arrayOf(6, 7, 8, 9, 10)
            changePartOfArray(3, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun SimpleArray2_MustWork() {
            val expected: Array<Int> = arrayOf(5, 1, 2, 3, 4)
            val actual: Array<Int> = arrayOf(1, 2, 3, 4, 5)
            changePartOfArray(4, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun PartLengthIsEqualToSize_MustWork() {
            val expected: Array<Int> = arrayOf(1, 2, 3, 4, 5)
            val actual: Array<Int> = arrayOf(1, 2, 3, 4, 5)
            changePartOfArray(5, actual)
            assertArrayEquals(expected, actual)
        }
    }
}
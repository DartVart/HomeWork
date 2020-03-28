package homeworks.homework1.task1

import org.junit.jupiter.api.*
import org.junit.jupiter.api.Assertions.assertArrayEquals

internal class Task1KtTest {

    @Nested
    inner class Check_ReversePartOfArray {

        @Test
        fun SimpleArray1_MustWork() {
            val expected: IntArray = intArrayOf(0, 5, 4, 3, 2, 1)
            val actual: IntArray = intArrayOf(0, 1, 2, 3, 4, 5)
            reversePartOfArray(1, 5, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun SimpleArray2_MustWork() {
            val expected: IntArray = intArrayOf(4, 5, 3, 2, 1)
            val actual:IntArray = intArrayOf(5, 4, 3, 2, 1)
            reversePartOfArray(0, 1, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun SingleElementArray_MustWork() {
            val expected:IntArray = intArrayOf(9)
            val actual: IntArray = intArrayOf(9)
            reversePartOfArray(0, 0, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun EmptyArray_MustWork() {
            val expected: IntArray = intArrayOf()
            val actual:IntArray = intArrayOf()
            reversePartOfArray(0, 0, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun EndIndexBiggerThanSize_MustWork() {
            val expected: IntArray = intArrayOf(1, 2, 5, 4, 3)
            val actual: IntArray = intArrayOf(1, 2, 3, 4, 5)
            reversePartOfArray(2, 10, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun StartIndexLessThanZero_MustWork() {
            val expected: IntArray = intArrayOf(3, 2, 1, 4, 5)
            val actual: IntArray = intArrayOf(1, 2, 3, 4, 5)
            reversePartOfArray(-10, 2, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun EndIndexLessThanStart_MustWork() {
            val expected: IntArray = intArrayOf(0, 2, 3, 1)
            val actual: IntArray = intArrayOf(0, 2, 3, 1)
            reversePartOfArray(3, 2, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun EndIndexLessThanZero_MustWork() {
            val expected: IntArray = intArrayOf(5, 4, 3, 2)
            val actual: IntArray = intArrayOf(5, 4, 3, 2)
            reversePartOfArray(0, -9, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun StartIndexBiggerThanSize_MustWork() {
            val expected: IntArray = intArrayOf(5, 4, 3, 2)
            val actual: IntArray = intArrayOf(5, 4, 3, 2)
            reversePartOfArray(100, 3, actual)
            assertArrayEquals(expected, actual)
        }

    }

    @Nested
    inner class Check_ChangePartOfArray {
        @Test
        fun EmptyArray_MustWork() {
            val expected: IntArray = intArrayOf()
            val actual: IntArray = intArrayOf()
            changePartOfArray(0, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun SingleElementArray_MustWork() {
            val expected: IntArray = intArrayOf(1)
            val actual: IntArray = intArrayOf(1)
            changePartOfArray(1, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun PartLengthMoreThanSize_MustWork() {
            val expected: IntArray = intArrayOf(1, 2, 3, 4, 5)
            val actual: IntArray = intArrayOf(1, 2, 3, 4, 5)
            changePartOfArray(100, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun PartLengthLessThanZero_MustWork() {
            val expected: IntArray = intArrayOf(6, 7, 8, 9)
            val actual: IntArray = intArrayOf(6, 7, 8, 9)
            changePartOfArray(-1, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun SimpleArray1_MustWork() {
            val expected: IntArray = intArrayOf(9, 10, 6, 7, 8)
            val actual: IntArray = intArrayOf(6, 7, 8, 9, 10)
            changePartOfArray(3, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun SimpleArray2_MustWork() {
            val expected: IntArray = intArrayOf(5, 1, 2, 3, 4)
            val actual: IntArray = intArrayOf(1, 2, 3, 4, 5)
            changePartOfArray(4, actual)
            assertArrayEquals(expected, actual)
        }

        @Test
        fun PartLengthIsEqualToSize_MustWork() {
            val expected: IntArray = intArrayOf(1, 2, 3, 4, 5)
            val actual: IntArray = intArrayOf(1, 2, 3, 4, 5)
            changePartOfArray(5, actual)
            assertArrayEquals(expected, actual)
        }
    }
}
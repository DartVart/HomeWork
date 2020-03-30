package homeworks.homework1.task2

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertThrows

internal class Task2KtTest {

    @Nested
    inner class Check_GetRecursiveFactorial {
        @Test
        fun factorialOfNumber0_MustWork() {
            assertEquals(1, getRecursiveFactorial(0))
        }

        @Test
        fun factorialOfNumber1_MustWork() {
            assertEquals(1, getRecursiveFactorial(1))
        }

        @Test
        fun factorialOfNumber2_MustWork() {
            assertEquals(2, getRecursiveFactorial(2))
        }

        @Test
        fun factorialOfNumber3_MustWork() {
            assertEquals(6, getRecursiveFactorial(3))
        }

        @Test
        fun factorialOfNumber5_MustWork() {
            assertEquals(120, getRecursiveFactorial(5))
        }

        @Test
        fun factorialOfNumber12_MustWork() {
            assertEquals(479001600, getRecursiveFactorial(12))
        }

        @Test
        fun factorialOfNonPositive_ThrowsException() {
            assertThrows(IllegalArgumentException::class.java) { getRecursiveFactorial(-1) }
        }
    }

    @Nested
    inner class Check_GetIterativeFactorial {

        @Test
        fun factorialOfNumber0_MustWork() {
            assertEquals(1, getIterativeFactorial(0))
        }

        @Test
        fun factorialOfNumber1_MustWork() {
            assertEquals(1, getIterativeFactorial(1))
        }

        @Test
        fun factorialOfNumber2_MustWork() {
            assertEquals(2, getIterativeFactorial(2))
        }

        @Test
        fun factorialOfNumber3_MustWork() {
            assertEquals(6, getIterativeFactorial(3))
        }

        @Test
        fun factorialOfNumber5_MustWork() {
            assertEquals(120, getIterativeFactorial(5))
        }

        @Test
        fun factorialOfNumber12_MustWork() {
            assertEquals(479001600, getIterativeFactorial(12))
        }

        @Test
        fun factorialOfNonPositive_ThrowsException() {
            assertThrows(IllegalArgumentException::class.java) { getRecursiveFactorial(-1) }
        }
    }
}

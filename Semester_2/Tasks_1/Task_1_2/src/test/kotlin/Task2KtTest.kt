import org.junit.jupiter.api.*
import org.junit.jupiter.api.Assertions.*

internal class Task2KtTest {

    @Nested
    inner class Check_getRecursiveFactorial {
        @Test
        fun FactorialOfZero_MustWork() {
            assertEquals(1, getRecursiveFactorial(0))
        }

        @Test
        fun FactorialOfNumber1_MustWork() {
            assertEquals(1, getRecursiveFactorial(1))
        }

        @Test
        fun FactorialOfNumber2_MustWork() {
            assertEquals(2, getRecursiveFactorial(2))
        }

        @Test
        fun FactorialOfNumber5_MustWork() {
            assertEquals(120, getRecursiveFactorial(5))
        }

        @Test
        fun FactorialOfNonPositive1_ThrowsExeption() {
            assertThrows(IllegalArgumentException::class.java) { getRecursiveFactorial(-1) }
        }

        @Test
        fun FactorialOfNonPositive2_ThrowsExeption() {
            assertThrows(IllegalArgumentException::class.java) { getRecursiveFactorial(-100) }
        }
    }

    @Nested
    inner class Check_getIterativeFactorial {

        @Test
        fun FactorialOfZero_MustWork() {
            assertEquals(1, getIterativeFactorial(0))
        }

        @Test
        fun FactorialOfNumber1_MustWork() {
            assertEquals(1, getIterativeFactorial(1))
        }

        @Test
        fun FactorialOfNumber2_MustWork() {
            assertEquals(2, getIterativeFactorial(2))
        }

        @Test
        fun FactorialOfNumber5_MustWork() {
            assertEquals(120, getIterativeFactorial(5))
        }

        @Test
        fun FactorialOfNonPositive1_ThrowsExeption() {
            assertThrows(IllegalArgumentException::class.java) { getRecursiveFactorial(-1) }
        }

        @Test
        fun FactorialOfNonPositive2_ThrowsExeption() {
            assertThrows(IllegalArgumentException::class.java) { getRecursiveFactorial(-100) }
        }
    }
}
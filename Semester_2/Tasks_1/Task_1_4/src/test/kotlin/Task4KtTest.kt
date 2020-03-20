import org.junit.jupiter.api.Assertions.*
import org.junit.jupiter.api.Test

internal class Task4KtTest {

    @Test
    fun IsPalindrome_StringWithOddLength_MustWork() {
        assertEquals(true, isPalindrome("asdsa"))
    }

    @Test
    fun IsPalindrome_StringWithEvenLength_MustWork() {
        assertEquals(true, isPalindrome("asddsa"))
    }

    @Test
    fun IsPalindrome_NonLetterCharacters_MustWork() {
        assertEquals(true, isPalindrome("_ _*_ _"))
    }

    @Test
    fun IsPalindrome_OneCharacter_MustWork() {
        assertEquals(true, isPalindrome("!"))
    }

    @Test
    fun IsPalindrome_SrtingInRussian_MustWork() {
        assertEquals(true, isPalindrome("шалаш"))
    }

    @Test
    fun IsPalindrome_DifferentRegisters_MustWork() {
        assertEquals(false, isPalindrome("ШаЛАш"))
    }

    @Test
    fun IsPalindrome_EmptyString_MustWork() {
        assertEquals(true, isPalindrome(""))
    }


    @Test
    fun IsPalindrome_BlankString_MustWork() {
        assertEquals(true, isPalindrome("     "))
    }

    @Test
    fun IsPalindrome_NonPalindromeString1_MustWork() {
        assertEquals(false, isPalindrome("123456789"))
    }

    @Test
    fun IsPalindrome_NonPalindromeString2_MustWork() {
        assertEquals(false, isPalindrome("jjjKjj"))
    }

    @Test
    fun IsPalindrome_NonPalindromeString3_MustWork() {
        assertEquals(false, isPalindrome("AAABaAA"))
    }
}
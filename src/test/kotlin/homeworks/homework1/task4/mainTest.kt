package homeworks.homework1.task4

import org.junit.jupiter.api.Assertions.assertFalse
import org.junit.jupiter.api.Test

internal class Task4KtTest {

    @Test
    fun isPalindrome_StringWithOddLength_MustWork() {
        assert(isPalindrome("repaper"))
    }

    @Test
    fun isPalindrome_StringWithEvenLength_MustWork() {
        assert(isPalindrome("-|--|-"))
    }

    @Test
    fun isPalindrome_CharactersWithoutGraphicRepresentation_MustWork() {
        assert(isPalindrome("\n\t\r\t\n"))
    }

    @Test
    fun isPalindrome_OneCharacter_MustWork() {
        assert(isPalindrome("!"))
    }

    @Test
    fun isPalindrome_StringInRussian_MustWork() {
        assert(isPalindrome("шалаш"))
    }

    @Test
    fun isPalindrome_SimilarEnglishAndRussianCharacters_MustWork() {
        assertFalse(isPalindrome("OAАО")) // The first two letters are English, the second ones are Russian
    }

    @Test
    fun isPalindrome_DifferentRegisters_MustWork() {
        assertFalse(isPalindrome("MadAm"))
    }

    @Test
    fun isPalindrome_EmptyString_MustWork() {
        assert(isPalindrome(""))
    }

    @Test
    fun isPalindrome_BlankString_MustWork() {
        assert(isPalindrome("           "))
    }

    @Test
    fun isPalindrome_NonPalindromeString1_MustWork() {
        assertFalse(isPalindrome("123456789"))
    }

    @Test
    fun isPalindrome_NonPalindromeString2_MustWork() {
        assertFalse(isPalindrome("jjjKjj"))
    }

    @Test
    fun isPalindrome_NonPalindromeString3_MustWork() {
        assertFalse(isPalindrome("AAABaAA"))
    }
}

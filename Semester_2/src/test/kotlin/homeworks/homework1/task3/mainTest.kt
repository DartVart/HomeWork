package homeworks.homework1.task3

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertThrows
import java.lang.IllegalArgumentException

internal class MainTest {

    @Test
    fun getNumberOfSubstrings_StringContainsSubstring1_MustWork() {
        assertEquals(3, getNumberOfSubstrings("QweQweQw eQ we", "we"))
    }

    @Test
    fun getNumberOfSubstrings_StringContainsSubstring2_MustWork() {
        assertEquals(5, getNumberOfSubstrings("aaaaaa", "aa"))
    }

    @Test
    fun getNumberOfSubstrings_StringContainsSubstring3_MustWork() {
        assertEquals(2, getNumberOfSubstrings("\n n nn \n\t \\n", "\n"))
    }

    @Test
    fun getNumberOfSubstrings_SubstringInRussian_MustWork() {
        assertEquals(2, getNumberOfSubstrings("some text. Ночь; --[Ночь]--", "Ночь"))
    }

    @Test
    fun getNumberOfSubstrings_BlankStringAndSubstring_MustWork() {
        assertEquals(3, getNumberOfSubstrings("    ", "  "))
    }

    @Test
    fun getNumberOfSubstrings_StringDoesNotContainSubstring1_MustWork() {
        assertEquals(0, getNumberOfSubstrings("asdfasdf", "ff"))
    }

    @Test
    fun getNumberOfSubstrings_StringDoesNotContainSubstring2_MustWork() {
        assertEquals(0, getNumberOfSubstrings("asdfasdf", " "))
    }

    @Test
    fun getNumberOfSubstrings_EmptySourceString_MustWork() {
        assertEquals(0, getNumberOfSubstrings("", "?"))
    }

    @Test
    fun getNumberOfSubstrings_EmptySubstring1_ThrowsException() {
        assertThrows(IllegalArgumentException::class.java) { getNumberOfSubstrings("some string", "") }
    }
}

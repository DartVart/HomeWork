import org.junit.jupiter.api.Test

import org.junit.jupiter.api.Assertions.*

internal class Task3KtTest {

    @Test
    fun getNumberOfSubstrings_StringContainsSubstring1_MustWork() {
        assertEquals(3, getNumberOfSubstrings("qweqweqw eq we", "we"))
    }

    @Test
    fun getNumberOfSubstrings_StringContainsSubstring2_MustWork() {
        assertEquals(5, getNumberOfSubstrings("aaaaaa", "aa"))
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
        assertEquals(0, getNumberOfSubstrings("asdfasdf", "adsff"))
    }

    @Test
    fun getNumberOfSubstrings_StringDoesNotContainSubstring2_MustWork() {
        assertEquals(0, getNumberOfSubstrings("asdfasdf", "-"))
    }

    @Test
    fun getNumberOfSubstrings_EmptySourceString_MustWork() {
        assertEquals(0, getNumberOfSubstrings("", "?"))
    }
}
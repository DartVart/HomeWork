package homeworks.homework2.task1

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Test

internal class Test1KtTest {

    @Test
    fun countCharactersToBeDeleted_FirstStringDoesNotContainXXX_MustWork() {
        assertEquals(0, countCharactersToBeDeleted("vx xv ff ff xx  x xx axxcx "))
    }

    @Test
    fun countCharactersToBeDeleted_SecondStringDoesNotContainX_MustWork() {
        assertEquals(0, countCharactersToBeDeleted("kk ll af aff fffaaa"))
    }

    @Test
    fun countCharactersToBeDeleted_XInUpperCase_MustWork() {
        assertEquals(1, countCharactersToBeDeleted("xxXXX xxx x XxXx"))
    }

    @Test
    fun countCharactersToBeDeleted_SimpleStringContainsXXX_MustWork() {
        assertEquals(10, countCharactersToBeDeleted("xxxxxffxxxgx xxx xxxx xxxxx x"))
    }

    @Test
    fun countCharactersToBeDeleted_StringConsistingOnlyOfX_MustWork() {
        assertEquals(7, countCharactersToBeDeleted("xxxxxxxxx"))
    }

    @Test
    fun countCharactersToBeDeleted_BlankString_MustWork() {
        assertEquals(0, countCharactersToBeDeleted("      "))
    }

    @Test
    fun countCharactersToBeDeleted_EmptyString_MustWork() {
        assertEquals(0, countCharactersToBeDeleted(""))
    }
}
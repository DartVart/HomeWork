import org.junit.jupiter.api.Assertions.*
import org.junit.jupiter.api.Test

internal class Test1KtTest {

    @Test
    fun CountCharactersToBeDeleted_FirstStringDoesNotContainXXX_MustWork() {
        assertEquals(0, countCharactersToBeDeleted("vx xv ff ff xx  x xx axxcx "))
    }

    @Test
    fun CountCharactersToBeDeleted_SecondStringDoesNotContainXXX_MustWork() {
        assertEquals(0, countCharactersToBeDeleted("kk ll af aff fffaaa"))
    }

    @Test
    fun CountCharactersToBeDeleted_xWithUpperCase_MustWork() {
        assertEquals(1, countCharactersToBeDeleted("xxXXX xxx x XxXx"))
    }

    @Test
    fun CountCharactersToBeDeleted_FirstStringContainsXXX_MustWork() {
        assertEquals(10, countCharactersToBeDeleted("xxxxxffxxxgx xxx xxxx xxxxx x"))
    }

    @Test
    fun CountCharactersToBeDeleted_SecondStringContainsXXX_MustWork() {
        assertEquals(7, countCharactersToBeDeleted("xxxxxxxxx"))
    }

    @Test
    fun CountCharactersToBeDeleted_BlankString_MustWork() {
        assertEquals(0, countCharactersToBeDeleted("      "))
    }

    @Test
    fun CountCharactersToBeDeleted_EmptyString_MustWork() {
        assertEquals(0, countCharactersToBeDeleted(""))
    }
}
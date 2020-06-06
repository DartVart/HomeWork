package homeworks.homework5.task1

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertThrows
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Assertions.assertFalse
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Test
import java.io.ByteArrayInputStream
import java.io.File
import java.io.FileOutputStream
import java.io.IOException

internal class TrieTest {
    private val pathToFolderWithTextFiles = "./src/test/resources/homeworks/homework5/task1"
    private val emptyTrie = Trie()
    fun getBigTrie(): Trie {
        val trie = Trie()
        for (i in 1..10000) {
            trie.add(i.toString())
        }
        return trie
    }

    @Nested
    inner class Check_add {
        private val trieAfterAddWithSamePrefix = Trie()

        init {
            trieAfterAddWithSamePrefix.add("a")
            trieAfterAddWithSamePrefix.add("ab")
            trieAfterAddWithSamePrefix.add("abc")
            trieAfterAddWithSamePrefix.add("abcd")
        }

        @Test
        fun simpleAdding_CheckingValue_MustWork() {
            val trie = Trie()
            trie.add("abc")
            trie.add("cab")
            trie.add("bca")
            assertTrue(trie.contains("cab"))
        }

        @Test
        fun simpleAdding_CheckingSize_MustWork() {
            val trie = Trie()
            trie.add("abc")
            trie.add("cab")
            trie.add("bca")
            assertEquals(3, trie.numberOfWords)
        }

        @Test
        fun addingWithSamePrefix_CheckSize_MustWork() {
            assertEquals(4, trieAfterAddWithSamePrefix.numberOfWords)
        }

        @Test
        fun addingWithSamePrefix_CheckValue1_MustWork() {
            assertTrue(trieAfterAddWithSamePrefix.contains("a"))
        }

        @Test
        fun addingWithSamePrefix_CheckValue2_MustWork() {
            assertTrue(trieAfterAddWithSamePrefix.contains("abc"))
        }

        @Test
        fun addingSameElements_MustWork() {
            val trie = Trie()
            trie.add("night")
            trie.add("night")
            trie.add("night")
            trie.add("night")
            assertEquals(1, trie.numberOfWords)
        }

        @Test
        fun checkResultOfAdding_containsElement_MustWork() {
            val trie = getBigTrie()
            assertTrue(trie.add("parker"))
        }

        @Test
        fun checkResultOfAdding_DoesNotContainsElement_MustWork() {
            val trie = getBigTrie()
            assertFalse(trie.add("300"))
        }
    }

    @Nested
    inner class Check_remove {
        @Test
        fun emptyTrie_MustWork() {
            val trie = Trie()
            trie.remove("0")
            assertEquals(emptyTrie, trie)
        }

        @Test
        fun simpleRemoving_MustWork() {
            val actual = Trie()
            actual.add("abc")
            actual.add("cab")
            actual.add("bca")
            actual.remove("cab")
            actual.remove("abc")
            val expected = Trie()
            expected.add("bca")
            assertEquals(expected, actual)
        }

        @Test
        fun removingElementThatIsSomeonePrefix__MustWork() {
            val actual = Trie()
            actual.add("param")
            actual.add("parameter")
            actual.remove("param")
            val expected = Trie()
            expected.add("parameter")
            assertEquals(expected, actual)
        }

        @Test
        fun bigTrie_turnToEmpty_MustWork() {
            val trie = getBigTrie()
            for (i in 1..10000) {
                trie.remove(i.toString())
            }
            assertEquals(emptyTrie, trie)
        }

        @Test
        fun bigTrie_removalOfOneElement_MustWork() {
            val trie = getBigTrie()
            trie.remove("590")
            assertFalse(trie.contains("590"))
        }

        @Test
        fun checkResultOfRemoving_containsElement_MustWork() {
            val trie = Trie()
            trie.add("qwerty")
            trie.add("qwe")
            assertTrue(trie.remove("qwerty"))
        }

        @Test
        fun checkResultOfRemoving_DoesNotContainsElement_MustWork() {
            val trie = Trie()
            trie.add("qwerty")
            trie.add("qwe")
            assertFalse(trie.remove("some"))
        }
    }

    @Nested
    inner class Check_numberOfWords {
        @Test
        fun emptyTrie_MustWork() {
            assertEquals(0, emptyTrie.numberOfWords)
        }

        @Test
        fun bigTrie_MustWork() {
            assertEquals(10000, getBigTrie().numberOfWords)
        }
    }

    @Nested
    inner class Check_contains {
        @Test
        fun emptyTrie_MustWork() {
            assertFalse(emptyTrie.contains("qwe"))
        }

        @Test
        fun bigTrie_MustWork() {
            assertTrue(getBigTrie().contains("123"))
        }
    }

    @Nested
    inner class Check_howManyStartsWithPrefix {
        @Test
        fun emptyTrie_MustWork() {
            assertEquals(0, emptyTrie.howManyStartsWithPrefix("some"))
        }

        @Test
        fun bigTrie_MustWork() {
            assertEquals(111, getBigTrie().howManyStartsWithPrefix("13"))
        }

        @Test
        fun containsPrefix_MustWork() {
            val trie = Trie()
            trie.add("he")
            trie.add("his")
            trie.add("she")
            trie.add("hers")
            assertEquals(3, trie.howManyStartsWithPrefix("h"))
        }

        @Test
        fun doesNotContainsPrefix_MustWork() {
            val trie = Trie()
            trie.add("somebody")
            trie.add("something")
            trie.add("somewhere")
            assertEquals(0, trie.howManyStartsWithPrefix("where"))
        }
    }

    @Nested
    inner class Check_serialize {
        @Test
        fun emptyStream_MustWork() {
            val outputStream = FileOutputStream("$pathToFolderWithTextFiles/recordedEmptyTrie.txt")
            emptyTrie.serialize(outputStream)
            val actual = File("$pathToFolderWithTextFiles/recordedEmptyTrie.txt").readText()
            val expected = ""
            assertEquals(expected, actual)
        }

        @Test
        fun simpleTrie_MustWork() {
            val trie = Trie()
            trie.add("parser")
            trie.add("parker")
            trie.add("parameter")
            trie.add("param")
            trie.add("kotlin")
            trie.add("camera")
            trie.add("cameron")
            val outputStream = FileOutputStream("$pathToFolderWithTextFiles/recordedNonEmptyTrie.txt")
            trie.serialize(outputStream)
            val actual = File("$pathToFolderWithTextFiles/recordedNonEmptyTrie.txt").readText()
            val expected = "parser;parker;param;parameter;kotlin;camera;cameron"
            assertEquals(expected, actual)
        }
    }

    @Nested
    inner class Check_deserialize {
        @Test
        fun fileStream_MustWork() {
            val inputStream = File("$pathToFolderWithTextFiles/nonEmptyTrie.txt").inputStream()
            val actual = Trie()
            actual.deserialize(inputStream)
            val expected = Trie()
            expected.add("something")
            expected.add("somewhere")
            expected.add("someone")
            expected.add("somebody")
            expected.add("never")
            expected.add("ever")
            expected.add("nothing")
            expected.add("nowhere")
            assertEquals(expected, actual)
        }

        @Test
        fun byteArrayStream_MustWork() {
            val inputStream = ByteArrayInputStream("101;102;103;140;150;160".toByteArray())
            val actual = Trie()
            actual.deserialize(inputStream)
            val expected = Trie()
            expected.add("101")
            expected.add("102")
            expected.add("103")
            expected.add("140")
            expected.add("150")
            expected.add("160")
            assertEquals(expected, actual)
        }

        @Test
        fun invalidStream_MustWork() {
            val inputStream = ByteArrayInputStream("".toByteArray())
            val trie = Trie()
            assertThrows(IOException::class.java) {
                trie.deserialize(inputStream)
            }
        }
    }
}

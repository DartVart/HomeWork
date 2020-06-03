package homeworks.homework4.task1

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Assertions.assertFalse
import org.junit.jupiter.api.Assertions.assertNull
import org.junit.jupiter.api.Assertions.assertThrows
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Test
import java.io.FileNotFoundException
import java.lang.IllegalStateException
import java.io.File as File

const val PATH_TO_DIRECTORY_WITH_TEXTS = "./src/test/resources/homeworks/homework4/task1"

internal class HashTableTest {
    fun getEmptyHashTable() = HashTable<String, String>(INITIAL_SIZE) { simpleHashFunction(it) }
    fun getBigAlmostFilledHashTable(): HashTable<String, String> {
        val hashTable = getEmptyHashTable()
        for (i in 0..1000) {
            hashTable.add(i.toString(), (2 * i).toString())
        }
        return hashTable
    }

    @Nested
    inner class Check_add {
        @Test
        fun simpleAdding_MustWork() {
            val hashTable = getEmptyHashTable()
            hashTable.add("one", "first")
            assertEquals("first", hashTable.find("one"))
        }

        @Test
        fun addingWithSameKeyAndDifferentValues_MustWork() {
            val hashTable = getEmptyHashTable()
            hashTable.add("one", "first")
            hashTable.add("one", "ONE")
            assertEquals("ONE", hashTable.find("one"))
        }

        @Test
        fun addingWithSameKeyAndValues_CheckValue_MustWork() {
            val hashTable = getEmptyHashTable()
            hashTable.add("one", "first")
            hashTable.add("one", "first")
            assertEquals("first", hashTable.find("one"))
        }

        @Test
        fun addingWithSameKeyAndValues_CheckNumberOfEntries_MustWork() {
            val hashTable = getEmptyHashTable()
            hashTable.add("one", "first")
            hashTable.add("one", "first")
            assertEquals(1, hashTable.numberOfEntries)
        }

        @Test
        fun bigHashTable_CheckValue_MustWork() {
            val hashTable = getBigAlmostFilledHashTable()
            assertEquals("1000", hashTable.find("500"))
        }

        @Test
        fun bigHashTable_CheckNumberOfEntries_MustWork() {
            val hashTable = getBigAlmostFilledHashTable()
            assertEquals(1001, hashTable.numberOfEntries)
        }
    }

    @Nested
    inner class Check_remove {
        @Test
        fun emptyHashTable_MustWork() {
            val hashTable = getEmptyHashTable()
            assertFalse(hashTable.remove("1"))
        }

        @Test
        fun simpleRemoval_ContainsKey_MustWork() {
            val hashTable = getEmptyHashTable()
            hashTable.add("1", "one")
            hashTable.add("2", "two")
            hashTable.remove("2")
            assertNull(hashTable.find("2"))
        }

        @Test
        fun simpleRemoval_DoesNotContainsKey_MustWork() {
            val hashTable = getEmptyHashTable()
            hashTable.add("1", "one")
            hashTable.add("2", "two")
            assertFalse(hashTable.remove("3"))
        }

        @Test
        fun turnToEmptyHashTable_MustWork() {
            val hashTable = getBigAlmostFilledHashTable()
            for (i in 1000 downTo 0) {
                hashTable.remove(i.toString())
            }
            assertTrue(hashTable.isEmpty())
        }
    }

    @Nested
    inner class Check_find {
        @Test
        fun emptyHashTable_MustWork() {
            val hashTable = getEmptyHashTable()
            assertNull(hashTable.find("1"))
        }

        @Test
        fun bigHashTable_ContainsKey_MustWork() {
            val hashTable = getBigAlmostFilledHashTable()
            assertEquals("1000", hashTable.find("500"))
        }

        @Test
        fun bigHashTable_DoesNotContainsKey_MustWork() {
            val hashTable = getBigAlmostFilledHashTable()
            assertNull(hashTable.find("-1"))
        }
    }

    @Nested
    inner class Check_setHashFunction {
        private val hashTableWithAnotherHashFunction = getBigAlmostFilledHashTable()

        init {
            hashTableWithAnotherHashFunction.setHashFunction { polynomialHashFunction(it) }
        }

        @Test
        fun checkNumberOfEntries_MustWork() {
            assertEquals(1001, hashTableWithAnotherHashFunction.numberOfEntries)
        }

        @Test
        fun checkValue1_MustWork() {
            assertEquals("200", hashTableWithAnotherHashFunction.find("100"))
        }

        @Test
        fun checkValue2_MustWork() {
            assertEquals("400", hashTableWithAnotherHashFunction.find("200"))
        }
    }

    @Nested
    inner class Check_fillFromFile {
        private fun getHashTableFilledFromFile(fileName: String): HashTable<String, String> {
            val hashTable = getEmptyHashTable()
            hashTable.fileParser.stringToKey = { it }
            hashTable.fileParser.stringToValue = { it }
            val inputFile = File("$PATH_TO_DIRECTORY_WITH_TEXTS/$fileName")
            hashTable.fileParser.fillFromFile(inputFile)
            return hashTable
        }

        @Test
        fun emptyFile_MustWork() {
            val hashTable = getHashTableFilledFromFile("empty.txt")
            assertTrue(hashTable.isEmpty())
        }

        @Test
        fun fileWithEntriesOnly_CheckNumberOfEntries_MustWork() {
            val hashTable = getHashTableFilledFromFile("fileWithEntriesOnly.txt")
            assertEquals(8, hashTable.numberOfEntries)
        }

        @Test
        fun fileWithEntriesOnly_CheckValue_MustWork() {
            val hashTable = getHashTableFilledFromFile("fileWithEntriesOnly.txt")
            assertEquals("value3", hashTable.find("key3"))
        }

        @Test
        fun fileWithWordsThatAreNotEntries_CheckNumberOfEntries_MustWork() {
            val hashTable = getHashTableFilledFromFile("fileWithExtraWords.txt")
            assertEquals(8, hashTable.numberOfEntries)
        }

        @Test
        fun fileWithWordsThatAreNotEntries_CheckValue_MustWork() {
            val hashTable = getHashTableFilledFromFile("fileWithExtraWords.txt")
            assertEquals("value5", hashTable.find("key5"))
        }

        @Test
        fun nonexistentFile_ThrowsException() {
            val hashTable = getEmptyHashTable()
            val nonexistentFile = File("nonexistentFile.txt")
            assertThrows(FileNotFoundException::class.java) {
                hashTable.fileParser.fillFromFile(nonexistentFile)
            }
        }

        @Test
        fun stringToKeyIsNull_ThrowsException() {
            val hashTable = getEmptyHashTable()
            hashTable.fileParser.stringToValue = { it }
            val nonexistentFile = File("$PATH_TO_DIRECTORY_WITH_TEXTS/empty.txt")
            assertThrows(NullPointerException::class.java) {
                hashTable.fileParser.fillFromFile(nonexistentFile)
            }
        }

        @Test
        fun stringToValueIsNull_ThrowsException() {
            val hashTable = getEmptyHashTable()
            hashTable.fileParser.stringToKey = { it }
            val nonexistentFile = File("$PATH_TO_DIRECTORY_WITH_TEXTS/empty.txt")
            assertThrows(NullPointerException::class.java) {
                hashTable.fileParser.fillFromFile(nonexistentFile)
            }
        }

        @Test
        fun incorrectFile_ThrowsException() {
            val hashTable = getEmptyHashTable()
            hashTable.fileParser.stringToKey = { it }
            hashTable.fileParser.stringToValue = { it }
            val inputFile = File("$PATH_TO_DIRECTORY_WITH_TEXTS/incorrect.txt")
            assertThrows(IllegalStateException::class.java) {
                hashTable.fileParser.fillFromFile(inputFile)
            }
        }
    }
}

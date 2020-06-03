package homeworks.homework4.task1

import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertIterableEquals
import org.junit.jupiter.api.Assertions.assertNull
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Test

internal class BucketTest {
    val emptyBucket = Bucket<Int, String>()

    fun getSimpleBucket(): Bucket<Int, String> {
        val bucket = Bucket<Int, String>()
        bucket.add(100, "100")
        bucket.add(123, "123")
        bucket.add(321, "321")
        return bucket
    }
    val immutableSimpleBucket = getSimpleBucket()

    @Nested
    inner class Check_add {
        @Test
        fun simpleAdding_MustWork() {
            val bucket = Bucket<Int, String>()
            bucket.add(123, "123")
            bucket.add(-34, "-34")
            bucket.add(0, "0")
            val expectedListOfEntries =
                listOf(MutablePair(123, "123"), MutablePair(-34, "-34"), MutablePair(0, "0"))
            assertIterableEquals(expectedListOfEntries, bucket.listOfEntries)
        }

        @Test
        fun addingWithSameKey_MustWork() {
            val bucket = Bucket<Int, String>()
            bucket.add(0, "0")
            bucket.add(1, "1")
            bucket.add(1, "one")
            bucket.add(0, "zero")
            val expectedListOfEntries = listOf(MutablePair(0, "zero"), MutablePair(1, "one"))
            assertIterableEquals(expectedListOfEntries, bucket.listOfEntries)
        }

        @Test
        fun addingWithSameEntry_MustWork() {
            val bucket = Bucket<Int, String>()
            bucket.add(0, "0")
            bucket.add(1, "1")
            bucket.add(1, "1")
            bucket.add(0, "0")
            val expectedListOfEntries = listOf(MutablePair(0, "0"), MutablePair(1, "1"))
            assertIterableEquals(expectedListOfEntries, bucket.listOfEntries)
        }
    }

    @Nested
    inner class Check_getPairByKey {
        @Test
        fun emptyBucket_MustWork() {
            assertNull(emptyBucket.getPairByKey(123))
        }

        @Test
        fun containsKey_MustWork() {
            val expected = MutablePair(123, "123")
            assertEquals(expected, immutableSimpleBucket.getPairByKey(123))
        }

        @Test
        fun doesNotContainsKey_MustWork() {
            assertNull(immutableSimpleBucket.getPairByKey(-1))
        }
    }

    @Nested
    inner class Check_remove {
        @Test
        fun emptyBucket_MustWork() {
            val bucket = Bucket<Int, String>()
            bucket.remove(123)
            assertIterableEquals(listOf<MutablePair<Int, String>>(), bucket.listOfEntries)
        }

        @Test
        fun containsKey_MustWork() {
            val bucket = getSimpleBucket()
            bucket.remove(100)
            bucket.remove(321)
            val expectedListOfEntries =
                listOf(MutablePair(123, "123"))
            assertIterableEquals(expectedListOfEntries, bucket.listOfEntries)
        }

        @Test
        fun doesNotContainsKey_MustWork() {
            val bucket = getSimpleBucket()
            bucket.remove(-1)
            bucket.remove(-2)
            val expectedListOfEntries =
                listOf(MutablePair(100, "100"), MutablePair(123, "123"), MutablePair(321, "321"))
            assertIterableEquals(expectedListOfEntries, bucket.listOfEntries)
        }

        @Test
        fun turnToEmptyBucket_MustWork() {
            val bucket = getSimpleBucket()
            bucket.remove(100)
            bucket.add(1, "1")
            bucket.remove(123)
            bucket.remove(1)
            bucket.remove(321)
            assertIterableEquals(emptyBucket.listOfEntries, bucket.listOfEntries)
        }
    }

    @Nested
    inner class Check_size {
        @Test
        fun emptyBucket_MustWork() {
            assertEquals(0, emptyBucket.size)
        }

        @Test
        fun simpleBucket_MustWork() {
            assertEquals(3, immutableSimpleBucket.size)
        }

        @Test
        fun bigBucket_MustWork() {
            val bucket = Bucket<Int, String>()
            for (i in 0 until 10000) {
                bucket.add(i, i.toString())
            }
            assertEquals(10000, bucket.size)
        }
    }
}

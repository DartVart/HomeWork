package homeworks.homework3.task1

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Assertions.assertEquals
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Assertions.assertFalse
import org.junit.jupiter.api.Assertions.assertNull

internal class AVLTreeTest {
    private val smallTree = AVLTree<Int, String>()
    init {
        smallTree.put(20, "b")
        smallTree.put(30, "c")
        smallTree.put(10, "a")
    }

    // Will be used to test methods that change the tree
    private fun getBigTree(): AVLTree<Int, String> {
        val tree = AVLTree<Int, String>()
        for (i in 0..1000 step 2) {
            tree.put(i, i.toString())
        }
        return tree
    }

    // Will be used to test methods that don't change the tree
    private val bigTree = getBigTree()

    private val emptyTree = AVLTree<Int, String>()

    @Nested
    inner class Check_equalsTo {
        @Test
        fun onlyFirstTreeIsEmpty_MustWork() {
            println(emptyTree)
            println(smallTree)
            assertFalse(emptyTree.equalsTo(smallTree))
        }

        @Test
        fun onlySecondTreeIsEmpty_MustWork() {
            assertFalse(smallTree.equalsTo(emptyTree))
        }

        @Test
        fun bothTreesAreEmpty_MustWork() {
            assertTrue(emptyTree.equalsTo(emptyTree))
        }

        @Test
        fun notIdenticalAndNotEmptyTrees_MustWork() {
            assertFalse(bigTree.equalsTo(smallTree))
        }

        @Test
        fun identicalAndNotEmptyTrees_MustWork() {
            assertTrue(bigTree.equalsTo(getBigTree()))
        }
    }

    @Nested
    inner class Check_containsKey {
        @Test
        fun emptyTree_MustWork() {
            assertFalse(emptyTree.containsKey(90))
        }

        @Test
        fun singleElementTree_ContainsKey_MustWork() {
            val tree = AVLTree<Int, String>()
            tree.put(10, "ten")
            assertTrue(tree.containsKey(10))
        }

        @Test
        fun bigTree_ContainsKey_MustWork() {
            assertTrue(bigTree.containsKey(460))
        }

        @Test
        fun bigTree_DoesNotContainKey_MustWork() {
            assertFalse(bigTree.containsKey(461))
        }
    }

    @Nested
    inner class Check_containsValue {
        @Test
        fun emptyTree_MustWork() {
            assertFalse(emptyTree.containsValue("some"))
        }

        @Test
        fun singleElementTree_ContainsValue_MustWork() {
            val tree = AVLTree<Int, String>()
            tree.put(10, "ten")
            assertTrue(tree.containsValue("ten"))
        }

        @Test
        fun bigTree_ContainsValue_MustWork() {
            assertTrue(bigTree.containsValue("460"))
        }

        @Test
        fun bigTree_DoesNotContainValue_MustWork() {
            assertFalse(bigTree.containsValue("461"))
        }
    }

    @Nested
    inner class Check_size {
        @Test
        fun emptyTree_MustWork() {
            assertEquals(0, emptyTree.size)
        }

        @Test
        fun bigTree_MustWork() {
            assertEquals(501, bigTree.size)
        }
    }

    @Nested
    inner class Check_isEmpty {
        @Test
        fun emptyTree_MustWork() {
            assertTrue(emptyTree.isEmpty())
        }

        @Test
        fun notEmptyTree_MustWork() {
            val tree = AVLTree<Int, String>()
            tree.put(-1, "-1")
            assertFalse(tree.isEmpty())
        }
    }

    @Nested
    inner class Check_get {
        @Test
        fun emptyTree_MustWork() {
            assertNull(emptyTree[90])
        }

        @Test
        fun bigTree_ContainsKey_MustWork() {
            assertEquals("100", bigTree[100])
        }

        @Test
        fun bigTree_DoesNotContainKey_MustWork() {
            assertNull(bigTree[101])
        }
    }

    @Nested
    inner class CheckProperty_keys {
        @Test
        fun emptyTree_MustWork() {
            val emptySet = setOf<Int>()
            assertEquals(emptySet, emptyTree.keys)
        }

        @Test
        fun smallTree_MustWork() {
            val expectedSet = setOf(10, 20, 30)
            assertEquals(expectedSet, smallTree.keys)
        }
    }

    @Nested
    inner class CheckProperty_values {
        @Test
        fun emptyTree_MustWork() {
            val emptyList = listOf<String>()
            assertEquals(emptyList, emptyTree.values)
        }

        @Test
        fun smallTree_MustWork() {
            val expectedList = listOf("b", "c", "a")
            assertEquals(expectedList, smallTree.values)
        }
    }

    @Nested
    inner class CheckProperty_entries {
        @Test
        fun emptyTree_MustWork() {
            val actualSet = emptyTree.entries.map { Pair(it.key, it.value) }.toSet()
            val emptySet = setOf<Pair<Int, String>>()
            assertEquals(emptySet, actualSet)
        }

        @Test
        fun smallTree_MustWork() {
            val actualSet = smallTree.entries.map { Pair(it.key, it.value) }.toSet()
            val expectedSet = setOf(Pair(10, "a"), Pair(20, "b"), Pair(30, "c"))
            assertEquals(expectedSet, actualSet)
        }
    }

    @Nested
    inner class Check_Put_And_Remove {
        @Test
        fun putToBigTree_MustWork() {
            val tree = getBigTree()
            tree.put(-100, "-100")
            assertTrue(tree.containsKey(-100))
        }

        @Test
        fun checkValueReturnedAfterPutting_KeyWasNotInTree_MustWork() {
            assertNull(getBigTree().put(101, "101"))
        }

        @Test
        fun checkValueReturnedAfterPutting_KeyWasInTree_MustWork() {
            assertEquals("0", getBigTree().put(0, "zero"))
        }

        @Test
        fun removeFromBigTree_MustWork() {
            val tree = getBigTree()
            tree.remove(0)
            assertFalse(tree.containsKey(0))
        }

        @Test
        fun checkValueReturnedAfterRemoving_KeyWasInTree_MustWork() {
            assertEquals("500", getBigTree().remove(500))
        }

        @Test
        fun checkValueReturnedAfterRemoving_KeyWasNotInTree_MustWork() {
            assertNull(getBigTree().remove(501))
        }

        @Test
        fun putAndRemove_ItTurnsOutEmptyTree_MustWork() {
            val tree = AVLTree<Int, String>()
            tree.put(1, "1")
            tree.put(3, "3")
            tree.remove(1)
            tree.put(2, "2")
            tree.remove(2)
            tree.remove(3)
            assertTrue(tree.equalsTo(emptyTree))
        }
    }
}

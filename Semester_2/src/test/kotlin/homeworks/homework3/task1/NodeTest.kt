package homeworks.homework3.task1

import org.junit.jupiter.api.Test
import org.junit.jupiter.api.Nested
import org.junit.jupiter.api.Assertions.assertNull
import org.junit.jupiter.api.Assertions.assertTrue
import org.junit.jupiter.api.Assertions.assertFalse

internal class NodeTest {
    val simpleNode = Node(9, "9")

    fun getNodeWithChildren(): Node<Int, String> {
        val result = Node(10, "10")
        result.addRightChild(Node(20, "20"))
        result.addLeftChild(Node(0, "0"))
        return result
    }

    fun <K, V> Node<K, V>.addRightChild(node: Node<K, V>) where K : Comparable<K> {
        rightChild = node
        updateHeight()
    }

    fun <K, V> Node<K, V>.addLeftChild(node: Node<K, V>) where K : Comparable<K> {
        leftChild = node
        updateHeight()
    }

    @Nested
    inner class Check_equalsTo {
        @Test
        fun argumentIsNull_MustWork() {
            assertFalse(getNodeWithChildren().equalsTo(null))
        }

        @Test
        fun identicalNodesWithoutChildren_MustWork() {
            assertTrue(simpleNode.equalsTo(Node(9, "9")))
        }

        @Test
        fun identicalNodesWithChildren_MustWork() {
            val firstNode = getNodeWithChildren()
            val secondNode = getNodeWithChildren()
            assertTrue(firstNode.equalsTo(secondNode))
        }

        @Test
        fun notIdenticalNodes_MustWork() {
            assertFalse(getNodeWithChildren().equalsTo(simpleNode))
        }

        @Test
        fun objectsThatAreEqualByReference_MustWork() {
            assertTrue(simpleNode.equalsTo(simpleNode))
        }
    }

    @Nested
    inner class Check_getMinimumNode {
        @Test
        fun nodeWithoutChildren_MustWork() {
            val result = simpleNode.getMinimumNode()
            assertTrue(simpleNode.equalsTo(result))
        }

        @Test
        fun nodeWithoutLeftChild_MustWork() {
            val node = Node(0, "0")
            node.addRightChild(Node(2, "2"))
            val result = node.getMinimumNode()
            assertTrue(node.equalsTo(result))
        }

        @Test
        fun nodeWithLeftChild_MustWork() {
            val node = getNodeWithChildren()
            node.leftChild?.addLeftChild(Node(-9, "-9"))
            node.leftChild?.leftChild?.addRightChild(Node(-1, "-1"))

            val actual = node.getMinimumNode()
            val expected = Node(-9, "-9")
            expected.addRightChild(Node(-1, "-1"))
            assertTrue(expected.equalsTo(actual))
        }
    }

    @Nested
    inner class Check_separateMinimumNode {
        @Test
        fun nodeWithoutChildren_MustWork() {
            assertNull(simpleNode.separateMinimumNode())
        }

        @Test
        fun nodeWithoutLeftChild_MustWork() {
            val node = Node(0, "0")
            node.addRightChild(Node(2, "2"))

            val actual = node.separateMinimumNode()
            val expected = Node(2, "2")
            assertTrue(expected.equalsTo(actual))
        }

        @Test
        fun nodeWithLeftChild_MustWork() {
            val node = getNodeWithChildren()
            node.leftChild?.addRightChild(Node(8, "8"))

            val actual = node.separateMinimumNode()
            val expected = getNodeWithChildren()
            expected.addLeftChild(Node(8, "8"))
            assertTrue(expected.equalsTo(actual))
        }
    }

    @Nested
    inner class Check_getBalancedNode {
        @Test
        fun needOnlyRightTurn_threeNodes_MustWork() {
            val node = Node(0, "0")
            node.addLeftChild(Node(-1, "-1"))
            node.leftChild?.addLeftChild(Node(-2, "-2"))

            val actual = node.getBalancedNode()
            val expected = Node(-1, "-1")
            expected.addLeftChild(Node(-2, "-2"))
            expected.addRightChild(Node(0, "0"))
            assertTrue(expected.equalsTo(actual))
        }

        @Test
        fun needOnlyRightTurn_standardSituation_MustWork() {
            val node = getNodeWithChildren()
            node.leftChild?.addRightChild(Node(8, "8"))
            node.leftChild?.addLeftChild(Node(-1, "-1"))
            node.leftChild?.leftChild?.addLeftChild(Node(-2, "-2"))
            node.leftChild?.updateHeight()

            val actual = node.getBalancedNode()
            val expected = Node(0, "0")
            expected.addRightChild(Node(10, "10"))
            expected.rightChild?.addLeftChild(Node(8, "8"))
            expected.rightChild?.addRightChild(Node(20, "20"))
            expected.addLeftChild(Node(-1, "-1"))
            expected.leftChild?.addLeftChild(Node(-2, "-2"))
            assertTrue(expected.equalsTo(actual))
        }

        @Test
        fun needOnlyLeftTurn_threeNodes_MustWork() {
            val node = Node(0, "0")
            node.addRightChild(Node(1, "1"))
            node.rightChild?.addRightChild(Node(2, "2"))

            val actual = node.getBalancedNode()
            val expected = Node(1, "1")
            expected.addLeftChild(Node(0, "0"))
            expected.addRightChild(Node(2, "2"))
            assertTrue(expected.equalsTo(actual))
        }

        @Test
        fun needOnlyLeftTurn_standardSituation_MustWork() {
            val node = getNodeWithChildren()
            node.rightChild?.addRightChild(Node(30, "30"))
            node.rightChild?.addLeftChild(Node(15, "15"))
            node.rightChild?.rightChild?.addRightChild(Node(40, "40"))
            node.rightChild?.updateHeight()

            val actual = node.getBalancedNode()
            val expected = Node(20, "20")
            expected.addRightChild(Node(30, "30"))
            expected.rightChild?.addRightChild(Node(40, "40"))
            expected.addLeftChild(Node(10, "10"))
            expected.leftChild?.addRightChild(Node(15, "15"))
            expected.leftChild?.addLeftChild(Node(0, "0"))
            assertTrue(expected.equalsTo(actual))
        }

        @Test
        fun needRightThenLeftTurn_MustWork() {
            val node = Node(0, "0")
            node.addRightChild(Node(2, "2"))
            node.rightChild?.addLeftChild(Node(1, "1"))

            val actual = node.getBalancedNode()
            val expected = Node(1, "1")
            expected.addRightChild(Node(2, "2"))
            expected.addLeftChild(Node(0, "0"))
            assertTrue(expected.equalsTo(actual))
        }

        @Test
        fun needLeftThenRightTurn_MustWork() {
            val node = Node(0, "0")
            node.addLeftChild(Node(-2, "-2"))
            node.leftChild?.addRightChild(Node(-1, "-1"))

            val actual = node.getBalancedNode()
            val expected = Node(-1, "-1")
            expected.addLeftChild(Node(-2, "-2"))
            expected.addRightChild(Node(0, "0"))
            assertTrue(expected.equalsTo(actual))
        }
    }
}

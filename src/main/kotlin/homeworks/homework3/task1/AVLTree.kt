package homeworks.homework3.task1

import java.util.Stack
import kotlin.math.max

class AVLTree<K, V> : Map<K, V> where K : Comparable<K> {
    override val entries: Set<Map.Entry<K, V>>
        get() = root?.asSequence()?.toSet() ?: setOf()

    override val keys: Set<K>
        get() = root?.asSequence()?.map { it.key }?.toSet() ?: setOf()

    override val values: Collection<V>
        get() = root?.asSequence()?.map { it.value }?.toList() ?: listOf()

    override val size: Int
        get() = root?.sizeOfSubtree ?: 0

    private var root: Node? = null

    private var returnValueAfterPutting: V? = null
    private var returnValueAfterRemoval: V? = null

    companion object {
        private const val BALANCE_FACTOR_NEEDED_FOR_RIGHT_TURN = -2
        private const val BALANCE_FACTOR_NEEDED_FOR_LEFT_TURN = 2
    }

    private inner class Node(override val key: K, override var value: V) : Map.Entry<K, V>, Iterable<Node> {
        private var rightChild: Node? = null
        private var leftChild: Node? = null
        private val children: List<Node>
            get() = listOfNotNull(leftChild, rightChild)

        /**
         * Should be 0 if the node is null
         */
        private var height: Int = 1

        private val leftChildHeight: Int
            get() = leftChild?.height ?: 0

        private val rightChildHeight: Int
            get() = rightChild?.height ?: 0

        private val balanceFactor: Int
            get() = rightChildHeight - leftChildHeight

        private fun updateHeight() {
            height = max(leftChildHeight, rightChildHeight) + 1
        }

        val sizeOfSubtree: Int
            get() = (rightChild?.sizeOfSubtree ?: 0) + (leftChild?.sizeOfSubtree ?: 0) + 1

        private val minimumInSubtree: Node?
            get() = leftChild?.minimumInSubtree ?: this

        private fun rotateLeft(): Node? {
            val pivot = rightChild
            rightChild = pivot?.leftChild
            pivot?.leftChild = this
            updateHeight()
            pivot?.updateHeight()
            return pivot
        }

        private fun rotateRight(): Node? {
            val pivot = leftChild
            leftChild = pivot?.rightChild
            pivot?.rightChild = this
            updateHeight()
            pivot?.updateHeight()
            return pivot
        }

        private fun getBalancedNode(): Node? {
            updateHeight()
            return when (balanceFactor) {
                BALANCE_FACTOR_NEEDED_FOR_LEFT_TURN -> {
                    if ((rightChild?.balanceFactor ?: 0) < 0) {
                        rightChild = rightChild?.rotateRight()
                    }
                    rotateLeft()
                }
                BALANCE_FACTOR_NEEDED_FOR_RIGHT_TURN -> {
                    if ((leftChild?.balanceFactor ?: 0) > 0) {
                        leftChild = leftChild?.rotateLeft()
                    }
                    rotateRight()
                }
                else -> {
                    this
                }
            }
        }

        fun containsValueInSubtree(value: V): Boolean {
            if (this.value == value) {
                return true
            }
            return leftChild?.containsValueInSubtree(value) ?: false ||
                    rightChild?.containsValueInSubtree(value) ?: false
        }

        fun getFromSubtree(key: K): V? {
            return when {
                this.key < key -> {
                    rightChild?.getFromSubtree(key)
                }
                this.key > key -> {
                    leftChild?.getFromSubtree(key)
                }
                else -> {
                    this.value
                }
            }
        }

        fun getSubtreeWithInsertedElement(key: K, value: V): Node? {
            when {
                this.key < key -> {
                    rightChild = rightChild?.getSubtreeWithInsertedElement(key, value) ?: Node(key, value)
                }
                this.key > key -> {
                    leftChild = leftChild?.getSubtreeWithInsertedElement(key, value) ?: Node(key, value)
                }
                else -> {
                    returnValueAfterPutting = this.value
                    this.value = value
                }
            }
            return getBalancedNode()
        }

        private fun separateMinimumFromSubtree(): Node? {
            if (leftChild == null) {
                return rightChild
            }
            leftChild = leftChild?.separateMinimumFromSubtree()
            return getBalancedNode()
        }

        fun getSubtreeWithRemovedNode(key: K): Node? {
            when {
                this.key < key -> {
                    rightChild = rightChild?.getSubtreeWithRemovedNode(key)
                }
                this.key > key -> {
                    leftChild = leftChild?.getSubtreeWithRemovedNode(key)
                }
                else -> {
                    returnValueAfterRemoval = this.value
                    return if (rightChild == null) {
                        leftChild
                    } else {
                        val minimumInRightSubtree = rightChild?.minimumInSubtree
                        minimumInRightSubtree?.rightChild = rightChild?.separateMinimumFromSubtree()
                        minimumInRightSubtree?.leftChild = leftChild
                        minimumInRightSubtree?.getBalancedNode()
                    }
                }
            }
            return getBalancedNode()
        }

        override fun iterator(): Iterator<Node> {
            val stackOfNodes = Stack<Node>()
            stackOfNodes.push(this)
            var currentNode: Node

            return sequence {
                while (stackOfNodes.isNotEmpty()) {
                    currentNode = stackOfNodes.pop()
                    currentNode.children.forEach {
                        stackOfNodes.push(it)
                    }
                    yield(currentNode)
                }
            }.iterator()
        }
    }

    override fun containsKey(key: K): Boolean {
        return root?.getFromSubtree(key) != null
    }

    override fun containsValue(value: V): Boolean {
        return root?.containsValueInSubtree(value) ?: false
    }

    override fun get(key: K): V? {
        return root?.getFromSubtree(key)
    }

    override fun isEmpty(): Boolean {
        return size == 0
    }

    fun put(key: K, value: V): V? {
        root = root?.getSubtreeWithInsertedElement(key, value) ?: Node(key, value)
        val result = returnValueAfterPutting
        returnValueAfterPutting = null
        return result
    }

    fun remove(key: K): V? {
        root = root?.getSubtreeWithRemovedNode(key)
        val result = returnValueAfterRemoval
        returnValueAfterRemoval = null
        return result
    }
}

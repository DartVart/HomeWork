package homeworks.homework3.task1

import java.util.Stack

class Node<K, V>(override val key: K, override var value: V) : Map.Entry<K, V>, Iterable<Node<K, V>>
        where K : Comparable<K> {

    companion object {
        private const val BALANCE_FACTOR_NEEDED_FOR_RIGHT_TURN = -2
        private const val BALANCE_FACTOR_NEEDED_FOR_LEFT_TURN = 2
    }

    var rightChild: Node<K, V>? = null
    var leftChild: Node<K, V>? = null
    private val children: List<Node<K, V>>
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
        height = kotlin.math.max(leftChildHeight, rightChildHeight) + 1
    }

    private fun rotateLeft(): Node<K, V>? {
        val pivot = rightChild
        rightChild = pivot?.leftChild
        pivot?.leftChild = this
        updateHeight()
        pivot?.updateHeight()
        return pivot
    }

    private fun rotateRight(): Node<K, V>? {
        val pivot = leftChild
        leftChild = pivot?.rightChild
        pivot?.rightChild = this
        updateHeight()
        pivot?.updateHeight()
        return pivot
    }

    fun getBalancedNode(): Node<K, V>? {
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

    fun separateMinimumNode(): Node<K, V>? {
        if (leftChild == null) {
            return rightChild
        }
        leftChild = leftChild?.separateMinimumNode()
        return getBalancedNode()
    }

    fun getMinimumNode(): Node<K, V>? {
        return leftChild?.getMinimumNode() ?: this
    }

    override fun iterator(): Iterator<Node<K, V>> {
        val stackOfNodes = Stack<Node<K, V>>()
        stackOfNodes.push(this)
        var currentNode: Node<K, V>

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
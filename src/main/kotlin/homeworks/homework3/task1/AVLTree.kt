package homeworks.homework3.task1

class AVLTree<K, V> : Map<K, V> where K : Comparable<K> {
    override val entries: Set<Map.Entry<K, V>>
        get() = root?.asSequence()?.toSet() ?: setOf()

    override val keys: Set<K>
        get() = root?.asSequence()?.map { it.key }?.toSet() ?: setOf()

    override val values: Collection<V>
        get() = root?.asSequence()?.map { it.value }?.toList() ?: listOf()

    override var size = 0

    private var root: Node<K, V>? = null
    private val subtreeOperations = SubtreeOperations()

    private var returnValueAfterPutting: V? = null
    private var returnValueAfterRemoval: V? = null

    override fun containsKey(key: K): Boolean {
        return root?.let { subtreeOperations.get(key, it) } != null
    }

    override fun containsValue(value: V): Boolean {
        return root?.let { subtreeOperations.containsValue(value, it) } ?: false
    }

    override fun get(key: K): V? {
        return root?.let { subtreeOperations.get(key, it) }
    }

    override fun isEmpty(): Boolean {
        return size == 0
    }

    fun put(key: K, value: V): V? {
        root = root?.let { subtreeOperations.put(key, value, it) } ?: subtreeOperations.getNodeToInsert(key, value)
        val result = returnValueAfterPutting
        returnValueAfterPutting = null
        return result
    }

    fun remove(key: K): V? {
        root = root?.let { subtreeOperations.remove(key, it) }
        val result = returnValueAfterRemoval
        returnValueAfterRemoval = null
        return result
    }

    fun equalsTo(tree: AVLTree<K, V>): Boolean {
        return root?.equalsTo(tree.root) ?: (tree.root == null)
    }

    private inner class SubtreeOperations {
        fun getNodeToInsert(key: K, value: V): Node<K, V> {
            size++
            return Node(key, value)
        }

        fun remove(key: K, node: Node<K, V>): Node<K, V>? {
            when {
                node.key < key -> {
                    node.rightChild = node.rightChild?.let { remove(key, it) }
                }
                node.key > key -> {
                    node.leftChild = node.leftChild?.let { remove(key, it) }
                }
                else -> {
                    returnValueAfterRemoval = node.value
                    size--
                    return if (node.rightChild == null) {
                        node.leftChild
                    } else {
                        val minimumInRightSubtree = node.rightChild?.getMinimumNode()
                        minimumInRightSubtree?.rightChild = node.rightChild?.separateMinimumNode()
                        minimumInRightSubtree?.leftChild = node.leftChild
                        minimumInRightSubtree?.getBalancedNode()
                    }
                }
            }
            return node.getBalancedNode()
        }

        fun put(key: K, value: V, node: Node<K, V>): Node<K, V>? {
            when {
                node.key < key -> {
                    node.rightChild =
                        node.rightChild?.let { put(key, value, it) } ?: getNodeToInsert(key, value)
                }
                node.key > key -> {
                    node.leftChild =
                        node.leftChild?.let { put(key, value, it) } ?: getNodeToInsert(key, value)
                }
                else -> {
                    returnValueAfterPutting = node.value
                    node.value = value
                }
            }
            return node.getBalancedNode()
        }

        fun get(key: K, node: Node<K, V>): V? {
            return when {
                node.key < key -> {
                    node.rightChild?.let { get(key, it) }
                }
                node.key > key -> {
                    node.leftChild?.let { get(key, it) }
                }
                else -> {
                    node.value
                }
            }
        }

        fun containsValue(value: V, node: Node<K, V>): Boolean {
            if (node.value == value) {
                return true
            }
            return node.leftChild?.let { containsValue(value, it) } ?: false ||
                    node.rightChild?.let { containsValue(value, it) } ?: false
        }
    }
}

package homeworks.homework5.task1

import java.io.IOException
import java.io.InputStream
import java.io.OutputStream
import java.util.Stack

class Trie : Serializable {
    private var root = Node()
    var size = 0
        private set

    fun add(element: String): Boolean {
        if (contains(element)) {
            return false
        }

        var currentNode = root
        element.forEach { it ->
            if (!currentNode.children.containsKey(it)) {
                currentNode.children[it] = Node()
            }
            currentNode.children[it]?.let { currentNode = it }
            currentNode.howManyStartsWithPrefix++
        }

        size++
        currentNode.isTerminal = true
        return true
    }

    fun contains(element: String): Boolean {
        var currentNode = root
        element.forEach {
            currentNode = currentNode.children[it] ?: return false
        }
        return currentNode.isTerminal
    }

    fun remove(element: String): Boolean {
        if (!contains(element)) {
            return false
        }

        var currentNode = root
        var nextNode: Node? = root
        for (symbol in element) {
            nextNode = currentNode.children[symbol]
            nextNode?.let { it.howManyStartsWithPrefix-- }
            if (nextNode?.howManyStartsWithPrefix == 0) {
                currentNode.children.remove(symbol)
                break
            } else {
                nextNode?.let { currentNode = it }
            }
        }
        nextNode?.let { it.isTerminal = false }
        size--
        return true
    }

    fun howManyStartsWithPrefix(prefix: String): Int {
        if (prefix == "") return size
        var currentNode: Node? = root
        prefix.forEach {
            currentNode = currentNode?.children?.get(it)
        }

        return currentNode?.howManyStartsWithPrefix ?: 0
    }

    override fun serialize(outputStream: OutputStream) {
        outputStream.write(root.getWords().joinToString(";").toByteArray())
        outputStream.close()
    }

    override fun deserialize(inputStream: InputStream) {
        root = Node()
        inputStream.bufferedReader().readLine()?.split(";")?.forEach {
            add(it)
        } ?: throw IOException("An attempt to read the stream resulted in a null result")
        inputStream.close()
    }

    fun equalsTo(otherTrie: Trie) = root.equalsTo(otherTrie.root)

    private class Node {
        var isTerminal = false
        val children: MutableMap<Char, Node> = mutableMapOf()
        var howManyStartsWithPrefix = 0

        fun getWords(): Stack<String> {
            val result = Stack<String>()
            children.forEach {
                if (it.value.isTerminal) {
                    result.push("${it.key}")
                }
                for (word in it.value.getWords()) {
                    result.push("${it.key}$word")
                }
            }
            return result
        }

        fun equalsTo(otherNode: Node): Boolean {
            var areEquals = true
            if (isTerminal == otherNode.isTerminal && children.size == otherNode.children.size) {
                for (charAndNodePair in children) {
                    if (!(otherNode.children[charAndNodePair.key]?.equalsTo(charAndNodePair.value) ?: return false)) {
                        areEquals = false
                        break
                    }
                }
            } else {
                areEquals = false
            }
            return areEquals
        }
    }
}

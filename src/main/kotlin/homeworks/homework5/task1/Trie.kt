package homeworks.homework5.task1

import java.io.IOException
import java.io.InputStream
import java.io.OutputStream
import java.io.Serializable
import java.util.Stack

class Trie : Serializable {
    private val root = Node()
    var numberOfWords = 0
        private set

    private companion object {
        const val PRIME_NUMBER_FOR_HASH_CODE = 31
    }

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

        numberOfWords++
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
                currentNode.children[symbol]?.removeAllDescendants()
                currentNode.children.remove(symbol)
                break
            } else {
                nextNode?.let { currentNode = it }
            }
        }
        nextNode?.let { it.isTerminal = false }
        numberOfWords--
        return true
    }

    fun howManyStartsWithPrefix(prefix: String): Int {
        var currentNode: Node? = root
        prefix.forEach {
            currentNode = currentNode?.children?.get(it)
        }

        return currentNode?.howManyStartsWithPrefix ?: 0
    }

    fun writeObject(outputStream: OutputStream) {
        outputStream.write(root.getWords().joinToString(";").toByteArray())
        outputStream.close()
    }

    fun readObject(inputStream: InputStream) {
        root.removeAllDescendants()
        numberOfWords = 0
        inputStream.bufferedReader().readLine()?.split(";")?.forEach {
            add(it)
        } ?: throw IOException("An attempt to read the stream resulted in a null result")
        inputStream.close()
    }

    override fun equals(other: Any?) = other is Trie && other.root == root

    override fun hashCode(): Int {
        var result = root.hashCode()
        result = PRIME_NUMBER_FOR_HASH_CODE * result + numberOfWords
        return result
    }

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

        fun removeAllDescendants() {
            if (children.isEmpty()) {
                return
            }
            children.forEach {
                it.value.removeAllDescendants()
            }
            children.clear()
        }

        override fun equals(other: Any?): Boolean {
            var areEquals = true
            if (other is Node && isTerminal == other.isTerminal && children.size == other.children.size) {
                for (charAndNodePair in children) {
                    if (other.children[charAndNodePair.key] != charAndNodePair.value) {
                        areEquals = false
                        break
                    }
                }
            } else {
                areEquals = false
            }
            return areEquals
        }

        override fun hashCode(): Int {
            var result = isTerminal.hashCode()
            result = PRIME_NUMBER_FOR_HASH_CODE * result + children.hashCode()
            result = PRIME_NUMBER_FOR_HASH_CODE * result + howManyStartsWithPrefix
            return result
        }
    }
}

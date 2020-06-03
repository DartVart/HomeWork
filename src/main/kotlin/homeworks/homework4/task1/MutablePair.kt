package homeworks.homework4.task1

class MutablePair<A, B>(var first: A, var second: B) {

    companion object {
        const val PRIME_NUMBER_FOR_HASH_CODE = 31
    }

    override fun toString(): String {
        return "($first, $second)"
    }

    override fun equals(other: Any?): Boolean {
        return if (other != null && other is MutablePair<*, *>) {
            first == other.first && second == other.second
        } else {
            false
        }
    }

    override fun hashCode(): Int {
        var result = first?.hashCode() ?: 0
        result = PRIME_NUMBER_FOR_HASH_CODE * result + (second?.hashCode() ?: 0)
        return result
    }
}

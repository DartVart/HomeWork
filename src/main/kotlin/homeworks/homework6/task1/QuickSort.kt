package homeworks.homework6.task1

class QuickSort<T> where T : Comparable<T> {
    private fun partition(
        list: MutableList<T>,
        leftElement: Int = 0,
        rightElement: Int = list.lastIndex
    ): Pair<Int, Int> {
        var upIterator = leftElement
        var downIterator = rightElement
        val middleIndex = (leftElement + rightElement) / 2
        val middleValue = list[middleIndex]

        while (upIterator < downIterator) {
            while (list[upIterator] < middleValue) {
                upIterator++
            }

            while (list[downIterator] > middleValue) {
                downIterator--
            }

            if (upIterator <= downIterator) {
                list[upIterator] = list[downIterator].also { list[downIterator] = list[upIterator] }
                upIterator++
                downIterator--
            }
        }
        return (Pair(upIterator, downIterator))
    }

    /**
     * Elements will be in ascending order.
     * */
    suspend fun asyncQuickSort(list: MutableList<T>, leftElement: Int = 0, rightElement: Int = list.lastIndex) {
        if (rightElement > leftElement) {
            val iteratorsPair = partition(list, leftElement, rightElement)
            asyncQuickSort(list, iteratorsPair.first, rightElement)
            asyncQuickSort(list, leftElement, iteratorsPair.second)
        }
    }

    /**
     * Elements will be in ascending order.
     * */
    fun usualQuickSort(list: MutableList<T>, leftElement: Int = 0, rightElement: Int = list.lastIndex) {
        if (rightElement > leftElement) {
            val iteratorsPair = partition(list, leftElement, rightElement)
            usualQuickSort(list, iteratorsPair.first, rightElement)
            usualQuickSort(list, leftElement, iteratorsPair.second)
        }
    }
}

#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//This method sorts descending
void quickSort(int array[], int leftElement, int rightElement)
{
    if (rightElement - leftElement < 1)
        return;

    int upIterator = leftElement, downIterator = rightElement;
    int middleIndex = (leftElement + rightElement) / 2;
    int middle = array[middleIndex];

    while (upIterator < downIterator)
    {
        while (array[upIterator] > middle)
        {
            upIterator++;
        }

        while (array[downIterator] < middle)
        {
            downIterator--;
        }

        if (upIterator <= downIterator)
        {
            swap(&array[upIterator], &array[downIterator]);
            upIterator++;
            downIterator--;
        }
    }

    quickSort(array, upIterator, rightElement);
    quickSort(array, leftElement, downIterator);
}

//This method modifies the array
int getIndexOfRepeatingMax(int array[], int sizeOfArray)
{
    quickSort(array, 0, sizeOfArray - 1);

    for (int i = 0; i < sizeOfArray - 1; i++)
    {
        if (array[i] == array[i + 1])
        {
            return i;
        }
    }

    return -1;
}

int main()
{
    int sizeOfInputArray = 0;
    printf("Enter the array size: ");
    scanf("%d", &sizeOfInputArray);

    int* inputArray = (int*) malloc(sizeOfInputArray * sizeof(int));
    printf("Enter the integer elements of the array: ");
    for (int i = 0; i < sizeOfInputArray; i++)
    {
        scanf("%d", &inputArray[i]);
    }

    int indexOfRepeatingMax = getIndexOfRepeatingMax(inputArray, sizeOfInputArray);
    if (indexOfRepeatingMax >= 0)
    {
        printf("The maximum repeating element: %d", inputArray[indexOfRepeatingMax]);
    }
    else
    {
        printf("There is no repeating element");
    }

    free(inputArray);

    return 0;
}
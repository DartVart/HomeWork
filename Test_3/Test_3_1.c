#include <stdio.h>
#include <stdlib.h>

const int initialSizeOfArray = 10;

int* scanArrayFromConsole(int* sizeOfArray)
{
    int newElement = 0;
    int currentArrayCapacity = initialSizeOfArray;

    printf("Enter elements (0 means end of input):\n");

    scanf("%d", &newElement);
    if (newElement == 0)
    {
        return NULL;
    }

    int* array = (int*) calloc(initialSizeOfArray, sizeof(int));

    while (newElement != 0)
    {
        if (*sizeOfArray == currentArrayCapacity)
        {
            currentArrayCapacity *= 2;
            array = (int*) realloc(array, currentArrayCapacity * sizeof(int));
        }

        array[*sizeOfArray] = newElement;
        (*sizeOfArray)++;
        scanf("%d", &newElement);
    }

    return array;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int array[], int leftElement, int rightElement)
{
    if (rightElement - leftElement < 1)
    {
        return;
    }

    int upIterator = leftElement;
    int downIterator = rightElement;
    int middleIndex = (leftElement + rightElement) / 2;
    int middle = array[middleIndex];

    while (upIterator < downIterator)
    {
        while (array[upIterator] < middle)
        {
            upIterator++;
        }

        while (array[downIterator] > middle)
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

int main()
{
    int sizeOfArray = 0;

    int* inputArray = scanArrayFromConsole(&sizeOfArray);
    if (inputArray == NULL)
    {
        printf("You have not entered a single number!\n");
        return 0;
    }

    quickSort(inputArray, 0, sizeOfArray - 1);

    printf("The entered elements are displayed in ascending order, without repetition in the format\n"
           "\"<number> - <how many times it was entered>\":\n");

    printf("%d - ", inputArray[0]);
    // one number already entered
    int numberOfEqualElements = 1;
    for (int i = 1; i < sizeOfArray; i++)
    {
        if (inputArray[i] == inputArray[i - 1])
        {
            numberOfEqualElements++;
        }
        else
        {
            printf("%d\n", numberOfEqualElements);
            printf("%d - ", inputArray[i]);
            numberOfEqualElements = 1;
        }
    }
    printf("%d\n", numberOfEqualElements);

    free(inputArray);
    return 0;
}

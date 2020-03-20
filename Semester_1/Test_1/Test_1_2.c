#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertSortEvenPositions(int array[], int sizeOfArray)
{
    int newElement = 0;
    int location = 0;

    for (int i = 2; i < sizeOfArray; i += 2)
    {
        newElement = array[i];
        location = i - 2;
        while (location >= 0 && array[location] > newElement)
        {
            array[location + 2] = array[location];
            location = location - 2;
        }
        array[location + 2] = newElement;
    }
}

void printArray(int array[], int sizeOfArray)
{
    printf("{");
    for (int i = 0; i < sizeOfArray - 1; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("%d}", array[sizeOfArray - 1]);

}

int* createArrayWithManualInput(int* sizeOfArray)
{
    int* array = NULL;
    *sizeOfArray = 0;
    int currentPositionForInput = 0;

    printf("Enter elements of array (To end the output, enter 0):" );
    int newElement = 0;
    scanf("%d", &newElement);

    for (int i = 1; newElement != 0; i++)
    {
        array = (int*)realloc(array,  (i * 10) * sizeof(int));
        for (int j = 0; newElement != 0 && j < 10; j++)
        {
            (*sizeOfArray)++;
            currentPositionForInput = (*sizeOfArray) - 1;
            array[currentPositionForInput] = newElement;
            scanf("%d", &newElement);
        }
    }

    return array;
}

int* createArrayWithRandomElements(int* sizeOfArray)
{
    srand(time(NULL));

    printf("Enter the array size: ");
    scanf("%d", sizeOfArray);
    printf("This array will be filled with random integers from 11 to 42.\n");

    int* array = (int*) malloc((*sizeOfArray) * sizeof(int));
    for (int i = 0; i < *sizeOfArray; i++)
    {
        array[i] = rand() % 32 + 11;
    }
    return array;
}

int main()
{
    int sizeOfArray = 0;
    int* array = NULL;
    int choiceOfArrayInput = 0;
    printf("If you want to enter the elements of the array manually, enter 1;\n");
    printf("If you want the array elements to fill up automatically, enter 2: ");
    scanf("%d", &choiceOfArrayInput);

    switch (choiceOfArrayInput)
    {
        case 1:
        {
            array = createArrayWithManualInput(&sizeOfArray);
            break;
        }
        case 2:
        {
            array = createArrayWithRandomElements(&sizeOfArray);
            break;
        }
        default:
        {
            break;
        }
    }


    printf("Source array:");
    printArray(array, sizeOfArray);
    printf("\n");

    insertSortEvenPositions(array, sizeOfArray);

    printf("Array with sorted even elements:");
    printArray(array, sizeOfArray);

    free(array);

    return 0;
}
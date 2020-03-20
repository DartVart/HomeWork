#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printTwoDimensionalArray(int** array, int numberOfRows, int numberOfColumns)
{
    for (int row = 0; row < numberOfRows; row++)
    {
        for (int column = 0; column < numberOfColumns; column++)
        {
            printf("%4d", array[row][column]);
        }
        printf("\n");
    }
}

enum Direction
{
    LEFT,
    RIGHT,
    DOWN,
    UP
};

void printPartOfColumnOrRow(int** array, enum Direction direction, int numberOfCharacterToPrint, int* currentRow, int* currentColumn)
{
    switch (direction)
    {
        case LEFT:
        {
            for (int i = 0; i < numberOfCharacterToPrint; i++)
            {
                (*currentColumn)--;
                printf("%d ", array[*currentRow][*currentColumn]);
            }
            break;
        }

        case RIGHT:
        {
            for (int i = 0; i < numberOfCharacterToPrint; i++)
            {
                (*currentColumn)++;
                printf("%d ", array[*currentRow][*currentColumn]);
            }
            break;
        }

        case DOWN:
        {
            for (int i = 0; i < numberOfCharacterToPrint; i++)
            {
                (*currentRow)++;
                printf("%d ", array[*currentRow][*currentColumn]);
            }
            break;
        }

        case UP:
        {
            for (int i = 0; i < numberOfCharacterToPrint; i++)
            {
                (*currentRow)--;
                printf("%d ", array[*currentRow][*currentColumn]);
            }
            break;
        }

        default:
        {
            break;
        }
    }
}

void printArrayInSpiral(int** array, int sizeOfSquareArray)
{
    bool isPrintingLeftOrDown = true;
    int currentRow = sizeOfSquareArray / 2;
    int currentColumn = sizeOfSquareArray / 2;

    printf("%d ", array[currentRow][currentColumn]);

    for (int i = 1; i < sizeOfSquareArray; i++)
    {
        if (isPrintingLeftOrDown)
        {
            printPartOfColumnOrRow(array, LEFT, i, &currentRow, &currentColumn);
            printPartOfColumnOrRow(array, DOWN, i, &currentRow, &currentColumn);
            isPrintingLeftOrDown = false;
        }
        else
        {
            printPartOfColumnOrRow(array, RIGHT, i, &currentRow, &currentColumn);
            printPartOfColumnOrRow(array, UP, i, &currentRow, &currentColumn);
            isPrintingLeftOrDown = true;
        }
    }

    printPartOfColumnOrRow(array, LEFT, sizeOfSquareArray - 1, &currentRow, &currentColumn);
}

void freeTwoDimensionalArray(int** array, int numberOfRows)
{
    for (int i = 0; i < numberOfRows; i++)
    {
        free(array[i]);
    }
    free(array);
}

int main()
{
    int sizeOfInputSquareArray = 0;
    printf("Enter the size of a two-dimensional array with the same odd number of rows and columns:");
    scanf("%d", &sizeOfInputSquareArray);

    int** inputArray = (int**) malloc(sizeOfInputSquareArray * sizeof(int*));
    for (int row = 0; row < sizeOfInputSquareArray; row++)
    {
        printf("Enter the integer elements of the rows number %d: ", row + 1);
        inputArray[row] = (int*) calloc(sizeOfInputSquareArray, sizeof(int));
        for (int column = 0; column < sizeOfInputSquareArray; column++)
        {
            scanf("%d", &inputArray[row][column]);
        }
    }

    printf("You entered the array:\n");
    printTwoDimensionalArray(inputArray, sizeOfInputSquareArray, sizeOfInputSquareArray);

    printf("The same array but printed in a spiral:\n");
    printArrayInSpiral(inputArray, sizeOfInputSquareArray);

    freeTwoDimensionalArray(inputArray, sizeOfInputSquareArray);

    return 0;
}
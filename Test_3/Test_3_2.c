#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// The function returns the column index with the minimum element.
int findMinimumInRow(double** array, int indexOfRow, int numberOfColumn)
{
    int resultColumnIndex = 0;
    for (int i = 0; i < numberOfColumn; i++)
    {
        if (array[indexOfRow][resultColumnIndex] > array[indexOfRow][i])
        {
            resultColumnIndex = i;
        }
    }
    return resultColumnIndex;
}

bool isMaximumInColumn(double** array, int indexOfRow, int indexOfColumn, int numberOfRows)
{
    for (int i = 0; i < numberOfRows; i++)
    {
        if (array[indexOfRow][indexOfColumn] < array[i][indexOfColumn])
        {
            return false;
        }
    }
    return true;
}

void freeTwoDimensionalArray(double** array, int numberOfRows)
{
    for (int i = 0; i < numberOfRows; i++)
    {
        free(array[i]);
    }
    free(array);
}

int main()
{
    int numberOfRows = 0;
    int numberOfColumns = 0;

    printf("Enter the number of rows:\n");
    scanf("%d", &numberOfRows);

    printf("Enter the number of columns:\n");
    scanf("%d", &numberOfColumns);

    double** inputArray = (double**) malloc(numberOfRows * sizeof(double*));
    for (int row = 0; row < numberOfRows; row++)
    {
        printf("Enter the integer elements of the rows number %d:\n", row);
        inputArray[row] = (double*) calloc(numberOfColumns, sizeof(double));
        for (int column = 0; column < numberOfColumns; column++)
        {
            scanf("%lf", &inputArray[row][column]);
        }
    }

    bool haveSaddlePoint = false;
    int columnIndexOfMinimumInRow = 0;
    for (int i = 0; i < numberOfRows; i++)
    {
        columnIndexOfMinimumInRow = findMinimumInRow(inputArray, i, numberOfColumns);
        for (int j = 0; j < numberOfColumns; j++)
        {
            if (inputArray[i][j] == inputArray[i][columnIndexOfMinimumInRow])
            {
                if (isMaximumInColumn(inputArray, i, columnIndexOfMinimumInRow, numberOfRows))
                {
                    if (haveSaddlePoint == false)
                    {
                        printf("The following elements are saddle points:\n");
                        haveSaddlePoint = true;
                    }
                    printf("%lf (row: %d, column: %d)\n", inputArray[i][j], i, j);
                }
            }
        }
    }

    if (haveSaddlePoint == false)
    {
        printf("%There are no saddle points in this array.");
    }
    freeTwoDimensionalArray(inputArray, numberOfRows);
    return 0;
}
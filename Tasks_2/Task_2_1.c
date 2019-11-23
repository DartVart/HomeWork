#include <stdio.h>
#include <stdlib.h>

int getMinimum(int a, int b)
{
    return (a < b) ? a : b;
}

void printPartitionOfNumber(int number, int maximumTermInPartition, int partition[], int currentNumberOfTerms)
{
    if (number == 0)
    {
        // Display the current partition.
        for (int i = 0; i < currentNumberOfTerms - 1; i++)
        {
            printf("%d + ", partition[i]);
        }
        printf("%d\n", partition[currentNumberOfTerms - 1]);

        return;
    }

    currentNumberOfTerms++;

    int maximumInCurrentPartOfPartition = getMinimum(number, maximumTermInPartition);
    for (int term = 1; term <= maximumInCurrentPartOfPartition; term++)
    {
        partition[currentNumberOfTerms - 1] = term;

        printPartitionOfNumber(number - term, term, partition, currentNumberOfTerms);
    }
}

int main()
{
    int inputNumber = 0;
    printf("Enter an integer from 2: ");
    scanf("%d", &inputNumber);

    printf("Partition of %d:\n ", inputNumber);

    int* partition = (int*) calloc(inputNumber, sizeof(int));
    printPartitionOfNumber(inputNumber, inputNumber - 1, partition, 0);

    free(partition);

    return 0;
}

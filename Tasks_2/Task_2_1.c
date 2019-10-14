#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxSizeOfAddingString = 10;

int getMinimum(int a, int b)
{
    return (a < b) ? a : b;
}

//This method doesn't change amount of memory allocated for the string
void shortenString(char string[], int newLengthOfString)
{
    string[newLengthOfString] = '\0';
}

void printPartitionOfNumber(int number, int maximumTermInPartition, char* partOfPartition, int lengthOfPreviousAddingString)
{
    int lengthOfPartOfPartition = strlen(partOfPartition);
    int lengthOfPartitionWithoutLastTerm = lengthOfPartOfPartition - lengthOfPreviousAddingString;

    if (number == 0)
    {
        int lengthOfPartitionWithoutLastPlus = lengthOfPartOfPartition - 2;
        shortenString(partOfPartition, lengthOfPartitionWithoutLastPlus);

        printf("%s\n", partOfPartition);

        shortenString(partOfPartition, lengthOfPartitionWithoutLastTerm);
        return;
    }

    int lengthOfExtendedPartOfPartition = 0;
    int lengthOfAddingString = 0;
    int maximumTermInCurrentPartOfPartition = getMinimum(number, maximumTermInPartition);
    for (int term = 1; term <= maximumTermInCurrentPartOfPartition; term++)
    {
        char addingString[maxSizeOfAddingString] = "";
        itoa(term, addingString, 10);
        strcat(addingString, " + ");
        lengthOfAddingString = strlen(addingString);

        lengthOfExtendedPartOfPartition = lengthOfPartOfPartition + lengthOfAddingString + 1;
        partOfPartition = (char*) realloc(partOfPartition, (lengthOfExtendedPartOfPartition) * sizeof(char));

        strcat(partOfPartition, addingString);

        printPartitionOfNumber(number - term, term, partOfPartition, lengthOfAddingString);
    }

    shortenString(partOfPartition, lengthOfPartitionWithoutLastTerm);
}

int main()
{
    int inputNumber = 0;
    printf("Enter an integer from 2: ");
    scanf("%d", &inputNumber);

    printf("Partition of %d:\n ", inputNumber);

    char* partition = (char*) calloc(0 , sizeof(char));
    printPartitionOfNumber(inputNumber, inputNumber - 1, partition, 0);

    free(partition);

    return 0;
}


#include <stdio.h>
#include <string.h>

const int maxSizeOfString = 1002;

int main()
{
    char inputString[maxSizeOfString] = "";
    int initialNumberOfSpaces = 0;
    int newLengthOfString = 0;

    // A length is (maxSizeOfString - 2), taking into account characters '\0' and '\n'
    printf("Enter a string with a maximum length of %d:", maxSizeOfString - 2);
    fgets(inputString, maxSizeOfString, stdin);

    int initialLengthOfString = strlen(inputString);

    // Delete the character '\n'
    inputString[initialLengthOfString - 1] = '\0';
    initialLengthOfString--;

    for (int i = 0; i < initialLengthOfString; i++)
    {
        if (inputString[i] == ' ')
        {
            initialNumberOfSpaces++;
        }
    }

    if (initialNumberOfSpaces == 0)
    {
        printf("ERROR. There must be more than one word in a line!");
        return 0;
    }

    printf("Enter new length: ");
    scanf("%d", &newLengthOfString);

    int differenceBetweenLengths = newLengthOfString - initialLengthOfString;

    int totalNumberOfSpacesInNewString = differenceBetweenLengths + initialNumberOfSpaces;
    int minimumNumberOfSpacesBetweenWords = totalNumberOfSpacesInNewString / initialNumberOfSpaces;

    int numberOfPartsWithMaximumNumberOfSpaces = totalNumberOfSpacesInNewString % initialNumberOfSpaces;

    printf("String with new length: \n");

    printf("\"");
    for (int i = 0; i < initialLengthOfString; i++)
    {
        printf("%c", inputString[i]);
        if (inputString[i] == ' ')
        {
            // (minimumNumberOfSpacesBetweenWords - 1) spaces prints as one space is already printed
            for (int j = 0; j < minimumNumberOfSpacesBetweenWords - 1; j++)
            {
                printf(" ");
            }

            if (numberOfPartsWithMaximumNumberOfSpaces > 0)
            {
                printf(" ");
                numberOfPartsWithMaximumNumberOfSpaces--;
            }
        }
    }
    printf("\"");

    return 0;
}
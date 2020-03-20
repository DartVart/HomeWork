#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int maxSizeOfString = 1000;

bool isStringEmpty(char string[])
{
    int lengthOfString = strlen(string);
    for (int i = 0; i < lengthOfString; i++)
    {
        if (string[i] != '\n' &&
            string[i] != '\t' &&
            string[i] != ' ')
        {
            return false;
        }
    }
    return true;
}

int main()
{
    char nameOfFile[] = "input.txt";
    FILE* file = fopen(nameOfFile, "r");

    if (file == NULL)
    {
        printf("Failed to open \"%s\".", nameOfFile);
        return -1;
    }

    int numberOfNonEmptyStrings = 0;
    char inputString[maxSizeOfString] = "";

    while (!feof(file))
    {
        fgets(inputString, maxSizeOfString, file);
        if (!isStringEmpty(inputString))
        {
            numberOfNonEmptyStrings++;
        }
    }

    printf("Number of non-empty strings in the file \"%s\": %d",  nameOfFile, numberOfNonEmptyStrings);

    fclose(file);

    return 0;
}
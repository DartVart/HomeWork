#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int numberOfSymbols = 256;
const int maxSizeOfString = 1000;

bool isAnagram(char firstString[], char secondString[])
{
    int lengthOfFirstString = strlen(firstString);

    if (lengthOfFirstString != strlen(secondString))
    {
        return false;
    }

    int symbols[numberOfSymbols] = {0};
    for (int i = 0; i < lengthOfFirstString; i++)
    {
        symbols[(int)firstString[i]]++;
        symbols[(int)secondString[i]]--;
    }

    for (int i = 0; i < numberOfSymbols; i++)
    {
        if (symbols[i] != 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    char firstString[maxSizeOfString] = "";
    char secondString[maxSizeOfString] = "";

    printf("Enter the first string: ");
    scanf("%s", firstString);

    printf("Enter the second string: ");
    scanf("%s", secondString);

    if (isAnagram(firstString, secondString))
    {
        printf("You can get \"%s\" from \"%s\" by reposition the characters.", secondString, firstString);
    }
    else
    {
        printf("You cannot get \"%s\" from \"%s\" by reposition the characters.", secondString, firstString);
    }

    return 0;
}
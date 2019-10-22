#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int numberOfCharacters = (int)'z' - (int)'A' + 1;
const int numberOfFirstUsedCharacter = (int)'A';
const int maxSizeOfString = 1000;

bool isAnagram(char firstString[], char secondString[])
{
    int lengthOfFirstString = strlen(firstString);
    int lengthOfSecondString = strlen(secondString);
    int indexOfCharacter = 0;


    if (lengthOfFirstString != lengthOfSecondString)
    {
        return false;
    }

    int symbols[numberOfCharacters] = {0};
    for (int i = 0; i < lengthOfFirstString; i++)
    {

        indexOfCharacter = (int)firstString[i] - numberOfFirstUsedCharacter;
        symbols[indexOfCharacter]++;
        indexOfCharacter = (int)secondString[i] - numberOfFirstUsedCharacter;
        symbols[indexOfCharacter]--;
    }

    for (int i = 0; i < numberOfCharacters; i++)
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
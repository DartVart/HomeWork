#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int maxSizeOfString = 1001;

bool isPalindrome(char checkingString[], int lengthOfString)
{
    int halfLengthOfString = lengthOfString / 2;
    for (int i = 0; i < halfLengthOfString; i++)
    {
        if (checkingString[i] != checkingString[lengthOfString - 1 - i])
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    char inputString[maxSizeOfString] = "";

    printf("Enter a string with a maximum of %d characters and no spaces: ", maxSizeOfString - 1);
    scanf("%s", inputString);

    if (isPalindrome(inputString, strlen(inputString)))
    {
        printf("The string \"%s\" is a palindrome." , inputString);
    }
    else
    {
        printf("The string \"%s\" isn't a palindrome." , inputString);
    }

    return 0;
}
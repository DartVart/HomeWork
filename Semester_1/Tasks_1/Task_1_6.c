#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int maxSizeOfString = 1000;

int getNumberOfSubstring(char string[], char substring[])
{
    bool isEqual = false;
    int result = 0;
    int lengthOfSubstring = strlen(substring);
    int lengthOfString = strlen(string);

    for (int i = 0; i + lengthOfSubstring <= lengthOfString; i++)
    {
        isEqual = true;

        for (int j = 0; j < lengthOfSubstring; j++)
        {
            if (string[j + i] != substring[j])
            {
                isEqual = false;
            }
        }

        if (isEqual)
        {
            result++;
        }
    }

    return result;
}

int main()
{
    char checkingString[maxSizeOfString] = "";
    char substring[maxSizeOfString] = "";

    printf("Enter the substring, %d symbols maximum: ", maxSizeOfString);
    scanf("%s", substring);
    printf("Enter the checking string, %d symbols maximum: ", maxSizeOfString);
    scanf("%s", checkingString);

    printf("The number of entry of the first string in the second: ");
    printf("%d", getNumberOfSubstring(checkingString, substring));

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "myString.h"

void printStringData(MyString* string)
{
    printf("\"");
    printString(string, stdout);
    printf("\" (length = %d)\n", getLengthOfString(string));
}

void displayClonedString(MyString* sourceString)
{
    printf("Clone string.\n");
    printf("Source string: ");
    printStringData(sourceString);
    MyString* clonedString = cloneString(sourceString);
    printf("Cloned string: ");
    printStringData(clonedString);
    deleteString(clonedString);
}

void displayStringAfterConcatenation(MyString* destinationString, MyString* addedString)
{
    printf("String concatenation.\n");
    printf("Destination string: ");
    printStringData(destinationString);
    printf("Added string: ");
    printStringData(addedString);
    concatenateStrings(destinationString, addedString);
    printf("String after concatenation: ");
    printStringData(destinationString);
}

void displayCheckingForEmptiness(MyString* string)
{
    printf("Checking for emptiness. \n");
    printf("String: ");
    printStringData(string);
    if (isStringEmpty(string))
    {
        printf("String is empty.\n");
    }
    else
    {
        printf("String isn't empty.\n");
    }
}

void displayCheckingForEquivalence(MyString* firstString, MyString* secondString)
{
    printf("Checking for equivalence. \n");
    printf("First string: ");
    printStringData(firstString);
    printf("Second string: ");
    printStringData(secondString);
    if (areStringEqual(firstString, secondString))
    {
        printf("Strings are equal.\n");
    }
    else
    {
        printf("String aren't equal.\n");
    }

}

void conversionToCharArrayTest(MyString* string)
{
    printf("Conversion string to char array.\n");
    printf("String to convert: ");
    printStringData(string);
    char* charArray = convertStringToCharArray(string);
    printf("Converted char array: \"%s\"\n", charArray);
    free(charArray);
}

void conversionToMyStringTest(char* charArray)
{
    printf("Conversion char array to string.\n");
    printf("Char array to convert: \"%s\"\n", charArray);
    MyString* string = convertCharArrayToString(charArray);
    printf("Converted string: ");
    printStringData(string);
    deleteString(string);
}

void displaySubstring(MyString* sourceString, int firstIndex, int lastIndex)
{
    printf("Taking substring.\n");
    printf("Source string: ");
    printStringData(sourceString);
    printf("Substring (from %d to %d index): ", firstIndex, lastIndex);
    MyString* substring = getSubstring(sourceString, firstIndex, lastIndex);
    printStringData(substring);
    deleteString(substring);
}

void test()
{
    printf("Enter any two strings:\n");
    MyString* firstString = getStringFromStream(stdin, readingWithSpaces);
    MyString* secondString = getStringFromStream(stdin, readingWithSpaces);

    displayClonedString(firstString);
    printf("\n");

    displayCheckingForEmptiness(firstString);
    printf("\n");

    displayCheckingForEquivalence(firstString, secondString);
    printf("\n");

    conversionToMyStringTest("hot dog");
    printf("\n");

    conversionToCharArrayTest(firstString);
    printf("\n");

    displaySubstring(firstString, 2, 7);
    printf("\n");

    displayStringAfterConcatenation(firstString, secondString);
    printf("\n");

    deleteString(firstString);
    deleteString(secondString);
}

int main()
{
    test();
    return 0;
}

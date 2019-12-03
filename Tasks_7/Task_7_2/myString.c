#include <stdlib.h>
#include <string.h>
#include "myString.h"

MyString createString(char* charArray)
{
    int lengthOfString = strlen(charArray);
    MyString* newString = (MyString*) malloc(sizeof(MyString));
    newString->size = lengthOfString;
    newString->array = (char*) malloc(lengthOfString * sizeof(char));

    for (int i = 0; i < lengthOfString; i++)
    {
        newString->array[i] = charArray[i];
    }

    return *newString;
}

void cloneString(MyString* firstString, MyString* secondString)
{
    int lengthOfString = firstString->size;
    free(secondString);
    secondString = (MyString*) malloc(sizeof(MyString));
    secondString->size = lengthOfString;
    secondString->array = (char*) malloc(lengthOfString * sizeof(char));

    for (int i = 0; i < lengthOfString; i++)
    {
        secondString->array[i] = firstString->array[i];
    }
}

void concatenationOfString(MyString* first, MyString* second)
{
    int newLength = first->size + second->size;
    first->array = (char*) realloc(first->array, newLength * sizeof(char));

    int indexOfSecond = 0;
    for (int i = 0, j = first->size; i < second->size; i++, j++)
    {
        first->array[j] = second->array[i];
    }

    first->size = newLength;
}

bool isStringEqual(MyString* first, MyString* second)
{
    if (first->size != second->size)
    {
        return false;
    }

    for (int i = 0; i < first->size; i++)
    {
        if (first->array[i] != second->array[i])
        {
            return false;
        }
    }

    return true;
}

int getSizeOfString(MyString* string)
{
    return string->size;
}

bool isStringEmpty(MyString* string)
{
    return string->size == 0;
}

char* stringToChar(MyString* string)
{
    int sizeOfCharArray = string->size + 1;
    char* newCharArray = (char*) malloc(sizeOfCharArray * sizeof(char));

    for (int i = 0; i < string->size; i++)
    {
        newCharArray[i] = string->array[i];
    }
    newCharArray[sizeOfCharArray - 1] = '\0';

    return newCharArray;
}

void charToString(MyString* string, char charArray[])
{
    int lengthOfString = strlen(charArray);
    if (string->size != lengthOfString)
    {
        ////why no realloc??????????
        free(string->array);
        string->array = (char*) malloc(lengthOfString * sizeof(char));
    }

    for (int i = 0; i < lengthOfString; i++)
    {
        string->array[i] = charArray[i];
    }
}

MyString* getSubstring(MyString* string, int firstIndex, int secondIndex)
{
    if (firstIndex < 0)
    {
        firstIndex += string->size;
    }

    if (secondIndex < 0)
    {
        secondIndex += string->size;
    }

    if (firstIndex >= string->size ||
        secondIndex >= string->size)
    {
        return NULL;
    }

    int sizeOfSubstring = abs(firstIndex - secondIndex) + 1;

    MyString* substring = (MyString*) malloc(sizeof(MyString));
    substring->size = sizeOfSubstring;
    substring->array = (char*) malloc(sizeOfSubstring * sizeof(char));

    int indexing = (secondIndex - firstIndex > 0) ? 1 : -1;
    for (int i = 0, j = firstIndex; i < sizeOfSubstring; i++, j += indexing)
    {
        substring->array[i] = string->array[j];
    }

    return substring;
}

void printString(MyString* string, struct _iobuf* stream)
{
    char* charArray = stringToChar(string);
    fprintf(stream,"%s", charArray);
}

void deleteString(MyString* string)
{
    free(string->array);
    free(string);
}
#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef enum ReadingType
{
    readingWithSpaces = 0,
    readingWithoutSpaces = 1
} ReadingType;

typedef struct MyString MyString;

/* The function creates an empty string. */
MyString* createString();

/* If (sourceString == NULL), the function will return NULL. */
MyString* cloneString(MyString* sourceString);

/* If (destinationString == NULL) or (addedString == NULL), the function will return false. */
bool concatenateStrings(MyString* destinationString, MyString* addedString);

/* If (firstString == NULL) or (secondString == NULL), the function will return false. */
bool areStringEqual(MyString* firstString, MyString* secondString);

/* If (string == NULL), the function will return -1. */
int getLengthOfString(MyString* string);

bool isStringEmpty(MyString* string);

/* If (string == NULL), the function will return NULL.
 * If (firstIndex < 0), then it will be assigned 0.
 * If (firstIndex > (length of string) - 1), then 'firstIndex' will be assigned ((length of string) - 1).
 * If (firstIndex > lastIndex), the function will return empty string. */
MyString* getSubstring(MyString* string, int firstIndex, int lastIndex);

/* If (string == NULL), the function will return NULL. */
char* convertStringToCharArray(MyString* string);

/* If (charArray == NULL), the function will return NULL. */
MyString* convertCharArrayToString(char* charArray);

/* If (string == NULL) or (stream == NULL), the function will return false. */
bool printString(MyString* string, FILE* outputStream);

/* If (readingType == readingWithoutSpaces), the function reads a non-empty string
 * until a '\n' or '\t' or '\r' is found, not including it.
 * If (readingType == readingWithoutSpaces), then the character ' ' is added to the delimiter characters.
 * The function will return NULL if the file ended before reading a string or (inputStream == NULL). */
MyString* getStringFromStream(FILE* inputStream, ReadingType readingType);

void deleteString(MyString* string);
#include <stdlib.h>
#include <string.h>
#include "myString.h"

struct MyString
{
    char* content;
    int length;
};

MyString* createString()
{
    MyString* newString = (MyString*) malloc(sizeof(MyString));
    newString->length = 0;
    newString->content = calloc(1, sizeof(char));
    return newString;
}

bool isStringEmpty(MyString* string)
{
    return string == NULL || string->content == NULL || string->length == 0;
}

int getLengthOfString(MyString* string)
{
    if (string != NULL && string->content != NULL)
    {
        return string->length;
    }
    return -1;
}

/* If (string == NULL), the function will return false. */
bool resizeString(MyString* string, int newLength)
{
    if (string == NULL || string->content == NULL)
    {
        return false;
    }
    char* contentWithNewLength = calloc((newLength + 1), sizeof(char));
    strcpy(contentWithNewLength, string->content);
    free(string->content);
    string->content = contentWithNewLength;
    string->length = newLength;
    return true;
}

MyString* cloneString(MyString* sourceString)
{
    if (sourceString == NULL || sourceString->content == NULL)
    {
        return NULL;
    }
    MyString* newString = createString();
    resizeString(newString, sourceString->length);
    strcpy(newString->content, sourceString->content);
    return newString;
}

bool concatenateStrings(MyString* destinationString, MyString* addedString)
{
    if (destinationString == NULL || addedString == NULL)
    {
        return false;
    }
    int newLength = destinationString->length + addedString->length;
    resizeString(destinationString, newLength);
    strcat(destinationString->content, addedString->content);
    return true;
}

bool areStringEqual(MyString* firstString, MyString* secondString)
{
    return firstString != NULL && secondString != NULL &&
           firstString->length == secondString->length &&
           strcmp(firstString->content, secondString->content) == 0;
}

char* convertStringToCharArray(MyString* string)
{
    if (string == NULL || string->content == NULL)
    {
        return NULL;
    }
    char* charArray = calloc(string->length + 1, sizeof(char));
    strcpy(charArray, string->content);
    return charArray;
}

MyString* convertCharArrayToString(char* charArray)
{
    if (charArray == NULL)
    {
        return NULL;
    }

    int length = strlen(charArray);
    MyString* newString = createString();
    resizeString(newString, length);
    strcpy(newString->content, charArray);
    return newString;
}

MyString* getSubstring(MyString* sourceString, int firstIndex, int lastIndex)
{
    if (sourceString == NULL || sourceString->content == NULL)
    {
        return NULL;
    }

    if (firstIndex < 0)
    {
        firstIndex = 0;
    }
    if (lastIndex > sourceString->length - 1)
    {
        lastIndex = sourceString->length - 1;
    }
    if (firstIndex > lastIndex)
    {
        return createString();
    }

    int lengthOfSubstring = lastIndex - firstIndex + 1;
    MyString* substring = createString();
    resizeString(substring, lengthOfSubstring);
    strncpy(substring->content, sourceString->content + firstIndex, lengthOfSubstring);
    return substring;
}

bool printString(MyString* string, FILE* outputStream)
{
    if (string == NULL || string->content == NULL || outputStream == NULL)
    {
        return false;
    }
    fprintf(outputStream, "%s", string->content);
    return true;
}

/* The function moves the stream position indicator to the first character
 * that is not equal to the character recorded in the 'symbol'.
 * The function returns false if the end of the file is reached or (inputStream == NULL). */
bool ignoreSymbolsInInputStream(char* symbols, FILE* inputStream)
{
    if (inputStream == NULL)
    {
        return false;
    }

    int readingSymbol = 0;
    do
    {
        readingSymbol = fgetc(inputStream);
        if (readingSymbol == EOF)
        {
            return false;
        }
    } while (strchr(symbols, readingSymbol) != NULL);

    ungetc(readingSymbol, inputStream);
    return true;
}

MyString* getDelimitedStringFromStream(char* delimiters, FILE* inputStream)
{
    bool isReadingCorrect = ignoreSymbolsInInputStream(delimiters, inputStream);
    if (!isReadingCorrect)
    {
        return NULL;
    }

    MyString* stringBuffer = createString();
    int currentCapacity = stringBuffer->length + 1;
    int currentLength = stringBuffer->length;
    resizeString(stringBuffer, currentCapacity);
    int readingSymbolKey = fgetc(inputStream);
    do
    {
        stringBuffer->content[currentLength] = (char) readingSymbolKey;
        currentLength++;
        readingSymbolKey = fgetc(inputStream);

        if (currentLength == currentCapacity)
        {
            currentCapacity *= 2;
            resizeString(stringBuffer, currentCapacity);
        }
    } while (readingSymbolKey != EOF && strchr(delimiters, readingSymbolKey) == NULL);

    stringBuffer->content[currentLength] = '\0';
    resizeString(stringBuffer, currentLength);
    return stringBuffer;
}

MyString* getStringFromStream(FILE* inputStream, ReadingType readingType)
{
    switch (readingType)
    {
        case readingWithoutSpaces:
        {
            return getDelimitedStringFromStream("\n\r\t ", inputStream);
        }
        case readingWithSpaces:
        {
            return getDelimitedStringFromStream("\n\r\t", inputStream);
        }
        default:
        {
            return NULL;
        }
    }
}

void deleteString(MyString* string)
{
    if (string != NULL)
    {
        free(string->content);
    }
    free(string);
}
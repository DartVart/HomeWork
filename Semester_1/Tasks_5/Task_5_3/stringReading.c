#include <string.h>
#include <stdlib.h>
#include "stringReading.h"

const int initialStringCapacity = 10;

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

char* getDelimitedStringFromStream(char* delimiters, FILE* inputStream)
{
    bool isReadingCorrect = ignoreSymbolsInInputStream(delimiters, inputStream);
    if (!isReadingCorrect)
    {
        return NULL;
    }

    char* stringBuffer = (char*) malloc(initialStringCapacity * sizeof(char));
    int lengthOfString = 0;
    int currentCapacity = initialStringCapacity;
    int readingSymbolKey = fgetc(inputStream);

    do
    {
        stringBuffer[lengthOfString] = (char) readingSymbolKey;
        lengthOfString++;
        readingSymbolKey = fgetc(inputStream);

        if (lengthOfString == currentCapacity)
        {
            currentCapacity *= 2;
            stringBuffer = (char*) realloc(stringBuffer, currentCapacity * sizeof(char));
        }

    } while (readingSymbolKey != EOF && strchr(delimiters, readingSymbolKey) == NULL);

    stringBuffer[lengthOfString] = '\0';
    return stringBuffer;
}

char* getStringFromStream(FILE* inputStream, ReadingType readingType)
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
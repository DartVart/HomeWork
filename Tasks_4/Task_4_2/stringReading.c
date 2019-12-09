#include <string.h>
#include "stringReading.h"

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

bool scanDelimitedString(char* delimiters, FILE* inputStream, char* stringBuffer,
                         int maxLengthOfString)
{
    bool isReadingCorrect = ignoreSymbolsInInputStream(delimiters, inputStream);
    if (!isReadingCorrect)
    {
        return false;
    }

    int readingSymbolKey = 0;
    int currentLength = 0;
    readingSymbolKey = fgetc(inputStream);

    do
    {
        stringBuffer[currentLength] = (char)readingSymbolKey;
        currentLength++;
        readingSymbolKey = fgetc(inputStream);

    } while (readingSymbolKey != EOF &&
             strchr(delimiters, readingSymbolKey) == NULL &&
             currentLength < maxLengthOfString - 1);

    stringBuffer[currentLength] = '\0';
    return true;
}

bool scanStringWithSpaces(FILE* inputStream, char* stringBuffer, int maxLengthOfString)
{
    bool isCorrectScanning = scanDelimitedString("\n\t", inputStream,
                                                 stringBuffer, maxLengthOfString);
    return isCorrectScanning;
}

bool scanString(FILE* inputStream, char* stringBuffer, int maxLengthOfString)
{
    bool isCorrectScanning = scanDelimitedString("\n\t ", inputStream,
                                                 stringBuffer, maxLengthOfString);
    return isCorrectScanning;
}
#include <string.h>
#include "stringReading.h"

/* The function moves the stream position indicator to the first character
 * that is not equal to the character recorded in the 'symbol'.
 * The function returns false if the end of the file is reached or (inputStream == NULL). */
bool ignoreSymbolInInputStream(char symbol, FILE* inputStream)
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
    } while (readingSymbol == symbol);

    ungetc(readingSymbol, inputStream);
    return true;
}

bool scanStringWithSpaces(FILE* inputStream, char* stringBuffer, int maxLengthOfString)
{
    bool isReadingCorrect = ignoreSymbolInInputStream('\n', inputStream);
    if (!isReadingCorrect)
    {
        return false;
    }

    fgets(stringBuffer, maxLengthOfString, inputStream);
    int indexOfLastCharacterInString = strlen(stringBuffer) - 1;
    if (stringBuffer[indexOfLastCharacterInString] == '\n')
    {
        stringBuffer[indexOfLastCharacterInString] = '\0';
    }

    return true;
}

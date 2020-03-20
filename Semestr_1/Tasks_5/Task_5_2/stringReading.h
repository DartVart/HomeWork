/**
 * This module implements reading a string (char array)
 * */

#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef enum ReadingType
{
    readingWithSpaces = 0,
    readingWithoutSpaces = 1
} ReadingType;

/* If (readingType == readingWithoutSpaces), the function reads a non-empty string
 * until a '\n' or '\t' or '\r' is found, not including it.
 * If (readingType == readingWithoutSpaces), then the character ' ' is added to the delimiter characters.
 * The function will return NULL if the file ended before reading a string or (inputStream == NULL). */
char* getStringFromStream(FILE* inputStream, ReadingType readingType);
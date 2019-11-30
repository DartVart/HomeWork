/**
 * This module implements safe reading a string (char array) with spaces
 * */

#pragma once

#include <stdbool.h>
#include <stdio.h>

/* The function reads a non-empty string until a '\n' is found, not including it.
 * The function will return 'false' if the file ended before reading a string or (inputStream == NULL). */
bool scanStringWithSpaces(FILE* inputStream, char* stringBuffer, int maxLengthOfString);
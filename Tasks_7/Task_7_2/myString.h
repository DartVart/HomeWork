#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stdio.h>

typedef struct MyString MyString;
struct MyString
{
    char* array;
    int size;
};

MyString createString(char* charArray);

//////////////bool????????//////////////first??????????????
void cloneString(MyString* firstString, MyString* SecondString);////???///???//???//???///???///??///???///?

void concatenationOfString(MyString* first, MyString* second);

bool isStringEqual(MyString* first, MyString* second);

int getSizeOfString(MyString* string);

bool isStringEmpty(MyString* string);

MyString* getSubstring(MyString* string, int firstIndex, int secondIndex);

char* stringToChar(MyString* string);

void charToString(MyString* string, char charArray[]);

////////////////////??????????????????????/////////////////////////
void printString(MyString* string, struct _iobuf* stream);

void deleteString(MyString* string);

#endif //STRING_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

const int maxSizeOfString = 1000;

bool isDigit(char symbol)
{
    return '0' <= symbol && '9' >= symbol;
}

typedef struct Date Date;
struct Date
{
    int day;
    int month;
    int year;
};

bool isDateLess(Date firstData, Date secondData)
{
    if (firstData.year < secondData.year)
    {
        return true;
    }
    else if (firstData.year == secondData.year)
    {
        if (firstData.month < secondData.month)
        {
            return true;
        }
        else if (firstData.month == secondData.month)
        {
            if (firstData.day < secondData.day)
            {
                return true;
            }
        }
    }

    return false;
}

bool isStringIsDate(char string[])
{
    int lengthOfString = strlen(string);
    return (lengthOfString == 10 &&
        isDigit(string[0]) &&
        isDigit(string[1]) &&
        string[2] == '.' &&
        isDigit(string[3]) &&
        isDigit(string[4]) &&
        string[5] == '.'&&
        isDigit(string[6]) &&
        isDigit(string[7]) &&
        isDigit(string[8]) &&
        isDigit(string[9]));
}

void stringToDate(char dateAsString[], Date *date)
{
    sscanf(dateAsString, "%d.%d.%d", &date->day, &date->month, &date->year);
}

int main()
{
    char* nameOfFile = "text.txt";
    FILE* inputFile = fopen(nameOfFile, "a+");

    Date smallestDate = {31, 12, 9999};
    Date currentDate = {0, 0, 0};

    char currentString[maxSizeOfString] = "";
    while (!feof(inputFile))
    {
       fscanf(inputFile, "%s", currentString);

       if (isStringIsDate(currentString))
       {
           stringToDate(currentString, &currentDate);
           if (isDateLess(currentDate, smallestDate))
           {
               smallestDate.year = currentDate.year;
               smallestDate.month = currentDate.month;
               smallestDate.day = currentDate.day;
           }
       }
    }

    printf("Smallest data in the file \"%s\": %d.%d.%d", nameOfFile, smallestDate.day, smallestDate.month, smallestDate.year);

    fclose(inputFile);

    return 0;
}
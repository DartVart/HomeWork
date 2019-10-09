#include <stdio.h>

const int numberOfDigits = 10;

unsigned long long getMinNumberFormedByDigits(unsigned long long number)
{
    if (number == 0)
    {
        return 0;
    }

    unsigned long long result = 0;

    int digitsOfNumber[numberOfDigits] = {0};

    int lastDigitOfNumber = 0;
    while (number > 0)
    {
        lastDigitOfNumber = number % 10;
        digitsOfNumber[lastDigitOfNumber]++;
        number /= 10;
    }

    int smallestNonzeroDigit = 0;
    for (int digit = 1; smallestNonzeroDigit == 0; digit++)
    {
        if (digitsOfNumber[digit] != 0)
        {
            smallestNonzeroDigit = digit;
            digitsOfNumber[smallestNonzeroDigit]--;
        }
    }

    result = smallestNonzeroDigit;

    for (int currentDigitOfNumber = 0; currentDigitOfNumber < numberOfDigits; currentDigitOfNumber++)
    {
        for (int i = 0; i < digitsOfNumber[currentDigitOfNumber]; i++)
        {
            result = result * 10 + currentDigitOfNumber;
        }
    }

    return result;
}

int main()
{
    unsigned long long inputNumber = 0;
    printf("Enter an integer: ");
    scanf("%llu", &inputNumber);

    printf("Smallest number formed by digits of the number %llu: %llu", inputNumber, getMinNumberFormedByDigits(inputNumber));

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int numberOfBitsInDouble = 64;
const int numberOfBytesInDouble = 8;
const int numberOfBitsInExponent = 11;
const int numberOfBitsInMantissa = 52;
const int exponentBias = 1023;

// The program uses the binary representation of a number in reverse order.
const int indexOfFirstExponentBit = numberOfBitsInDouble - 2; // 62
const int indexOfLastExponentBit = numberOfBitsInDouble - numberOfBitsInExponent - 1; // 52

typedef union RealNumber
{
    double value;
    char bytes[8];
} RealNumber;

int* getBinaryRepresentation(RealNumber number)
{
    int currentIndex = 0;
    int bit = 0;
    int* binaryRepresentation = (int*) calloc(numberOfBitsInDouble, sizeof(int));
    for (int i = numberOfBytesInDouble - 1; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            bit = number.bytes[i] & 1;
            currentIndex = i * 8 + j;
            binaryRepresentation[currentIndex] = bit;
            number.bytes[i] >>= 1;
        }
    }
    return binaryRepresentation;
}

/* If (binaryRepresentation == NULL), the function will return '\0'. */
char getSignOfNumber(const int* binaryRepresentation)
{
    if (binaryRepresentation == NULL)
    {
        return '\0';
    }
    if (binaryRepresentation[numberOfBitsInDouble - 1] == 0)
    {
        return '+';
    }
    return '-'; // binaryRepresentation[numberOfBitsInDouble - 1] == 1
}

/* If (binaryRepresentation == NULL), the function will return 0. */
int getExponent(const int* binaryRepresentation)
{
    if (binaryRepresentation == NULL)
    {
        return 0;
    }
    int exponent = 0;
    for (int i = indexOfFirstExponentBit; i >= indexOfLastExponentBit; i--)
    {
        exponent <<= 1;
        exponent += binaryRepresentation[i];
    }
    exponent -= exponentBias;
    return exponent;
}

/* If (binaryRepresentation == NULL), the function will return 0.0 */
double getMantissa(const int* binaryRepresentation)
{
    if (binaryRepresentation == NULL)
    {
        return 0.0;
    }
    double mantissa = 0.0;
    for (int i = 0; i < numberOfBitsInMantissa; i++)
    {
        mantissa += binaryRepresentation[i];
        mantissa /= 2;
    }
    return mantissa + 1;
}

void displayInExponentialForm(double value)
{
    RealNumber number = {value};
    int* binaryRepresentation = getBinaryRepresentation(number);
    char sign = ' ';
    int exponent = 0;
    double mantissa = 0.0;
    if (value != 0.0)
    {
        sign = getSignOfNumber(binaryRepresentation);
        exponent = getExponent(binaryRepresentation);
        mantissa = getMantissa(binaryRepresentation);
    }
    printf("The exponential notation of the number %lf: %c%.10lf * 2^(%d)\n", value, sign, mantissa, exponent);
    free(binaryRepresentation);
}

bool scanNumber(double* number)
{
    return scanf("%lf", number) == 1;
}

int main()
{
    double inputNumber;
    printf("Enter a real number:\n");
    bool isCorrectInput = scanNumber(&inputNumber);
    if (!isCorrectInput)
    {
        fprintf(stderr, "Error. Incorrect Input.");
        return -1;
    }

    displayInExponentialForm(inputNumber);
    return 0;
}
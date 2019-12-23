#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

const int numberOfBitsInInteger = 32;
const int numberOfBytesInInteger = 4;
const int minimumInteger = -2147483648; // -2^31
const int maximumInteger = 2147483647; // 2^31 - 1

/* If the number is not in the range of 4-byte integers, the function will return NULL.
 * The function returns the binary representation (two's complement) in reverse order. */
int* getBinaryForm(long int number)
{
    if (number > maximumInteger || number < minimumInteger)
    {
        return NULL;
    }
    int bit = 0;
    int* binaryForm = (int*) calloc(numberOfBitsInInteger, sizeof(int));
    for (int i = 0; i < numberOfBitsInInteger; i++)
    {
        bit = number & 1;
        binaryForm[i] = bit;
        number >>= 1;
    }
    return binaryForm;
}

/* If (binaryForm == NULL), the function will return false. */
bool displayBinaryForm(int* binaryForm)
{
    if (binaryForm == NULL)
    {
        return false;
    }
    int currentIndex = 0;
    for (int byteNumber = numberOfBytesInInteger - 1; byteNumber >= 0; byteNumber--)
    {
        for (int i = 7; i >= 0; i--)
        {
            currentIndex = byteNumber * 8 + i;
            printf("%d", binaryForm[currentIndex]);
        }
        printf(" ");
    }
    return true;
}

bool isSumOverflow(const int* firstBinaryNumber, const int* secondBinaryNumber, const int* sumInBinaryForm)
{
    int indexOfSignedBit = numberOfBitsInInteger - 1;
    int signedBitOfFirstNumber = firstBinaryNumber[indexOfSignedBit];
    int signedBitOfSecondNumber = secondBinaryNumber[indexOfSignedBit];
    int signedBitOfSum = sumInBinaryForm[indexOfSignedBit];
    return signedBitOfFirstNumber == signedBitOfSecondNumber && signedBitOfSum != signedBitOfFirstNumber;
}

/* The function sums two's complements of binary numbers.
 * If (binaryForm == NULL) or (secondBinaryNumber == NULL) or
 * the result of the sum is out of the range of 4-byte integers, the function will return NULL. */
int* getSumInBinaryForm(const int* firstBinaryNumber, const int* secondBinaryNumber)
{
    if (firstBinaryNumber == NULL || secondBinaryNumber == NULL)
    {
        return NULL;
    }
    int* result = (int*) calloc(numberOfBitsInInteger, sizeof(int));
    int carry = 0;
    int bitOfFirstNumber = 0;
    int bitOfSecondNumber = 0;
    int totalAmountOfBits = 0;
    for (int i = 0; i < numberOfBitsInInteger; i++)
    {
        bitOfFirstNumber = firstBinaryNumber[i];
        bitOfSecondNumber = secondBinaryNumber[i];
        totalAmountOfBits = bitOfFirstNumber + bitOfSecondNumber + carry;
        carry = totalAmountOfBits / 2;
        result[i] = totalAmountOfBits % 2;
    }
    if (isSumOverflow(firstBinaryNumber, secondBinaryNumber, result))
    {
        free(result);
        return NULL;
    }
    return result;
}

/* If (binaryForm == NULL), the function will return 0. */
int getDecimalFromBinary(const int* binaryForm)
{
    if (binaryForm == NULL)
    {
        return 0;
    }
    int decimalForm = 0;
    if (binaryForm[numberOfBitsInInteger - 1] == 1)
    {
        for (int i = numberOfBitsInInteger - 2; i >= 0; i--)
        {
            decimalForm <<= 1;
            decimalForm = decimalForm + (1 - binaryForm[i]);
        }
        decimalForm++;
        decimalForm *= -1;
    }
    else
    {
        for (int i = numberOfBitsInInteger - 2; i >= 0; i--)
        {
            decimalForm <<= 1;
            decimalForm = decimalForm + binaryForm[i];
        }
    }
    return decimalForm;
}

bool scanNumber(long int* number)
{
    return scanf("%ld", number) == 1;
}

/* If some of the arguments is 0, the function will print the corresponding error and return false. */
bool displayAnswer(int* firstBinaryNumber, int* secondBinaryNumber, int* sumInBinaryForm)
{
    if (firstBinaryNumber == NULL || secondBinaryNumber == NULL)
    {
        fprintf(stderr, "Error. 4-byte integer overflow.\n");
        return false;
    }
    if (sumInBinaryForm == NULL)
    {
        fprintf(stderr, "Error. The result of the sum is out of the range of 4-byte integers.\n");
        return false;
    }

    printf("First number in binary representation (two's complement): ");
    displayBinaryForm(firstBinaryNumber);
    printf("\n");
    printf("Second number in binary representation (two's complement): ");
    displayBinaryForm(secondBinaryNumber);
    printf("\n");
    printf("The sum of these numbers in binary representation (two's complement): ");
    displayBinaryForm(sumInBinaryForm);
    printf("\n");

    int sumOfNumbers = getDecimalFromBinary(sumInBinaryForm);
    printf("The sum of these numbers in decimal representation: %d\n", sumOfNumbers);
    return true;
}

int main()
{
    long int firstNumber = 0;
    long int secondNumber = 0;
    printf("Enter two integers:\n");
    bool isCorrectReading = scanNumber(&firstNumber) &&
                            scanNumber(&secondNumber);

    if (!isCorrectReading)
    {
        fprintf(stderr, "Error. Incorrect input.\n");
        return 0;
    }

    int* firstBinaryNumber = getBinaryForm(firstNumber);
    int* secondBinaryNumber = getBinaryForm(secondNumber);
    int* sumInBinaryForm = getSumInBinaryForm(firstBinaryNumber, secondBinaryNumber);

    displayAnswer(firstBinaryNumber, secondBinaryNumber, sumInBinaryForm);

    free(firstBinaryNumber);
    free(secondBinaryNumber);
    free(sumInBinaryForm);
    return 0;
}
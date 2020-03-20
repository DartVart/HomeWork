#include <stdio.h>

int main(int argc, char* argv[])
{
    int numOfLuckyTickets = 0;
    int sumOfDigits[28];

    for (int i = 0; i < 28; i++)
    {
        sumOfDigits[i] = 0;
    }

    for (int firstDigit = 0; firstDigit < 10; firstDigit++)
    {
        for (int secondDigit = 0; secondDigit < 10; secondDigit++)
        {
            for (int thirdDigits = 0; thirdDigits < 10; thirdDigits++)
            {
                sumOfDigits[firstDigit + secondDigit + thirdDigits]++;
            }
        }
    }

    for (int i = 0; i < 28; i++)
    {
        numOfLuckyTickets += sumOfDigits[i] * sumOfDigits[i];
    }

    printf("The number of lucky tickets: %d", numOfLuckyTickets);

    return 0;
}
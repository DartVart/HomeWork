#include <stdio.h>

double binaryPower(double base, int power)
{
    if (power == 0)
    {
        return 1;
    }

    double halfPower = binaryPower(base, power / 2);

    if (power % 2 == 1)
    {
        return halfPower * halfPower * base;
    }
    else
    {
        return halfPower * halfPower;
    }
}

double getPower(double base, int power)
{
    return (power >= 0) ? binaryPower(base, power) : 1 / binaryPower(base, -power);
}

int main(int argc, char* argv[])
{
    double base = 0.0;
    int power = 0;

    printf("Enter a real number and an integer power: ");
    scanf("%lf%d", &base, &power);

    printf("%lf ^ %d = %lf", base, power, getPower(base, power));

    return 0;
}
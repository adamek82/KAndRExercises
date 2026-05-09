#include <stdio.h>

/*
 * Exercise 1-4.
 *
 * Write a program to print the corresponding Celsius-Fahrenheit table.
 *
 * Starting from:
 *
 *     celsius = (5.0 / 9.0) * (fahr - 32.0)
 *
 * we get:
 *
 *     fahr = (9.0 / 5.0) * celsius + 32.0
 */
int main(void)
{
    float celsius;
    float fahr;
    int lower;
    int upper;
    int step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("%7s %6s\n", "Celsius", "Fahr");

    celsius = lower;
    while (celsius <= upper) {
        fahr = (9.0 / 5.0) * celsius + 32.0;

        /*
         * %7.0f prints Celsius in a field at least 7 characters wide,
         * with no digits after the decimal point.
         * %6.1f prints Fahrenheit in a field at least 6 characters wide,
         * with 1 digit after the decimal point.
         */
        printf("%7.0f %6.1f\n", celsius, fahr);

        celsius = celsius + step;
    }

    return 0;
}

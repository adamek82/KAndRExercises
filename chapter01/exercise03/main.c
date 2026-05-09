#include <stdio.h>

/*
 * Exercise 1-3.
 *
 * Modify the Fahrenheit-Celsius temperature conversion program
 * to print a heading above the table.
 */
int main(void)
{
    float fahr;
    float celsius;
    int lower;
    int upper;
    int step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("Fahr Celsius\n");

    fahr = lower;
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);

        /*
         * %3.0f prints Fahrenheit in a field at least 3 characters wide,
         * with no digits after the decimal point.
         * %6.1f prints Celsius in a field at least 6 characters wide,
         * with 1 digit after the decimal point.
         */
        printf("%3.0f %6.1f\n", fahr, celsius);

        fahr = fahr + step;
    }

    return 0;
}

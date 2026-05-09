#include <stdio.h>

/*
 * Exercise 1-5.
 *
 * Modify the temperature conversion program to print the table
 * in reverse order, that is, from 300 degrees to 0.
 */
int main(void)
{
    int fahr;

    printf("%4s %7s\n", "Fahr", "Celsius");

    for (fahr = 300; fahr >= 0; fahr = fahr - 20) {
        printf("%4d %7.1f\n", fahr, (5.0 / 9.0) * (fahr - 32.0));
    }

    return 0;
}

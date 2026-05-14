#include <stdio.h>

float celsius(float fahr);

/*
 * Exercise 1-15.
 *
 * Rewrite the temperature conversion program of Section 1.2 to use
 * a function for conversion.
 */
int main(void)
{
    float fahr;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("%4s %7s\n", "Fahr", "Celsius");

    fahr = lower;
    while (fahr <= upper) {
        printf("%4.0f %7.1f\n", fahr, celsius(fahr));
        fahr = fahr + step;
    }

    return 0;
}

/*
 * Convert a Fahrenheit temperature to Celsius.
 */
float celsius(float fahr)
{
    return (5.0 / 9.0) * (fahr - 32.0);
}

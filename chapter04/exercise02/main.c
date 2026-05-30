#include <ctype.h>
#include <math.h>
#include <stdio.h>

double atof_kr(char s[]);
double power10(int exponent);
int nearly_equal(double a, double b);
int check_atof(void);

/*
 * Exercise 4-2.
 *
 * Extend atof to handle scientific notation of the form:
 *
 *     123.45e-6
 *
 * A floating-point number may be followed by e or E and an optionally signed
 * integer exponent.
 *
 * This is still a small K&R-style converter, not a full replacement for the
 * standard strtod function. It handles leading white space, an optional sign,
 * an optional fractional part, and an optional decimal exponent.
 */
int main(void)
{
    printf("atof_kr(\"123\") = %.10g\n", atof_kr("123"));
    printf("atof_kr(\"123.45\") = %.10g\n", atof_kr("123.45"));
    printf("atof_kr(\".45\") = %.10g\n", atof_kr(".45"));
    printf("atof_kr(\"123.\") = %.10g\n", atof_kr("123."));
    printf("atof_kr(\"-123.45\") = %.10g\n", atof_kr("-123.45"));
    printf("atof_kr(\"123.45e-6\") = %.10g\n", atof_kr("123.45e-6"));
    printf("atof_kr(\"123.45E+6\") = %.10g\n", atof_kr("123.45E+6"));
    printf("atof_kr(\"1e3\") = %.10g\n", atof_kr("1e3"));
    printf("atof_kr(\"1e-3\") = %.10g\n", atof_kr("1e-3"));

    if (!check_atof()) {
        printf("atof checks: failed\n");
        return 1;
    }

    printf("atof checks: ok\n");

    return 0;
}

double atof_kr(char s[])
{
    double val;
    double power;
    int i;
    int sign;
    int exponent;
    int exponent_sign;

    for (i = 0; isspace((unsigned char) s[i]); ++i) {
        ;
    }

    sign = s[i] == '-' ? -1 : 1;

    if (s[i] == '+' || s[i] == '-') {
        ++i;
    }

    for (val = 0.0; isdigit((unsigned char) s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
    }

    if (s[i] == '.') {
        ++i;
    }

    for (power = 1.0; isdigit((unsigned char) s[i]); ++i) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    val = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E') {
        ++i;

        exponent_sign = s[i] == '-' ? -1 : 1;

        if (s[i] == '+' || s[i] == '-') {
            ++i;
        }

        for (exponent = 0; isdigit((unsigned char) s[i]); ++i) {
            exponent = 10 * exponent + (s[i] - '0');
        }

        val *= power10(exponent_sign * exponent);
    }

    return val;
}

double power10(int exponent)
{
    double result = 1.0;

    if (exponent >= 0) {
        while (exponent > 0) {
            result *= 10.0;
            --exponent;
        }
    } else {
        while (exponent < 0) {
            result /= 10.0;
            ++exponent;
        }
    }

    return result;
}

int nearly_equal(double a, double b)
{
    double diff = a - b;

    if (diff < 0.0) {
        diff = -diff;
    }

    return diff < 1e-9;
}

int check_atof(void)
{
    if (!nearly_equal(atof_kr("123"), 123.0)) {
        return 0;
    }

    if (!nearly_equal(atof_kr("123.45"), 123.45)) {
        return 0;
    }

    if (!nearly_equal(atof_kr(".45"), 0.45)) {
        return 0;
    }

    if (!nearly_equal(atof_kr("123."), 123.0)) {
        return 0;
    }

    if (!nearly_equal(atof_kr("-123.45"), -123.45)) {
        return 0;
    }

    if (!nearly_equal(atof_kr("123.45e-6"), 0.00012345)) {
        return 0;
    }

    if (!nearly_equal(atof_kr("123.45E+6"), 123450000.0)) {
        return 0;
    }

    if (!nearly_equal(atof_kr("1e3"), 1000.0)) {
        return 0;
    }

    if (!nearly_equal(atof_kr("1e-3"), 0.001)) {
        return 0;
    }

    return 1;
}

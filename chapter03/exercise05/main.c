#include <limits.h>
#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);
void reverse(char s[]);
int string_equal(char s[], char t[]);
int check_itob(void);

/*
 * Exercise 3-5.
 *
 * Convert integer n to a character representation in base b.
 *
 * Bases from 2 to 36 are supported. Digits above 9 are represented by
 * lowercase letters a..z. Negative numbers are written with a leading '-'.
 *
 * As in exercise 3-4, we must not convert a negative n to positive by doing
 * n = -n. On a two's complement machine the smallest negative int has no
 * positive counterpart representable as int. Instead, we keep n possibly
 * negative and negate only the remainder n % b, whose magnitude is smaller
 * than b and therefore safe for bases up to 36.
 */
int main(void)
{
    char s[100];

    itob(0, s, 2);
    printf("itob(0, 2) = %s\n", s);

    itob(31, s, 2);
    printf("itob(31, 2) = %s\n", s);

    itob(31, s, 16);
    printf("itob(31, 16) = %s\n", s);

    itob(-31, s, 16);
    printf("itob(-31, 16) = %s\n", s);

    itob(255, s, 16);
    printf("itob(255, 16) = %s\n", s);

    itob(35, s, 36);
    printf("itob(35, 36) = %s\n", s);

    itob(INT_MIN, s, 10);
    printf("itob(INT_MIN, 10) = %s\n", s);

    itob(INT_MIN, s, 16);
    printf("itob(INT_MIN, 16) = %s\n", s);

    if (!check_itob()) {
        printf("itob checks: failed\n");
        return 1;
    }

    printf("itob checks: ok\n");

    return 0;
}

void itob(int n, char s[], int b)
{
    int i = 0;
    int sign = n;

    /*
     * Bases below 2 are rejected. Unary notation exists, but it is not a positional
     * base representation and does not fit the digit-by-remainder algorithm below.
     */
    if (b < 2 || b > 36) {
        s[0] = '\0';
        return;
    }

    do {
        int digit = n % b;

        if (digit < 0) {
            digit = -digit;
        }

        if (digit < 10) {
            s[i] = digit + '0';
        } else {
            s[i] = digit - 10 + 'a';
        }

        ++i;
    } while ((n /= b) != 0);

    if (sign < 0) {
        s[i] = '-';
        ++i;
    }

    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int i, j;
    int c;

    /* Cast before subtracting 1 to avoid unsigned underflow for empty strings. */
    for (i = 0, j = (int) strlen(s) - 1; i < j; ++i, --j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int check_itob(void)
{
    char actual[100];
    char expected[100];

    itob(0, actual, 2);
    if (!string_equal(actual, "0")) {
        return 0;
    }

    itob(31, actual, 2);
    if (!string_equal(actual, "11111")) {
        return 0;
    }

    itob(31, actual, 16);
    if (!string_equal(actual, "1f")) {
        return 0;
    }

    itob(-31, actual, 16);
    if (!string_equal(actual, "-1f")) {
        return 0;
    }

    itob(255, actual, 16);
    if (!string_equal(actual, "ff")) {
        return 0;
    }

    itob(35, actual, 36);
    if (!string_equal(actual, "z")) {
        return 0;
    }

    itob(123, actual, 1);
    if (!string_equal(actual, "")) {
        return 0;
    }

    itob(INT_MIN, actual, 10);
    sprintf(expected, "%d", INT_MIN);
    if (!string_equal(actual, expected)) {
        return 0;
    }

    return 1;
}

int string_equal(char s[], char t[])
{
    int i;

    for (i = 0; s[i] == t[i]; ++i) {
        if (s[i] == '\0') {
            return 1;
        }
    }

    return 0;
}

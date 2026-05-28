#include <limits.h>
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int w);
void reverse(char s[]);
int string_equal(char s[], char t[]);
int check_itoa(void);

/*
 * Exercise 3-6.
 *
 * Write a version of itoa that accepts a minimum field width. If the converted
 * number is shorter than that width, pad it on the left with blanks.
 *
 * As in exercise 3-4, this version must not negate n itself. On a two's
 * complement machine, INT_MIN has no positive counterpart representable as int.
 * Therefore we keep n possibly negative and negate only n % 10, whose magnitude
 * is at most 9.
 *
 * Padding is added before reversing the temporary result. Since digits are
 * generated in reverse order, spaces appended at the end become left padding
 * after reverse(s).
 */
int main(void)
{
    char s[100];

    itoa(0, s, 5);
    printf("itoa(0, 5) = '%s'\n", s);

    itoa(123, s, 5);
    printf("itoa(123, 5) = '%s'\n", s);

    itoa(-123, s, 6);
    printf("itoa(-123, 6) = '%s'\n", s);

    itoa(12345, s, 3);
    printf("itoa(12345, 3) = '%s'\n", s);

    itoa(INT_MIN, s, 0);
    printf("itoa(INT_MIN, 0) = '%s'\n", s);

    itoa(INT_MIN, s, 15);
    printf("itoa(INT_MIN, 15) = '%s'\n", s);

    if (!check_itoa()) {
        printf("itoa checks: failed\n");
        return 1;
    }

    printf("itoa checks: ok\n");

    return 0;
}

void itoa(int n, char s[], int w)
{
    int i = 0;
    int sign = n;

    do {
        int digit = n % 10;

        if (digit < 0) {
            digit = -digit;
        }

        s[i] = digit + '0';
        ++i;
    } while ((n /= 10) != 0);

    if (sign < 0) {
        s[i] = '-';
        ++i;
    }

    while (i < w) {
        s[i] = ' ';
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

int check_itoa(void)
{
    char actual[100];
    char expected[100];

    itoa(0, actual, 5);
    if (!string_equal(actual, "    0")) {
        return 0;
    }

    itoa(123, actual, 5);
    if (!string_equal(actual, "  123")) {
        return 0;
    }

    itoa(-123, actual, 6);
    if (!string_equal(actual, "  -123")) {
        return 0;
    }

    itoa(12345, actual, 3);
    if (!string_equal(actual, "12345")) {
        return 0;
    }

    itoa(INT_MIN, actual, 0);
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

#include <limits.h>
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);
void reverse(char s[]);
int string_equal(char s[], char t[]);
int check_itoa(int n);

/*
 * Exercise 3-4.
 *
 * The original K&R version of itoa changes a negative number into a positive
 * one by doing n = -n. This fails for the smallest negative int on a two's
 * complement machine.
 *
 * For example, with a 32-bit int:
 *
 *     INT_MIN = -2147483648
 *     INT_MAX =  2147483647
 *
 * The positive value 2147483648 cannot be represented as an int, so evaluating
 * -INT_MIN overflows. In standard C, signed integer overflow is undefined
 * behavior.
 *
 * This version avoids that problem by never negating n itself. It repeatedly
 * takes n % 10 while n may still be negative. The remainder has only one digit,
 * so if it is negative, negating that remainder is safe.
 */
int main(void)
{
    char s[100];

    itoa(0, s);
    printf("itoa(0) = %s\n", s);

    itoa(12345, s);
    printf("itoa(12345) = %s\n", s);

    itoa(-12345, s);
    printf("itoa(-12345) = %s\n", s);

    itoa(INT_MAX, s);
    printf("itoa(INT_MAX) = %s\n", s);

    itoa(INT_MIN, s);
    printf("itoa(INT_MIN) = %s\n", s);

    if (!check_itoa(0)) {
        return 1;
    }

    if (!check_itoa(12345)) {
        return 1;
    }

    if (!check_itoa(-12345)) {
        return 1;
    }

    if (!check_itoa(INT_MAX)) {
        return 1;
    }

    if (!check_itoa(INT_MIN)) {
        return 1;
    }

    printf("itoa checks: ok\n");

    return 0;
}

void itoa(int n, char s[])
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

int check_itoa(int n)
{
    char actual[100];
    char expected[100];

    itoa(n, actual);
    sprintf(expected, "%d", n);

    return string_equal(actual, expected);
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

#include <limits.h>
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);
int itoa_digits(int n, char s[], int i);
int check_itoa(void);
int check_case(int n);

/*
 * Exercise 4-12.
 *
 * Adapt the ideas of printd to write a recursive version of itoa; that is,
 * convert an integer into a string by calling a recursive routine.
 *
 * As in exercise 3-4, this version does not negate n as a whole. This lets it
 * handle INT_MIN, whose positive counterpart is not representable as int.
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

    if (!check_itoa()) {
        printf("itoa checks: failed\n");
        return 1;
    }

    printf("itoa checks: ok\n");

    return 0;
}

void itoa(int n, char s[])
{
    int i = 0;

    if (n < 0) {
        s[i] = '-';
        ++i;
    }

    i = itoa_digits(n, s, i);
    s[i] = '\0';
}

int itoa_digits(int n, char s[], int i)
{
    int digit;

    if (n / 10 != 0) {
        i = itoa_digits(n / 10, s, i);
    }

    digit = n % 10;

    if (digit < 0) {
        digit = -digit;
    }

    s[i] = (char) (digit + '0');
    ++i;

    return i;
}

int check_itoa(void)
{
    if (!check_case(0)) {
        return 0;
    }

    if (!check_case(12345)) {
        return 0;
    }

    if (!check_case(-12345)) {
        return 0;
    }

    if (!check_case(INT_MAX)) {
        return 0;
    }

    if (!check_case(INT_MIN)) {
        return 0;
    }

    return 1;
}

int check_case(int n)
{
    char actual[100];
    char expected[100];

    itoa(n, actual);
    sprintf(expected, "%d", n);

    return strcmp(actual, expected) == 0;
}

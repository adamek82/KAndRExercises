#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int get_line(char *s, int lim);
int kr_atoi(char *s);
void kr_itoa(int n, char *s);
void reverse(char *s);
int strindex(char *s, char *t);
int check_functions(void);
int check_itoa_case(int n);
int check_string(char *actual, char *expected);

/*
 * Exercise 5-6.
 *
 * Rewrite appropriate earlier functions using pointers instead of array
 * indexing. This program includes pointer versions of get_line, atoi, itoa,
 * reverse, and strindex.
 */
int main(void)
{
    char line[MAXLINE];
    char number[50];
    char text[] = "hello";

    get_line(line, MAXLINE);
    printf("get_line = %s", line);

    printf("kr_atoi(\"  -123x\") = %d\n", kr_atoi("  -123x"));

    kr_itoa(INT_MIN, number);
    printf("kr_itoa(INT_MIN) = %s\n", number);

    reverse(text);
    printf("reverse(\"hello\") = %s\n", text);

    printf("strindex(\"hello world\", \"world\") = %d\n",
           strindex("hello world", "world"));

    if (!check_functions()) {
        printf("pointer function checks: failed\n");
        return 1;
    }

    printf("pointer function checks: ok\n");

    return 0;
}

int get_line(char *s, int lim)
{
    int c;
    char *start = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        *s++ = (char) c;
    }

    if (c == '\n') {
        *s++ = (char) c;
    }

    *s = '\0';

    return s - start;
}

int kr_atoi(char *s)
{
    int n, sign;

    while (isspace((unsigned char) *s)) {
        ++s;
    }

    sign = *s == '-' ? -1 : 1;

    if (*s == '+' || *s == '-') {
        ++s;
    }

    for (n = 0; isdigit((unsigned char) *s); ++s) {
        n = 10 * n + (*s - '0');
    }

    return sign * n;
}

void kr_itoa(int n, char *s)
{
    int digit;
    int sign = n;
    char *start = s;

    do {
        digit = n % 10;

        if (digit < 0) {
            digit = -digit;
        }

        *s++ = (char) (digit + '0');
    } while ((n /= 10) != 0);

    if (sign < 0) {
        *s++ = '-';
    }

    *s = '\0';
    reverse(start);
}

void reverse(char *s)
{
    int c;
    char *t = s + strlen(s) - 1;

    while (s < t) {
        c = *s;
        *s++ = *t;
        *t-- = (char) c;
    }
}

int strindex(char *s, char *t)
{
    char *base = s;
    char *p;
    char *q;

    for (; *s; ++s) {
        for (p = s, q = t; *q && *p == *q; ++p, ++q) {
            ;
        }

        if (q > t && !*q) {
            return s - base;
        }
    }

    return -1;
}

int check_functions(void)
{
    char s1[50];

    if (kr_atoi("123") != 123) {
        return 0;
    }

    if (kr_atoi("  -42") != -42) {
        return 0;
    }

    if (kr_atoi("+17x") != 17) {
        return 0;
    }

    if (!check_itoa_case(0)) {
        return 0;
    }

    if (!check_itoa_case(12345)) {
        return 0;
    }

    if (!check_itoa_case(-12345)) {
        return 0;
    }

    if (!check_itoa_case(INT_MAX)) {
        return 0;
    }

    if (!check_itoa_case(INT_MIN)) {
        return 0;
    }

    strcpy(s1, "abcd");
    reverse(s1);
    if (!check_string(s1, "dcba")) {
        return 0;
    }

    strcpy(s1, "abcde");
    reverse(s1);
    if (!check_string(s1, "edcba")) {
        return 0;
    }

    if (strindex("hello world", "world") != 6) {
        return 0;
    }

    if (strindex("banana", "ana") != 1) {
        return 0;
    }

    if (strindex("abc", "x") != -1) {
        return 0;
    }

    if (strindex("abc", "") != -1) {
        return 0;
    }

    return 1;
}

int check_itoa_case(int n)
{
    char actual[50];
    char expected[50];

    kr_itoa(n, actual);
    sprintf(expected, "%d", n);

    return check_string(actual, expected);
}

int check_string(char *actual, char *expected)
{
    return strcmp(actual, expected) == 0;
}

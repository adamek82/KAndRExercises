#include <stdio.h>

int htoi(char s[]);
int hex_digit_value(int c);

/*
 * Exercise 2-3.
 *
 * Write the function htoi(s), which converts a string of hexadecimal digits
 * into its equivalent integer value. The string may begin with an optional
 * 0x or 0X prefix.
 *
 * This version stops conversion at the first non-hexadecimal character,
 * similarly to the atoi example from the book. Overflow is not handled here.
 */
int main(void)
{
    printf("0 -> %d\n", htoi("0"));
    printf("1 -> %d\n", htoi("1"));
    printf("9 -> %d\n", htoi("9"));
    printf("a -> %d\n", htoi("a"));
    printf("f -> %d\n", htoi("f"));
    printf("A -> %d\n", htoi("A"));
    printf("F -> %d\n", htoi("F"));
    printf("10 -> %d\n", htoi("10"));
    printf("0x10 -> %d\n", htoi("0x10"));
    printf("0X10 -> %d\n", htoi("0X10"));
    printf("7f -> %d\n", htoi("7f"));
    printf("0xff -> %d\n", htoi("0xff"));
    printf("0XABC -> %d\n", htoi("0XABC"));
    printf("123g -> %d\n", htoi("123g"));

    return 0;
}

int htoi(char s[])
{
    int i, n;
    int digit;

    i = 0;

    if (s[i] == '0') {
        if (s[i + 1] == 'x' || s[i + 1] == 'X') {
            i = i + 2;
        }
    }

    n = 0;
    while ((digit = hex_digit_value(s[i])) >= 0) {
        n = 16 * n + digit;
        ++i;
    }

    return n;
}

int hex_digit_value(int c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }

    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }

    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }

    return -1;
}

#include <stdio.h>

/*
 * Exercise 1-10.
 *
 * Write a program to copy its input to its output, replacing each tab
 * by \t, each backspace by \b, and each backslash by \\.
 *
 * This makes tabs and backspaces visible in an unambiguous way.
 */
int main(void)
{
    int c;
    int replaced;

    while ((c = getchar()) != EOF) {
        replaced = 0;

        if (c == '\t') {
            putchar('\\');
            putchar('t');
            replaced = 1;
        }

        if (c == '\b') {
            putchar('\\');
            putchar('b');
            replaced = 1;
        }

        if (c == '\\') {
            putchar('\\');
            putchar('\\');
            replaced = 1;
        }

        if (replaced == 0) {
            putchar(c);
        }
    }

    return 0;
}

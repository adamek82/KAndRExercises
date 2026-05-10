#include <stdio.h>

/*
 * Exercise 1-8.
 *
 * Write a program to count blanks, tabs, and newlines.
 *
 * The program reads characters from standard input until EOF.
 * It then prints three counters in this order:
 *
 *     blanks tabs newlines
 */
int main(void)
{
    int c;
    int blanks, tabs, newlines;

    blanks = 0;
    tabs = 0;
    newlines = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++blanks;
        }

        if (c == '\t') {
            ++tabs;
        }

        if (c == '\n') {
            ++newlines;
        }
    }

    printf("%d %d %d\n", blanks, tabs, newlines);

    return 0;
}

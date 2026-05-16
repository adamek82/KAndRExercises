#include <stdio.h>

#define TAB_WIDTH 8

/*
 * Exercise 1-20.
 *
 * Write a program detab that replaces tabs in the input with the proper
 * number of blanks to space to the next tab stop. Assume a fixed set of
 * tab stops, say every n columns.
 *
 * At this point in the book, n is best represented as a symbolic constant.
 * Later, after command-line arguments are introduced, it could naturally
 * become a user-provided parameter.
 */
int main(void)
{
    int c;
    int column;
    int blanks;

    column = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            blanks = TAB_WIDTH - column % TAB_WIDTH;

            while (blanks > 0) {
                putchar(' ');
                ++column;
                --blanks;
            }
        } else if (c == '\n') {
            putchar(c);
            column = 0;
        } else {
            putchar(c);
            ++column;
        }
    }

    return 0;
}

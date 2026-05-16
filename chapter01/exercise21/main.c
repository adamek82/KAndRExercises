#include <stdio.h>

#define TAB_WIDTH 8

/*
 * Exercise 1-21.
 *
 * Write a program entab that replaces strings of blanks by the minimum
 * number of tabs and blanks to achieve the same spacing. Use the same tab
 * stops as for detab.
 *
 * If either one tab or one blank would be enough to reach a tab stop, this
 * version prefers the tab. The goal of entab is to minimize the number of
 * output characters, and a tab represents reaching the next tab stop directly.
 */
int main(void)
{
    int c;
    int column, blanks, spaces_to_tab_stop;

    column = 0;
    blanks = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++blanks;
            ++column;

            if (column % TAB_WIDTH == 0) {
                putchar('\t');
                blanks = 0;
            }
        } else {
            while (blanks > 0) {
                putchar(' ');
                --blanks;
            }

            putchar(c);

            if (c == '\n') {
                column = 0;
            } else if (c == '\t') {
                spaces_to_tab_stop = TAB_WIDTH - column % TAB_WIDTH;
                column = column + spaces_to_tab_stop;
            } else {
                ++column;
            }
        }
    }

    while (blanks > 0) {
        putchar(' ');
        --blanks;
    }

    return 0;
}

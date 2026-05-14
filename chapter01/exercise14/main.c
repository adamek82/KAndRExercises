#include <stdio.h>
#include <ctype.h>

#define MAX_CHAR 128
#define MAX_BAR_WIDTH 10

/*
 * Exercise 1-14.
 *
 * Write a program to print a histogram of the frequencies of different
 * characters in its input.
 *
 * This program counts character codes from 0 to MAX_CHAR - 1. Characters
 * outside this range are ignored. Printable characters are shown directly;
 * selected whitespace and special characters get readable labels.
 */
int main(void)
{
    int c, i, j;
    int max_count, bar_length;
    int char_counts[MAX_CHAR];

    for (i = 0; i < MAX_CHAR; ++i) {
        char_counts[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c >= 0 && c < MAX_CHAR) {
            ++char_counts[c];
        }
    }

    max_count = 0;
    for (i = 0; i < MAX_CHAR; ++i) {
        if (char_counts[i] > max_count) {
            max_count = char_counts[i];
        }
    }

    printf("Code Char Count Histogram\n");

    for (i = 0; i < MAX_CHAR; ++i) {
        if (char_counts[i] > 0) {
            printf("%4d ", i);

            if (i == '\n') {
                printf("%4s", "\\n");
            } else if (i == '\t') {
                printf("%4s", "\\t");
            } else if (i == ' ') {
                printf("%4s", "sp");
            } else if (i == '\\') {
                printf("%4s", "\\\\");
            } else if (isprint(i)) {
                printf("%4c", i);
            } else {
                printf("%4s", "np");
            }

            printf(" %5d", char_counts[i]);

            bar_length = (char_counts[i] * MAX_BAR_WIDTH + max_count / 2) / max_count;

            if (bar_length <= 0) {
                bar_length = 1;
            }

            putchar(' ');
            for (j = 0; j < bar_length; ++j) {
                putchar('*');
            }

            putchar('\n');
        }
    }

    return 0;
}

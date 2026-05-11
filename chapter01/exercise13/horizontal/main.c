#include <stdio.h>

#define MAX_WORD_LENGTH 10
#define MAX_BAR_WIDTH  10

/*
 * Exercise 1-13.
 *
 * Write a program to print a histogram of the lengths of words in its input.
 *
 * This version prints a horizontal histogram. Words longer than
 * MAX_WORD_LENGTH are counted in a separate overflow bucket.
 *
 * The bars are scaled to MAX_BAR_WIDTH. The scaling uses rounding instead
 * of plain integer truncation, so counts very close to the maximum do not
 * lose a whole character just because of integer division.
 */
int main(void)
{
    int c, i, j;
    int word_length, max_count, bar_length, too_long_words;
    int word_lengths[MAX_WORD_LENGTH + 1];

    for (i = 0; i <= MAX_WORD_LENGTH; ++i) {
        word_lengths[i] = 0;
    }

    word_length = 0;
    too_long_words = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (word_length > 0) {
                if (word_length <= MAX_WORD_LENGTH) {
                    ++word_lengths[word_length];
                } else {
                    ++too_long_words;
                }

                word_length = 0;
            }
        } else {
            ++word_length;
        }
    }

    if (word_length > 0) {
        if (word_length <= MAX_WORD_LENGTH) {
            ++word_lengths[word_length];
        } else {
            ++too_long_words;
        }
    }

    max_count = too_long_words;
    for (i = 1; i <= MAX_WORD_LENGTH; ++i) {
        if (word_lengths[i] > max_count) {
            max_count = word_lengths[i];
        }
    }

    printf("Length Count Histogram\n");

    for (i = 1; i <= MAX_WORD_LENGTH; ++i) {
        printf("%6d %5d", i, word_lengths[i]);

        if (word_lengths[i] > 0) {
            bar_length = (word_lengths[i] * MAX_BAR_WIDTH + max_count / 2) / max_count;

            if (bar_length <= 0) {
                bar_length = 1;
            }

            putchar(' ');
            for (j = 0; j < bar_length; ++j) {
                putchar('*');
            }
        }

        putchar('\n');
    }

    printf("   >%2d %5d", MAX_WORD_LENGTH, too_long_words);

    if (too_long_words > 0) {
        bar_length = (too_long_words * MAX_BAR_WIDTH + max_count / 2) / max_count;

        if (bar_length <= 0) {
            bar_length = 1;
        }

        putchar(' ');
        for (j = 0; j < bar_length; ++j) {
            putchar('*');
        }
    }

    putchar('\n');

    return 0;
}

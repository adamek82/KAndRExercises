#include <stdio.h>

#define MAX_WORD_LENGTH 10
#define MAX_HIST_HEIGHT 10
#define OVERFLOW_BUCKET (MAX_WORD_LENGTH + 1)

/*
 * Exercise 1-13.
 *
 * Write a program to print a histogram of the lengths of words in its input.
 *
 * This version prints a vertical histogram. Words longer than
 * MAX_WORD_LENGTH are counted in a separate overflow bucket.
 *
 * The bars are scaled to MAX_HIST_HEIGHT. The scaling uses rounding instead
 * of plain integer truncation, so counts very close to the maximum do not
 * lose a whole character just because of integer division.
 */
int main(void)
{
    int c, i, level;
    int word_length, max_count, bar_height;
    int word_lengths[MAX_WORD_LENGTH + 2];
    int bar_heights[MAX_WORD_LENGTH + 2];

    for (i = 0; i <= OVERFLOW_BUCKET; ++i) {
        word_lengths[i] = 0;
        bar_heights[i] = 0;
    }

    word_length = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (word_length > 0) {
                if (word_length <= MAX_WORD_LENGTH) {
                    ++word_lengths[word_length];
                } else {
                    ++word_lengths[OVERFLOW_BUCKET];
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
            ++word_lengths[OVERFLOW_BUCKET];
        }
    }

    max_count = 0;
    for (i = 1; i <= OVERFLOW_BUCKET; ++i) {
        if (word_lengths[i] > max_count) {
            max_count = word_lengths[i];
        }
    }

    if (max_count > 0) {
        for (i = 1; i <= OVERFLOW_BUCKET; ++i) {
            if (word_lengths[i] > 0) {
                bar_height = (word_lengths[i] * MAX_HIST_HEIGHT + max_count / 2) / max_count;

                if (bar_height <= 0) {
                    bar_height = 1;
                }

                bar_heights[i] = bar_height;
            }
        }
    }

    printf("Length Histogram\n");

    for (level = MAX_HIST_HEIGHT; level > 0; --level) {
        for (i = 1; i <= MAX_WORD_LENGTH; ++i) {
            if (bar_heights[i] >= level) {
                printf("%4c", '*');
            } else {
                printf("%4c", ' ');
            }
        }

        if (bar_heights[OVERFLOW_BUCKET] >= level) {
            printf("%4c", '*');
        } else {
            printf("%4c", ' ');
        }

        putchar('\n');
    }

    for (i = 1; i <= MAX_WORD_LENGTH; ++i) {
        printf("%4d", i);
    }
    printf("%4s\n", ">10");

    for (i = 1; i <= MAX_WORD_LENGTH; ++i) {
        printf("%4d", word_lengths[i]);
    }
    printf("%4d\n", word_lengths[OVERFLOW_BUCKET]);

    return 0;
}

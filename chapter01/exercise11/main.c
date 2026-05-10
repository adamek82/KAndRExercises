#include <stdio.h>

#define IN  1
#define OUT 0

/*
 * Exercise 1-11.
 *
 * How would you test the word count program? What kinds of input are
 * most likely to uncover bugs if there are any?
 *
 * This file contains the word count program from the book, so the
 * corresponding Makefile target can test it with representative inputs.
 *
 * The tests focus on boundary cases and state transitions:
 *
 * - empty input: 0 lines, 0 words, 0 characters
 * - one word without a trailing newline: word ends at EOF
 * - one-letter word followed by newline: minimal word plus line count
 * - two-letter word followed by newline: character count sanity check
 * - two words in one line: transition OUT -> IN happens twice
 * - two lines with two words: line counting and word counting together
 * - only whitespace: no false words should be counted
 * - leading whitespace: word starts after blanks
 * - multiple blanks between words: still only two words
 * - mixed whitespace: spaces, tabs, and newlines all separate words
 */
int main(void)
{
    int c;
    int nl, nw, nc;
    int state;

    state = OUT;
    nl = nw = nc = 0;

    while ((c = getchar()) != EOF) {
        ++nc;

        if (c == '\n') {
            ++nl;
        }

        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
        } else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }

    printf("%d %d %d\n", nl, nw, nc);

    return 0;
}

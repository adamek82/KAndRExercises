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

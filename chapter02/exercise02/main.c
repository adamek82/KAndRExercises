#include <stdio.h>

#define MAXLINE 10

enum loop_state {
    LOOP_NO,
    LOOP_YES
};

int get_line(char s[], int lim);

/*
 * Exercise 2-2.
 *
 * Write a loop equivalent to:
 *
 *     for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
 *         s[i] = c;
 *
 * without using && or ||.
 *
 * This program uses that loop inside a get_line function and copies its input
 * to output. MAXLINE is intentionally small so tests exercise the buffer limit.
 */
int main(void)
{
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        printf("%s", line);
    }

    return 0;
}

/*
 * Read one line into s, up to lim - 1 characters.
 *
 * The main loop is equivalent to the K&R for loop, but avoids && and || by
 * checking one stopping condition at a time.
 */
int get_line(char s[], int lim)
{
    int c, i;
    enum loop_state keep_going;

    c = 0;
    i = 0;
    keep_going = LOOP_YES;

    while (keep_going == LOOP_YES) {
        if (i >= lim - 1) {
            keep_going = LOOP_NO;
        } else {
            c = getchar();

            if (c == '\n') {
                keep_going = LOOP_NO;
            } else if (c == EOF) {
                keep_going = LOOP_NO;
            } else {
                s[i] = c;
                ++i;
            }
        }
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}

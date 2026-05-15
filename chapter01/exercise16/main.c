#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

/*
 * Exercise 1-16.
 *
 * Revise the main routine of the longest-line program so it will correctly
 * print the length of arbitrarily long input lines, and as much as possible
 * of the text.
 *
 * get_line returns the full input line length, even if only the beginning of
 * the line fits in the provided array.
 */
int main(void)
{
    int len, max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;

    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }

    if (max > 0) {
        printf("%d\n", max);
        printf("%s", longest);
    }

    return 0;
}

/*
 * Read one input line into s and return its full length.
 *
 * The function stores as much text as fits in s, leaving room for the
 * terminating '\0'. It still continues reading the rest of the line so the
 * returned length is correct even for lines longer than the buffer.
 */
int get_line(char s[], int lim)
{
    int c, i, j;

    i = 0;
    j = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        if (j < lim - 1) {
            s[j] = c;
            ++j;
        }

        ++i;
    }

    if (c == '\n') {
        if (j < lim - 1) {
            s[j] = c;
            ++j;
        }

        ++i;
    }

    s[j] = '\0';

    return i;
}

/*
 * Copy from to to. The destination array must be large enough.
 */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

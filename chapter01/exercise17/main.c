#include <stdio.h>

#define MAXLINE 1000
#define LONG_LINE 80

int get_line(char line[], int maxline);

/*
 * Exercise 1-17.
 *
 * Write a program to print all input lines that are longer than
 * 80 characters.
 *
 * This program follows the K&R getline convention: the returned line length
 * includes the terminating '\n' if it was read from input. Therefore a line
 * with 79 visible characters plus '\n' has length 80, and a line with
 * 80 visible characters plus '\n' has length 81.
 */
int main(void)
{
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > LONG_LINE) {
            printf("%s", line);
        }
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

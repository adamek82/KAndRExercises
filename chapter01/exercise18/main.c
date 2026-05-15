#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
int trim_line(char line[]);

/*
 * Exercise 1-18.
 *
 * Write a program to remove all trailing blanks and tabs from each line
 * of input, and to delete entirely blank lines.
 *
 * This version does not assume that each stored line ends with '\n'.
 * The last input line may end at EOF, and very long lines may be stored
 * only partially.
 */
int main(void)
{
    char line[MAXLINE];

    while (get_line(line, MAXLINE) > 0) {
        if (trim_line(line) > 0) {
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

/*
 * Remove trailing blanks and tabs from s.
 *
 * If s ends with '\n', the newline is preserved, but blanks and tabs before
 * it are removed. If the resulting line is empty, the function returns 0.
 */
int trim_line(char s[])
{
    int i;
    int has_newline;

    i = 0;
    while (s[i] != '\0') {
        ++i;
    }

    has_newline = 0;
    if (i > 0 && s[i - 1] == '\n') {
        has_newline = 1;
        --i;
    }

    while (i > 0 && (s[i - 1] == ' ' || s[i - 1] == '\t')) {
        --i;
    }

    if (has_newline) {
        s[i] = '\n';
        ++i;
    }

    s[i] = '\0';

    if (has_newline) {
        return i - 1;
    }

    return i;
}

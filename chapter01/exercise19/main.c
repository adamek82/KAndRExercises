#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
void reverse(char s[]);

/*
 * Exercise 1-19.
 *
 * Write a function reverse(s) that reverses the character string s.
 * Use it to write a program that reverses its input a line at a time.
 *
 * If a line ends with '\n', reverse leaves that newline at the end.
 */
int main(void)
{
    char line[MAXLINE];

    while (get_line(line, MAXLINE) > 0) {
        reverse(line);
        printf("%s", line);
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
 * Reverse the characters in s.
 *
 * The terminating '\0' is not part of the text. If s ends with '\n',
 * that newline is kept at the end, so only the preceding text is reversed.
 */
void reverse(char s[])
{
    int i, j;
    char temp;

    i = 0;
    while (s[i] != '\0') {
        ++i;
    }

    --i;

    if (i >= 0 && s[i] == '\n') {
        --i;
    }

    j = 0;
    while (j < i) {
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;

        ++j;
        --i;
    }
}

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

int getint(int *pn);
int getch(void);
void ungetch(int c);
void ungets(char s[]);
void clear_pushback(void);
int is_digit(int c);
int is_space(int c);
int check_getint(void);
int check_number_case(char input[], int expected_value, int expected_next);
int check_rejected_case(char input[], int expected_first, int expected_second);

/*
 * Exercise 5-1.
 *
 * As written, getint treats a + or - not followed by a digit as a valid
 * representation of zero. Fix it to push such a character back on the input.
 *
 * This version returns:
 *
 *     EOF   end of input
 *     0     the next input token is not a number
 *     1     a number was read into *pn
 *
 * If a sign is not followed by a digit, both the following non-digit character
 * and the sign itself are pushed back, so the caller can read them normally.
 */
int main(void)
{
    int n;
    int status;
    int first;
    int second;

    clear_pushback();
    ungets("123x");
    status = getint(&n);
    printf("getint(\"123x\"): status=%d value=%d next=%c\n",
           status, n, getch());

    clear_pushback();
    ungets("-42x");
    status = getint(&n);
    printf("getint(\"-42x\"): status=%d value=%d next=%c\n",
           status, n, getch());

    clear_pushback();
    ungets("+x");
    status = getint(&n);
    first = getch();
    second = getch();
    printf("getint(\"+x\"): status=%d next=%c%c\n",
        status, first, second);

    if (!check_getint()) {
        printf("getint checks: failed\n");
        return 1;
    }

    printf("getint checks: ok\n");

    return 0;
}

int getint(int *pn)
{
    int c, sign, next;

    while (is_space(c = getch())) {
        ;
    }

    if (c == EOF) {
        return EOF;
    }

    if (!is_digit(c) && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = c == '-' ? -1 : 1;

    if (c == '+' || c == '-') {
        next = getch();

        if (!is_digit(next)) {
            if (next != EOF) {
                ungetch(next);
            }

            ungetch(c);
            return 0;
        }

        c = next;
    }

    for (*pn = 0; is_digit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }

    *pn *= sign;

    if (c != EOF) {
        ungetch(c);
    }

    return 1;
}

int is_digit(int c)
{
    return c != EOF && isdigit((unsigned char) c);
}

int is_space(int c)
{
    return c != EOF && isspace((unsigned char) c);
}

int buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    if (bufp > 0) {
        --bufp;
        return buf[bufp];
    }

    return getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp] = c;
        ++bufp;
    }
}

void ungets(char s[])
{
    int len = (int) strlen(s);

    while (len > 0) {
        ungetch(s[--len]);
    }
}

void clear_pushback(void)
{
    bufp = 0;
}

int check_getint(void)
{
    if (!check_number_case("123x", 123, 'x')) {
        return 0;
    }

    if (!check_number_case("-42x", -42, 'x')) {
        return 0;
    }

    if (!check_number_case("+17x", 17, 'x')) {
        return 0;
    }

    if (!check_rejected_case("+x", '+', 'x')) {
        return 0;
    }

    if (!check_rejected_case("-x", '-', 'x')) {
        return 0;
    }

    if (!check_rejected_case("abc", 'a', 'b')) {
        return 0;
    }

    return 1;
}

int check_number_case(char input[], int expected_value, int expected_next)
{
    int n = 0;
    int status;

    clear_pushback();
    ungets(input);

    status = getint(&n);

    return status == 1 && n == expected_value && getch() == expected_next;
}

int check_rejected_case(char input[], int expected_first, int expected_second)
{
    int n = 12345;
    int status;

    clear_pushback();
    ungets(input);

    status = getint(&n);

    return status == 0 && getch() == expected_first && getch() == expected_second;
}

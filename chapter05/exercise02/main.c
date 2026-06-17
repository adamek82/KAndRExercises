#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

int getfloat(float *pn);
int getch(void);
void ungetch(int c);
void ungets(char s[]);
void clear_pushback(void);
int is_digit(int c);
int is_space(int c);
int nearly_equal(float a, float b);
int check_getfloat(void);
int check_number_case(char input[], float expected_value, int expected_next);
int check_rejected_case(char input[], int expected_first, int expected_second);

/*
 * Exercise 5-2.
 *
 * Write getfloat, the floating-point analog of getint.
 *
 * getfloat returns an int status, not a float value. The parsed floating-point
 * value is stored through the pointer argument.
 *
 * Return values:
 *
 *     EOF   end of input
 *     0     the next input token is not a number
 *     1     a number was read into *pn
 */
int main(void)
{
    float x;
    int status, next;
    int first, second;

    clear_pushback();
    ungets("123.45x");
    status = getfloat(&x);
    next = getch();
    printf("getfloat(\"123.45x\"): status=%d value=%.8g next=%c\n",
           status, x, next);

    clear_pushback();
    ungets("-.5x");
    status = getfloat(&x);
    next = getch();
    printf("getfloat(\"-.5x\"): status=%d value=%.8g next=%c\n",
           status, x, next);

    clear_pushback();
    ungets("+x");
    status = getfloat(&x);
    first = getch();
    second = getch();
    printf("getfloat(\"+x\"): status=%d next=%c%c\n",
           status, first, second);

    if (!check_getfloat()) {
        printf("getfloat checks: failed\n");
        return 1;
    }

    printf("getfloat checks: ok\n");

    return 0;
}

int getfloat(float *pn)
{
    int c, sign, sign_char;
    int saw_digit = 0;
    float power = 1.0f;

    while (is_space(c = getch())) {
        ;
    }

    if (c == EOF) {
        return EOF;
    }

    if (!is_digit(c) && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }

    sign = c == '-' ? -1 : 1;
    sign_char = 0;

    if (c == '+' || c == '-') {
        sign_char = c;
        c = getch();

        if (!is_digit(c) && c != '.') {
            if (c != EOF) {
                ungetch(c);
            }

            ungetch(sign_char);
            return 0;
        }
    }

    for (*pn = 0.0f; is_digit(c); c = getch()) {
        *pn = 10.0f * *pn + (c - '0');
        saw_digit = 1;
    }

    if (c == '.') {
        c = getch();

        if (!is_digit(c) && !saw_digit) {
            if (c != EOF) {
                ungetch(c);
            }

            ungetch('.');

            if (sign_char != 0) {
                ungetch(sign_char);
            }

            return 0;
        }

        for (; is_digit(c); c = getch()) {
            *pn = 10.0f * *pn + (c - '0');
            power *= 10.0f;
            saw_digit = 1;
        }
    }

    *pn = sign * *pn / power;

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

int nearly_equal(float a, float b)
{
    float diff = a - b;

    if (diff < 0.0f) {
        diff = -diff;
    }

    return diff < 0.00001f;
}

int check_getfloat(void)
{
    if (!check_number_case("123.45x", 123.45f, 'x')) {
        return 0;
    }

    if (!check_number_case("-42.5x", -42.5f, 'x')) {
        return 0;
    }

    if (!check_number_case("+17.25x", 17.25f, 'x')) {
        return 0;
    }

    if (!check_number_case(".5x", 0.5f, 'x')) {
        return 0;
    }

    if (!check_number_case("123.x", 123.0f, 'x')) {
        return 0;
    }

    if (!check_rejected_case("+x", '+', 'x')) {
        return 0;
    }

    if (!check_rejected_case("-x", '-', 'x')) {
        return 0;
    }

    if (!check_rejected_case(".x", '.', 'x')) {
        return 0;
    }

    return 1;
}

int check_number_case(char input[], float expected_value, int expected_next)
{
    float value = 0.0f;
    int status;
    int next;

    clear_pushback();
    ungets(input);

    status = getfloat(&value);
    next = getch();

    return status == 1 && nearly_equal(value, expected_value)
        && next == expected_next;
}

int check_rejected_case(char input[], int expected_first, int expected_second)
{
    float value = 12345.0f;
    int status;
    int first;
    int second;

    clear_pushback();
    ungets(input);

    status = getfloat(&value);
    first = getch();
    second = getch();

    return status == 0 && first == expected_first && second == expected_second;
}

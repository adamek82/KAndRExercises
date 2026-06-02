#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int c);
void ungets(char s[]);
void print_next(int count);

/*
 * Exercise 4-7.
 *
 * Write a routine ungets(s) that pushes back an entire string onto the input.
 *
 * ungets does not know about buf and bufp directly. It uses ungetch, because
 * ungetch is already responsible for the pushback buffer and its bounds.
 *
 * The string has to be pushed back in reverse order, because getch retrieves
 * characters from the pushback buffer in LIFO order.
 */
int main(void)
{
    ungets("hello");
    print_next(5);
    putchar('\n');

    ungets("abc");
    ungets("123");
    print_next(6);
    putchar('\n');

    ungets("");
    printf("empty string pushed back\n");

    return 0;
}

char buf[BUFSIZE];
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
        buf[bufp] = (char) c;
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

void print_next(int count)
{
    int i;
    int c;

    for (i = 0; i < count; ++i) {
        c = getch();

        if (c == EOF) {
            return;
        }

        putchar(c);
    }
}

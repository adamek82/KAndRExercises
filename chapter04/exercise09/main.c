#include <stdio.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int c);

/*
 * Exercise 4-9.
 *
 * The original getch/ungetch implementation used a char buffer, which cannot
 * portably store EOF. EOF is an int value, not a character.
 *
 * To allow EOF to be pushed back and read again, the pushback buffer must store
 * int values.
 */
int main(void)
{
    int c;

    ungetch('A');
    putchar(getch());
    putchar('\n');

    ungetch(EOF);
    c = getch();

    if (c == EOF) {
        printf("EOF pushed back and read again\n");
    }

    c = getch();

    if (c == EOF) {
        printf("EOF read from empty input\n");
    }

    return 0;
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

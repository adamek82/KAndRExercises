#include <stdio.h>

int getch(void);
void ungetch(int c);

/*
 * Exercise 4-8.
 *
 * Suppose there will never be more than one character of pushback. Modify
 * getch and ungetch accordingly.
 *
 * Instead of an array and an index, we keep a single pushed-back character and
 * a flag telling whether that character is present. The flag is better than
 * using 0 as a sentinel value, because 0 can also be a valid character.
 */
int main(void)
{
    int c;

    ungetch('A');
    putchar(getch());
    putchar('\n');

    ungetch('B');
    ungetch('C');
    putchar(getch());
    putchar('\n');

    c = getch();
    if (c == EOF) {
        printf("EOF\n");
    }

    return 0;
}

int pushed_back = 0;
int pushed_char = 0;

int getch(void)
{
    if (pushed_back) {
        pushed_back = 0;
        return pushed_char;
    }

    return getchar();
}

void ungetch(int c)
{
    if (c == EOF) {
        return;
    }

    if (pushed_back) {
        printf("ungetch: too many characters\n");
    } else {
        pushed_char = c;
        pushed_back = 1;
    }
}

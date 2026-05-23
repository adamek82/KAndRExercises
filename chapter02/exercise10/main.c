#include <stdio.h>

int lower(int c);

/*
 * Exercise 2-10.
 *
 * Rewrite the function lower, which converts upper-case letters to lower-case,
 * with a conditional expression instead of if-else.
 *
 * This version assumes the ASCII character set, as in the book example.
 */
int main(void)
{
    printf("A -> %c\n", lower('A'));
    printf("Z -> %c\n", lower('Z'));
    printf("M -> %c\n", lower('M'));
    printf("a -> %c\n", lower('a'));
    printf("z -> %c\n", lower('z'));
    printf("0 -> %c\n", lower('0'));
    printf("? -> %c\n", lower('?'));

    return 0;
}

int lower(int c)
{
    return c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c;
}

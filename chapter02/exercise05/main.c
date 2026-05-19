#include <stdio.h>

int any(char s1[], char s2[]);
int contains(char s[], int c);

/*
 * Exercise 2-5.
 *
 * Write the function any(s1, s2), which returns the first location in s1
 * where any character from s2 occurs, or -1 if s1 contains no characters
 * from s2.
 *
 * The standard library function strpbrk does the same job, but returns
 * a pointer to the matching character instead of an index.
 */
int main(void)
{
    printf("hello, world / od -> %d\n", any("hello, world", "od"));
    printf("hello, world / xyz -> %d\n", any("hello, world", "xyz"));
    printf("abc / c -> %d\n", any("abc", "c"));
    printf("abc / a -> %d\n", any("abc", "a"));
    printf("abc / empty -> %d\n", any("abc", ""));
    printf("empty / abc -> %d\n", any("", "abc"));
    printf("mississippi / ps -> %d\n", any("mississippi", "ps"));

    return 0;
}

/*
 * Return the index of the first character in s1 that occurs in s2.
 * Return -1 if no such character exists.
 */
int any(char s1[], char s2[])
{
    int i;

    for (i = 0; s1[i] != '\0'; ++i) {
        if (contains(s2, s1[i])) {
            return i;
        }
    }

    return -1;
}

/*
 * Return 1 if c occurs in s, otherwise return 0.
 */
int contains(char s[], int c)
{
    int i;

    for (i = 0; s[i] != '\0'; ++i) {
        if (s[i] == c) {
            return 1;
        }
    }

    return 0;
}

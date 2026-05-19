#include <stdio.h>

void squeeze(char s1[], char s2[]);
int contains(char s[], int c);

/*
 * Exercise 2-4.
 *
 * Write an alternate version of squeeze(s1, s2) that deletes each character
 * in s1 that matches any character in s2.
 *
 * The function modifies s1 in place.
 */
int main(void)
{
    char s1[] = "hello, world";
    char s2[] = "lo";

    char s3[] = "The C Programming Language";
    char s4[] = "aeiouAEIOU";

    char s5[] = "abc";
    char s6[] = "";

    char s7[] = "";
    char s8[] = "abc";

    char s9[] = "mississippi";
    char s10[] = "is";

    squeeze(s1, s2);
    squeeze(s3, s4);
    squeeze(s5, s6);
    squeeze(s7, s8);
    squeeze(s9, s10);

    printf("hello, world / lo -> %s\n", s1);
    printf("The C Programming Language / vowels -> %s\n", s3);
    printf("abc / empty -> %s\n", s5);
    printf("empty / abc -> %s\n", s7);
    printf("mississippi / is -> %s\n", s9);

    return 0;
}

/*
 * Delete from s1 every character that occurs in s2.
 */
void squeeze(char s1[], char s2[])
{
    int i, j;

    j = 0;
    for (i = 0; s1[i] != '\0'; ++i) {
        if (!contains(s2, s1[i])) {
            s1[j] = s1[i];
            ++j;
        }
    }

    s1[j] = '\0';
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

#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void reverse_range(char s[], int left, int right);
int check_reverse(void);
int check_case(char s[], char expected[]);

/*
 * Exercise 4-13.
 *
 * Write a recursive version of reverse(s), which reverses the string s in place.
 *
 * The public function reverse keeps the usual interface. The recursive helper
 * receives the left and right indexes of the part of the string that still has
 * to be reversed.
 */
int main(void)
{
    char s1[] = "hello";
    char s2[] = "abcd";
    char s3[] = "";
    char s4[] = "a";
    char s5[] = "K&R";

    reverse(s1);
    reverse(s2);
    reverse(s3);
    reverse(s4);
    reverse(s5);

    printf("reverse(\"hello\") = %s\n", s1);
    printf("reverse(\"abcd\") = %s\n", s2);
    printf("reverse(\"\") = %s\n", s3);
    printf("reverse(\"a\") = %s\n", s4);
    printf("reverse(\"K&R\") = %s\n", s5);

    if (!check_reverse()) {
        printf("reverse checks: failed\n");
        return 1;
    }

    printf("reverse checks: ok\n");

    return 0;
}

void reverse(char s[])
{
    int len = (int) strlen(s);

    if (len > 0) {
        reverse_range(s, 0, len - 1);
    }
}

void reverse_range(char s[], int left, int right)
{
    int temp;

    if (left >= right) {
        return;
    }

    temp = s[left];
    s[left] = s[right];
    s[right] = (char) temp;

    reverse_range(s, left + 1, right - 1);
}

int check_reverse(void)
{
    char s1[] = "hello";
    char s2[] = "abcd";
    char s3[] = "";
    char s4[] = "a";
    char s5[] = "K&R";
    char s6[] = "123456789";

    if (!check_case(s1, "olleh")) {
        return 0;
    }

    if (!check_case(s2, "dcba")) {
        return 0;
    }

    if (!check_case(s3, "")) {
        return 0;
    }

    if (!check_case(s4, "a")) {
        return 0;
    }

    if (!check_case(s5, "R&K")) {
        return 0;
    }

    if (!check_case(s6, "987654321")) {
        return 0;
    }

    return 1;
}

int check_case(char s[], char expected[])
{
    reverse(s);

    return strcmp(s, expected) == 0;
}

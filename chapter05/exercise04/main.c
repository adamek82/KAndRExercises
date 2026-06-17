#include <stdio.h>

int strend(char *s, char *t);
int string_equal(char *s, char *t);
int string_length(char *s);
int check_strend(void);
int check_case(char *s, char *t, int expected);

/*
 * Exercise 5-4.
 *
 * Write the function strend(s, t), which returns 1 if the string t occurs at
 * the end of the string s, and 0 otherwise.
 */
int main(void)
{
    printf("strend(\"hello world\", \"world\") = %d\n",
           strend("hello world", "world"));

    printf("strend(\"hello world\", \"hello\") = %d\n",
           strend("hello world", "hello"));

    printf("strend(\"abc\", \"abc\") = %d\n",
           strend("abc", "abc"));

    printf("strend(\"abc\", \"\") = %d\n",
           strend("abc", ""));

    if (!check_strend()) {
        printf("strend checks: failed\n");
        return 1;
    }

    printf("strend checks: ok\n");

    return 0;
}

int strend(char *s, char *t)
{
    int s_len = string_length(s);
    int t_len = string_length(t);

    if (t_len > s_len) {
        return 0;
    }

    s += s_len - t_len;

    return string_equal(s, t);
}

int string_equal(char *s, char *t)
{
    while (*s == *t) {
        if (*s == '\0') {
            return 1;
        }

        ++s;
        ++t;
    }

    return 0;
}

int string_length(char *s)
{
    int len = 0;

    while (*s != '\0') {
        ++len;
        ++s;
    }

    return len;
}

int check_strend(void)
{
    if (!check_case("hello world", "world", 1)) {
        return 0;
    }

    if (!check_case("hello world", "hello", 0)) {
        return 0;
    }

    if (!check_case("abc", "abc", 1)) {
        return 0;
    }

    if (!check_case("abc", "bc", 1)) {
        return 0;
    }

    if (!check_case("abc", "abcd", 0)) {
        return 0;
    }

    if (!check_case("abc", "", 1)) {
        return 0;
    }

    if (!check_case("", "", 1)) {
        return 0;
    }

    if (!check_case("", "a", 0)) {
        return 0;
    }

    return 1;
}

int check_case(char *s, char *t, int expected)
{
    return strend(s, t) == expected;
}

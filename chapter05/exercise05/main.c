#include <stdio.h>

char *kr_strncpy(char *s, char *t, int n);
char *kr_strncat(char *s, char *t, int n);
int kr_strncmp(char *s, char *t, int n);
int string_equal(char *s, char *t);
int buffer_equal(char *s, char *t, int n);
int check_functions(void);

/*
 * Exercise 5-5.
 *
 * Write versions of strncpy, strncat, and strncmp, which operate on at most
 * the first n characters of their argument strings.
 *
 * The names are prefixed with kr_ to avoid colliding with the standard library
 * functions and compiler builtins.
 */
int main(void)
{
    char s1[20] = "hello";
    char s2[20] = "abc";
    char s3[20];

    kr_strncat(s1, " world", 3);
    printf("kr_strncat(\"hello\", \" world\", 3) = %s\n", s1);

    kr_strncpy(s2, "xy", 5);
    printf("kr_strncpy(\"abc\", \"xy\", 5) = %s\n", s2);

    kr_strncpy(s3, "abcdef", 3);
    s3[3] = '\0';
    printf("kr_strncpy(\"\", \"abcdef\", 3) prefix = %s\n", s3);

    printf("kr_strncmp(\"abc\", \"abd\", 2) = %d\n",
           kr_strncmp("abc", "abd", 2));

    printf("kr_strncmp(\"abc\", \"abd\", 3) = %d\n",
           kr_strncmp("abc", "abd", 3));

    if (!check_functions()) {
        printf("string function checks: failed\n");
        return 1;
    }

    printf("string function checks: ok\n");

    return 0;
}

char *kr_strncpy(char *s, char *t, int n)
{
    char *start = s;

    while (n > 0 && *t) {
        *s++ = *t++;
        --n;
    }

    while (n-- > 0) {
        *s++ = '\0';
    }

    return start;
}

char *kr_strncat(char *s, char *t, int n)
{
    char *start = s;

    while (*s) {
        ++s;
    }

    while (n > 0 && *t) {
        *s++ = *t++;
        --n;
    }

    *s = '\0';

    return start;
}

int kr_strncmp(char *s, char *t, int n)
{
    while (n-- > 0) {
        if (*s != *t) {
            return (unsigned char) *s - (unsigned char) *t;
        }

        if (!*s) {
            return 0;
        }

        ++s;
        ++t;
    }

    return 0;
}

int string_equal(char *s, char *t)
{
    while (*s && *s == *t) {
        ++s;
        ++t;
    }

    return *s == *t;
}

int buffer_equal(char *s, char *t, int n)
{
    while (n-- > 0) {
        if (*s++ != *t++) {
            return 0;
        }
    }

    return 1;
}

int check_functions(void)
{
    char a[20] = "hello";
    char b[20] = "abc";
    char c[20] = "unchanged";
    char d[20] = "hello";
    char e[20] = "hello";
    char f[20] = "hello";
    char g[20] = "hello";
    char h[20] = "xxxxx";
    char i[20] = "xxxxx";

    kr_strncat(a, " world", 3);
    if (!string_equal(a, "hello wo")) {
        return 0;
    }

    kr_strncpy(b, "xy", 5);
    if (!buffer_equal(b, "xy\0\0\0", 5)) {
        return 0;
    }

    kr_strncpy(c, "abcdef", 3);
    if (!buffer_equal(c, "abc", 3)) {
        return 0;
    }

    kr_strncat(d, " world", 0);
    if (!string_equal(d, "hello")) {
        return 0;
    }

    kr_strncat(e, "", 5);
    if (!string_equal(e, "hello")) {
        return 0;
    }

    kr_strncat(f, "!", 5);
    if (!string_equal(f, "hello!")) {
        return 0;
    }

    kr_strncat(g, "abc", 3);
    if (!string_equal(g, "helloabc")) {
        return 0;
    }

    kr_strncpy(h, "", 3);
    if (!buffer_equal(h, "\0\0\0", 3)) {
        return 0;
    }

    kr_strncpy(i, "abc", 0);
    if (!string_equal(i, "xxxxx")) {
        return 0;
    }

    if (kr_strncmp("abc", "abd", 2) != 0) {
        return 0;
    }

    if (kr_strncmp("abc", "abd", 3) >= 0) {
        return 0;
    }

    if (kr_strncmp("abd", "abc", 3) <= 0) {
        return 0;
    }

    if (kr_strncmp("abc", "abc", 3) != 0) {
        return 0;
    }

    if (kr_strncmp("abc", "ab", 3) <= 0) {
        return 0;
    }

    if (kr_strncmp("ab", "abc", 3) >= 0) {
        return 0;
    }

    if (kr_strncmp("abc", "abd", 0) != 0) {
        return 0;
    }

    if (kr_strncmp("", "", 5) != 0) {
        return 0;
    }

    if (kr_strncmp("", "a", 5) >= 0) {
        return 0;
    }

    if (kr_strncmp("a", "", 5) <= 0) {
        return 0;
    }

    return 1;
}

#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[]);
int strrindex_forward(char s[], char t[]);
int check_case(char s[], char t[], int expected);
int check_strrindex(void);

/*
 * Exercise 4-1.
 *
 * Write the function strrindex(s, t), which returns the position of the
 * rightmost occurrence of t in s, or -1 if there is none.
 *
 * strrindex_forward is close to K&R's strindex: it scans from the left,
 * remembers every match, and returns the last remembered position.
 *
 * strrindex is the actual solution used for the exercise. It starts from the
 * last possible position and scans left, so the first match it finds is already
 * the rightmost occurrence.
 *
 * As in K&R's strindex, an empty pattern is treated as "not found".
 */
int main(void)
{
    printf("strrindex(\"hello world\", \"world\") = %d\n",
           strrindex("hello world", "world"));

    printf("strrindex(\"banana\", \"ana\") = %d\n",
           strrindex("banana", "ana"));

    printf("strrindex(\"aaaa\", \"aa\") = %d\n",
           strrindex("aaaa", "aa"));

    printf("strrindex(\"abc\", \"x\") = %d\n",
           strrindex("abc", "x"));

    printf("strrindex(\"abc\", \"\") = %d\n",
           strrindex("abc", ""));

    if (!check_strrindex()) {
        printf("strrindex checks: failed\n");
        return 1;
    }

    printf("strrindex checks: ok\n");

    return 0;
}

/*
 * Scan from the right. The loop starts at the last position where t could still
 * fit in s. This avoids checking impossible suffix positions.
 */
int strrindex(char s[], char t[])
{
    int i, j, k;
    int s_len = (int) strlen(s);
    int t_len = (int) strlen(t);

    if (t_len == 0 || t_len > s_len) {
        return -1;
    }

    for (i = s_len - t_len; i >= 0; --i) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k) {
            ;
        }

        if (t[k] == '\0') {
            return i;
        }
    }

    return -1;
}

/*
 * K&R-like version: scan from the left and remember the last match.
 */
int strrindex_forward(char s[], char t[])
{
    int i, j, k;
    int pos = -1;

    for (i = 0; s[i] != '\0'; ++i) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k) {
            ;
        }

        if (k > 0 && t[k] == '\0') {
            pos = i;
        }
    }

    return pos;
}

int check_case(char s[], char t[], int expected)
{
    int right_result = strrindex(s, t);
    int forward_result = strrindex_forward(s, t);

    return right_result == expected && forward_result == expected;
}

int check_strrindex(void)
{
    if (!check_case("hello world", "world", 6)) {
        return 0;
    }

    if (!check_case("banana", "ana", 3)) {
        return 0;
    }

    if (!check_case("aaaa", "aa", 2)) {
        return 0;
    }

    if (!check_case("abc", "x", -1)) {
        return 0;
    }

    if (!check_case("abc", "", -1)) {
        return 0;
    }

    if (!check_case("", "abc", -1)) {
        return 0;
    }

    if (!check_case("abcabcabc", "abc", 6)) {
        return 0;
    }

    if (!check_case("abcabcabc", "bc", 7)) {
        return 0;
    }

    return 1;
}

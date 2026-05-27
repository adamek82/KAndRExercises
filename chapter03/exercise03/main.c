#include <stdio.h>

void expand(char s1[], char s2[]);
int valid_range(char left, char right);
int same_range_class(char left, char right);

/*
 * Exercise 3-3.
 *
 * Expand shorthand notations like a-z, A-Z and 0-9 in s1 into the equivalent
 * complete list in s2.
 *
 * We intentionally expand only ascending ranges whose endpoints belong to the
 * same class: lowercase letters, uppercase letters or digits. Other uses of '-'
 * are copied literally. This keeps cases like a-Z, z-a and a-9 predictable.
 * Leading and trailing '-' are also copied literally.
 */
int main(void)
{
    char out[1000];

    expand("a-z", out);
    printf("expand 1: %s\n", out);

    expand("A-Z", out);
    printf("expand 2: %s\n", out);

    expand("0-9", out);
    printf("expand 3: %s\n", out);

    expand("a-b-c", out);
    printf("expand 4: %s\n", out);

    expand("a-z0-9", out);
    printf("expand 5: %s\n", out);

    expand("-a-z", out);
    printf("expand 6: %s\n", out);

    expand("a-z-", out);
    printf("expand 7: %s\n", out);

    expand("a-Z", out);
    printf("expand 8: %s\n", out);

    expand("z-a", out);
    printf("expand 9: %s\n", out);

    expand("a-9", out);
    printf("expand 10: %s\n", out);

    return 0;
}

void expand(char s1[], char s2[])
{
    int i = 0, j = 0;
    char c;

    while (s1[i] != '\0') {
        if (s1[i] == '-' && j > 0 && valid_range(s2[j - 1], s1[i + 1])) {
            c = s2[j - 1] + 1;

            while (c <= s1[i + 1]) {
                s2[j] = c;
                ++j;
                ++c;
            }

            i = i + 2;
        } else {
            s2[j] = s1[i];
            ++j;
            ++i;
        }
    }

    s2[j] = '\0';
}

int valid_range(char left, char right)
{
    return left < right && same_range_class(left, right);
}

int same_range_class(char left, char right)
{
    if (left >= 'a' && left <= 'z') {
        return right >= 'a' && right <= 'z';
    }

    if (left >= 'A' && left <= 'Z') {
        return right >= 'A' && right <= 'Z';
    }

    if (left >= '0' && left <= '9') {
        return right >= '0' && right <= '9';
    }

    return 0;
}

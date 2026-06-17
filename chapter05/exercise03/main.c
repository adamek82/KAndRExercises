#include <stdio.h>
#include <string.h>

void strcat_pointer(char *s, char *t);
int check_strcat_pointer(void);
int check_case(char initial[], char suffix[], char expected[]);

/*
 * Exercise 5-3.
 *
 * Write a pointer version of strcat. The function appends string t to the end
 * of string s. The caller must ensure that s has enough space.
 */
int main(void)
{
    char s1[100] = "hello";
    char s2[100] = "";
    char s3[100] = "K&R";

    strcat_pointer(s1, " world");
    strcat_pointer(s2, "empty destination");
    strcat_pointer(s3, "");

    printf("strcat_pointer(\"hello\", \" world\") = %s\n", s1);
    printf("strcat_pointer(\"\", \"empty destination\") = %s\n", s2);
    printf("strcat_pointer(\"K&R\", \"\") = %s\n", s3);

    if (!check_strcat_pointer()) {
        printf("strcat_pointer checks: failed\n");
        return 1;
    }

    printf("strcat_pointer checks: ok\n");

    return 0;
}

void strcat_pointer(char *s, char *t)
{
    while (*s != '\0') {
        ++s;
    }

    while ((*s++ = *t++) != '\0') {
        ;
    }
}

int check_strcat_pointer(void)
{
    if (!check_case("hello", " world", "hello world")) {
        return 0;
    }

    if (!check_case("", "abc", "abc")) {
        return 0;
    }

    if (!check_case("abc", "", "abc")) {
        return 0;
    }

    if (!check_case("K", "&R", "K&R")) {
        return 0;
    }

    return 1;
}

int check_case(char initial[], char suffix[], char expected[])
{
    char buffer[100];

    strcpy(buffer, initial);
    strcat_pointer(buffer, suffix);

    return strcmp(buffer, expected) == 0;
}

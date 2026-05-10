#include <stdio.h>

/*
 * Exercise 1-6.
 *
 * Verify that the expression
 *
 *     getchar() != EOF
 *
 * evaluates to 0 or 1.
 *
 * getchar() returns either the next input character, converted to int,
 * or EOF. The != operator then compares this value with EOF and produces
 * 1 if the comparison is true, or 0 if it is false.
 */
int main(void)
{
    printf("%d\n", getchar() != EOF);

    return 0;
}

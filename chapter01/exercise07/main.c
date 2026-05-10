#include <stdio.h>

/*
 * Exercise 1-7.
 *
 * Write a program to print the value of EOF.
 *
 * EOF is an integer constant expression defined in <stdio.h>.
 * It is negative, but its exact value is implementation-defined.
 * On many systems it is -1.
 */
int main(void)
{
    printf("%d\n", EOF);

    return 0;
}

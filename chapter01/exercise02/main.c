#include <stdio.h>

/*
 * Exercise 1-2.
 *
 * Experiment to find out what happens when printf's argument string
 * contains \c, where c is some character not listed above.
 *
 * In ISO C, unknown escape sequences are not portable and should not be
 * used in real code. The actual experiment is guarded by
 * EXPERIMENT_UNKNOWN_ESCAPE so the normal build stays warning-free.
 */
int main(void)
{
    printf("K&R exercise 1-2\n");
    printf("The exercise asks what happens for an unknown escape sequence, such as backslash-c.\n");
    printf("In ISO C, such sequences are not portable and should not be used in real code.\n");
    printf("With GCC, enabling the experiment below produces a warning like:\n");
    printf("  warning: unknown escape sequence: '\\c'\n");
    printf("GCC commonly treats it as the ordinary character 'c', but portable code must not rely on this.\n");

#ifdef EXPERIMENT_UNKNOWN_ESCAPE
    printf("Actual experiment with an unknown escape sequence: \c\n");
#endif

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define TAB_WIDTH 8
#define MAX_TABSTOPS 100

int parse_tabstops(int argc, char *argv[], int tabstops[], int maxstops);
int next_tab_stop(int column, int tabstops[], int ntabs);
int next_default_tab_stop(int column);

/*
 * Exercise 5-11.
 *
 * Modify detab so that tab stops may be supplied as command-line arguments.
 * If no tab stops are supplied, use the default tab width.
 */
int main(int argc, char *argv[])
{
    int c;
    int column;
    int blanks;
    int tabstops[MAX_TABSTOPS];
    int ntabs;

    ntabs = parse_tabstops(argc, argv, tabstops, MAX_TABSTOPS);

    if (ntabs < 0) {
        printf("usage: detab [tabstop ...]\n");
        return 1;
    }

    column = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            blanks = next_tab_stop(column, tabstops, ntabs) - column;

            while (blanks > 0) {
                putchar(' ');
                ++column;
                --blanks;
            }
        } else if (c == '\n') {
            putchar(c);
            column = 0;
        } else {
            putchar(c);
            ++column;
        }
    }

    return 0;
}

int parse_tabstops(int argc, char *argv[], int tabstops[], int maxstops)
{
    int i;
    int value;
    char *end;

    for (i = 0; --argc > 0; ++i) {
        if (i >= maxstops) {
            return -1;
        }

        value = (int) strtol(*++argv, &end, 10);

        if (*end != '\0' || value <= 0) {
            return -1;
        }

        if (i > 0 && value <= tabstops[i - 1]) {
            return -1;
        }

        tabstops[i] = value;
    }

    return i;
}

int next_tab_stop(int column, int tabstops[], int ntabs)
{
    int i;

    if (ntabs == 0) {
        return next_default_tab_stop(column);
    }

    for (i = 0; i < ntabs; ++i) {
        if (tabstops[i] > column) {
            return tabstops[i];
        }
    }

    return next_default_tab_stop(column);
}

int next_default_tab_stop(int column)
{
    return column + TAB_WIDTH - column % TAB_WIDTH;
}

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_WIDTH 8
#define MAX_TABSTOPS 100

int parse_tabstops(int argc, char *argv[], int tabstops[], int maxstops);
int is_tab_stop(int column, int tabstops[], int ntabs);
int next_tab_stop(int column, int tabstops[], int ntabs);
int next_default_tab_stop(int column);
void entab(int tabstops[], int ntabs);

/*
 * Exercise 5-11.
 *
 * Modify entab so that tab stops may be supplied as command-line arguments.
 * If no tab stops are supplied, use the default tab width.
 */
int main(int argc, char *argv[])
{
    int tabstops[MAX_TABSTOPS];
    int ntabs;

    ntabs = parse_tabstops(argc, argv, tabstops, MAX_TABSTOPS);

    if (ntabs < 0) {
        printf("usage: entab [tabstop ...]\n");
        return 1;
    }

    entab(tabstops, ntabs);

    return 0;
}

void entab(int tabstops[], int ntabs)
{
    int c;
    int column;
    int blanks;

    column = 0;
    blanks = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++blanks;
            ++column;

            if (is_tab_stop(column, tabstops, ntabs)) {
                putchar('\t');
                blanks = 0;
            }
        } else {
            while (blanks > 0) {
                putchar(' ');
                --blanks;
            }

            putchar(c);

            if (c == '\n') {
                column = 0;
            } else if (c == '\t') {
                column = next_tab_stop(column, tabstops, ntabs);
            } else {
                ++column;
            }
        }
    }

    while (blanks > 0) {
        putchar(' ');
        --blanks;
    }
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

int is_tab_stop(int column, int tabstops[], int ntabs)
{
    int i;

    if (ntabs == 0) {
        return column % DEFAULT_TAB_WIDTH == 0;
    }

    for (i = 0; i < ntabs; ++i) {
        if (column == tabstops[i]) {
            return 1;
        }

        if (column < tabstops[i]) {
            return 0;
        }
    }

    return column % DEFAULT_TAB_WIDTH == 0;
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
    return column + DEFAULT_TAB_WIDTH - column % DEFAULT_TAB_WIDTH;
}

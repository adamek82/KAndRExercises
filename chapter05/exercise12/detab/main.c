#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_WIDTH 8
#define MAX_TABSTOPS 100

#define MODE_DEFAULT 0
#define MODE_LIST 1
#define MODE_REPEAT 2

struct TabSettings {
    int mode;
    int tabstops[MAX_TABSTOPS];
    int ntabs;
    int start;
    int increment;
};

int parse_tab_settings(int argc, char *argv[], struct TabSettings *settings);
int parse_positive_number(char *s, int *value);
int next_tab_stop(int column, struct TabSettings *settings);
int next_default_tab_stop(int column);
void detab(struct TabSettings *settings);

/*
 * Exercise 5-12.
 *
 * Extend detab so that it accepts the shorthand -m +n, meaning tab stops
 * every n columns, starting at column m. If no tab stops are supplied, use
 * the default tab width.
 */
int main(int argc, char *argv[])
{
    struct TabSettings settings;

    if (!parse_tab_settings(argc, argv, &settings)) {
        printf("usage: detab [tabstop ...] | [-m] [+n]\n");
        return 1;
    }

    detab(&settings);

    return 0;
}

void detab(struct TabSettings *settings)
{
    int c;
    int column;
    int blanks;

    column = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            blanks = next_tab_stop(column, settings) - column;

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
}

int parse_tab_settings(int argc, char *argv[], struct TabSettings *settings)
{
    int i;
    int value;

    settings->mode = MODE_DEFAULT;
    settings->ntabs = 0;
    settings->start = DEFAULT_TAB_WIDTH;
    settings->increment = DEFAULT_TAB_WIDTH;

    if (argc == 1) {
        return 1;
    }

    if (argv[1][0] == '-' || argv[1][0] == '+') {
        settings->mode = MODE_REPEAT;

        while (--argc > 0) {
            ++argv;

            if ((*argv)[0] == '-') {
                if (!parse_positive_number(*argv + 1, &value)) {
                    return 0;
                }

                settings->start = value;
            } else if ((*argv)[0] == '+') {
                if (!parse_positive_number(*argv + 1, &value)) {
                    return 0;
                }

                settings->increment = value;

                if (settings->start == DEFAULT_TAB_WIDTH) {
                    settings->start = value;
                }
            } else {
                return 0;
            }
        }

        return settings->start > 0 && settings->increment > 0;
    }

    settings->mode = MODE_LIST;

    for (i = 0; --argc > 0; ++i) {
        if (i >= MAX_TABSTOPS) {
            return 0;
        }

        ++argv;

        if (!parse_positive_number(*argv, &value)) {
            return 0;
        }

        if (i > 0 && value <= settings->tabstops[i - 1]) {
            return 0;
        }

        settings->tabstops[i] = value;
    }

    settings->ntabs = i;

    return 1;
}

int parse_positive_number(char *s, int *value)
{
    char *end;
    long parsed;

    if (*s == '\0') {
        return 0;
    }

    parsed = strtol(s, &end, 10);

    if (*end != '\0' || parsed <= 0) {
        return 0;
    }

    *value = (int) parsed;

    return 1;
}

int next_tab_stop(int column, struct TabSettings *settings)
{
    int i;
    int steps;

    if (settings->mode == MODE_DEFAULT) {
        return next_default_tab_stop(column);
    }

    if (settings->mode == MODE_REPEAT) {
        if (column < settings->start) {
            return settings->start;
        }

        steps = (column - settings->start) / settings->increment + 1;

        return settings->start + steps * settings->increment;
    }

    for (i = 0; i < settings->ntabs; ++i) {
        if (settings->tabstops[i] > column) {
            return settings->tabstops[i];
        }
    }

    return next_default_tab_stop(column);
}

int next_default_tab_stop(int column)
{
    return column + DEFAULT_TAB_WIDTH - column % DEFAULT_TAB_WIDTH;
}

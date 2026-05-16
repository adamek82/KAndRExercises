#include <stdio.h>

/*
 * 20 keeps examples and tests readable. A real-world formatter would commonly
 * use a wider value, such as 80 or 120 columns.
 */
#define FOLD_COLUMN 20
#define TAB_WIDTH 8

int add_char(char line[], int pos, int c);
int fold_line(char line[], int pos);
void print_line(char line[], int pos);
int is_blank(int c);

/*
 * Exercise 1-22.
 *
 * Write a program to fold long input lines into shorter lines after the last
 * non-blank character before the n-th column. The program should behave
 * sensibly for very long lines and when there are no blanks or tabs before
 * the fold column.
 *
 * FOLD_COLUMN is a symbolic constant. At this point in the book, command-line
 * arguments have not been introduced yet, so using a symbolic constant is the
 * natural way to represent n.
 *
 * Tabs are expanded to blanks before folding. This makes column counting
 * unambiguous and reuses the same idea as detab from exercise 1-20.
 */
int main(void)
{
    int c;
    int pos, blanks;
    char line[FOLD_COLUMN + 1];

    pos = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            blanks = TAB_WIDTH - pos % TAB_WIDTH;

            while (blanks > 0) {
                pos = add_char(line, pos, ' ');
                --blanks;
            }
        } else if (c == '\n') {
            print_line(line, pos);
            putchar('\n');
            pos = 0;
        } else {
            pos = add_char(line, pos, c);
        }
    }

    if (pos > 0) {
        print_line(line, pos);
    }

    return 0;
}

/*
 * Add one character to the current output line. If the line reaches the fold
 * column, fold it immediately and return the new position in the rebuilt line.
 */
int add_char(char line[], int pos, int c)
{
    line[pos] = c;
    ++pos;

    if (pos >= FOLD_COLUMN) {
        pos = fold_line(line, pos);
    }

    return pos;
}

/*
 * Fold the current line and return the new position.
 *
 * If there is a blank before the fold column, print up to the last non-blank
 * character before that blank run. The blank run itself is discarded.
 *
 * If there is no blank before the fold column, print the whole buffer. This
 * handles very long words by splitting them at FOLD_COLUMN.
 */
int fold_line(char line[], int pos)
{
    int i, j;
    int print_end;
    int remainder_start;

    i = pos - 1;
    while (i >= 0 && !is_blank(line[i])) {
        --i;
    }

    if (i < 0) {
        print_line(line, pos);
        putchar('\n');
        return 0;
    }

    print_end = i;
    while (print_end > 0 && is_blank(line[print_end - 1])) {
        --print_end;
    }

    if (print_end > 0) {
        print_line(line, print_end);
        putchar('\n');
    }

    remainder_start = print_end;
    while (remainder_start < pos && is_blank(line[remainder_start])) {
        ++remainder_start;
    }

    j = 0;
    while (remainder_start < pos) {
        line[j] = line[remainder_start];
        ++j;
        ++remainder_start;
    }

    return j;
}

/*
 * Print exactly pos characters from line.
 */
void print_line(char line[], int pos)
{
    int i;

    for (i = 0; i < pos; ++i) {
        putchar(line[i]);
    }
}

int is_blank(int c)
{
    return c == ' ' || c == '\t';
}

#include <stdio.h>

void skip_block_comment(void);
void skip_line_comment(void);
void echo_quote(int quote);

/*
 * Exercise 1-23.
 *
 * Write a program to remove all comments from a C program. Character
 * constants and string literals must be handled correctly. C comments do
 * not nest.
 *
 * Block comments are replaced by one blank, not by an empty string, so that
 * token separation is preserved. For example, if a block comment appears
 * between int and x, the result should be int x, not intx.
 *
 * The original K&R exercise predates C99 line comments, but this program also
 * handles // comments because they are part of modern C.
 */
int main(void)
{
    int c, d;

    while ((c = getchar()) != EOF) {
        if (c == '/') {
            d = getchar();

            if (d == '*') {
                putchar(' ');
                skip_block_comment();
            } else if (d == '/') {
                skip_line_comment();
            } else {
                putchar(c);

                if (d != EOF) {
                    if (d == '\'' || d == '"') {
                        echo_quote(d);
                    } else {
                        putchar(d);
                    }
                }
            }
        } else if (c == '\'' || c == '"') {
            echo_quote(c);
        } else {
            putchar(c);
        }
    }

    return 0;
}

/*
 * Skip input until the end of a block comment.
 */
void skip_block_comment(void)
{
    int c;
    int previous;

    previous = 0;

    while ((c = getchar()) != EOF) {
        if (previous == '*' && c == '/') {
            return;
        }

        previous = c;
    }
}

/*
 * Skip input until the end of a line comment.
 */
void skip_line_comment(void)
{
    int c;

    while ((c = getchar()) != EOF && c != '\n') {
        ;
    }

    if (c == '\n') {
        putchar('\n');
    }
}

/*
 * Echo a character constant or string literal.
 *
 * The opening quote has already been read. Escaped characters are copied
 * together with their backslash so that \" or \' do not end the literal.
 */
void echo_quote(int quote)
{
    int c, d;

    putchar(quote);

    while ((c = getchar()) != EOF) {
        putchar(c);

        if (c == '\\') {
            d = getchar();

            if (d == EOF) {
                return;
            }

            putchar(d);
        } else if (c == quote) {
            return;
        }
    }
}

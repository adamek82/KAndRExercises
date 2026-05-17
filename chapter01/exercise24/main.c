#include <stdio.h>

#define MAX_STACK 1000

char stack[MAX_STACK];
int top;

int check_char(int c);
int matching_pair(int open, int close);
int is_opening(int c);
int is_closing(int c);
void skip_block_comment(void);
void skip_line_comment(void);
void skip_quote(int quote);

/*
 * Exercise 1-24.
 *
 * Write a program to check a C program for rudimentary syntax errors like
 * unbalanced parentheses, brackets and braces. Quoted strings, character
 * constants, escape sequences and comments must be handled correctly.
 *
 * This is not a full C parser. It only checks (), [] and {} balance and
 * nesting order, while ignoring those characters inside comments and quoted
 * literals.
 *
 * The stack and its top index are external variables. This keeps the helper
 * functions simple at this stage of the book, before pointers are introduced.
 */
int main(void)
{
    int c, d;

    top = 0;

    while ((c = getchar()) != EOF) {
        if (c == '/') {
            d = getchar();

            if (d == '*') {
                skip_block_comment();
            } else if (d == '/') {
                skip_line_comment();
            } else {
                if (!check_char(c)) {
                    return 1;
                }

                if (d != EOF) {
                    if (d == '\'' || d == '"') {
                        skip_quote(d);
                    } else if (!check_char(d)) {
                        return 1;
                    }
                }
            }
        } else if (c == '\'' || c == '"') {
            skip_quote(c);
        } else if (!check_char(c)) {
            return 1;
        }
    }

    if (top > 0) {
        printf("unmatched opening %c\n", stack[top - 1]);
        return 1;
    }

    printf("ok\n");
    return 0;
}

/*
 * Check one ordinary source character.
 *
 * Returns 1 if processing can continue, 0 if a syntax error was found.
 */
int check_char(int c)
{
    if (is_opening(c)) {
        if (top >= MAX_STACK) {
            printf("nesting too deep\n");
            return 0;
        }

        stack[top] = c;
        ++top;
    } else if (is_closing(c)) {
        if (top == 0 || !matching_pair(stack[top - 1], c)) {
            printf("unmatched closing %c\n", c);
            return 0;
        }

        --top;
    }

    return 1;
}

int matching_pair(int open, int close)
{
    return (open == '(' && close == ')')
        || (open == '[' && close == ']')
        || (open == '{' && close == '}');
}

int is_opening(int c)
{
    return c == '(' || c == '[' || c == '{';
}

int is_closing(int c)
{
    return c == ')' || c == ']' || c == '}';
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
}

/*
 * Skip a string literal or character constant.
 *
 * The opening quote has already been read. Escaped characters are skipped
 * together with their backslash so that \" or \' do not end the literal.
 */
void skip_quote(int quote)
{
    int c, d;

    while ((c = getchar()) != EOF) {
        if (c == '\\') {
            d = getchar();

            if (d == EOF) {
                return;
            }
        } else if (c == quote) {
            return;
        }
    }
}

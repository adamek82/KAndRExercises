#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]);
void push(double f);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);
int getch(void);
void ungetch(int c);

/*
 * Exercise 4-4.
 *
 * Add commands to print the top element of the stack without popping it,
 * duplicate it, swap the top two elements, and clear the stack.
 *
 * Commands:
 *
 *     ?   print the top element without popping it
 *     d   duplicate the top element
 *     s   swap the top two elements
 *     c   clear the stack
 */
int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;

        case '+':
            push(pop() + pop());
            break;

        case '*':
            push(pop() * pop());
            break;

        case '-':
            op2 = pop();
            push(pop() - op2);
            break;

        case '/':
            op2 = pop();
            if (op2 != 0.0) {
                push(pop() / op2);
            } else {
                printf("error: zero divisor\n");
            }
            break;

        case '%':
            op2 = pop();
            if (op2 != 0.0) {
                push(fmod(pop(), op2));
            } else {
                printf("error: zero divisor for modulus\n");
            }
            break;

        case '?':
            print_top();
            break;

        case 'd':
            duplicate_top();
            break;

        case 's':
            swap_top();
            break;

        case 'c':
            clear_stack();
            break;

        case '\n':
            printf("\t%.8g\n", pop());
            break;

        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }

    return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL) {
        val[sp] = f;
        ++sp;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void)
{
    if (sp > 0) {
        --sp;
        return val[sp];
    }

    printf("error: stack empty\n");
    return 0.0;
}

void print_top(void)
{
    if (sp > 0) {
        printf("\t%.8g\n", val[sp - 1]);
    } else {
        printf("error: stack empty\n");
    }
}

void duplicate_top(void)
{
    if (sp > 0) {
        push(val[sp - 1]);
    } else {
        printf("error: stack empty\n");
    }
}

void swap_top(void)
{
    double temp;

    if (sp >= 2) {
        temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    } else {
        printf("error: stack has fewer than two elements\n");
    }
}

void clear_stack(void)
{
    sp = 0;
}

int getop(char s[])
{
    int i, c, next;

    while ((c = getch()) == ' ' || c == '\t') {
        ;
    }

    if (c == EOF) {
        return EOF;
    }

    s[0] = (char) c;
    s[1] = '\0';

    if (c == '-') {
        next = getch();

        if (!isdigit((unsigned char) next) && next != '.') {
            if (next != EOF) {
                ungetch(next);
            }

            return c;
        }

        s[1] = (char) next;
        i = 1;
        c = next;
    } else if (!isdigit((unsigned char) c) && c != '.') {
        return c;
    } else {
        i = 0;
    }

    if (isdigit((unsigned char) c)) {
        while (isdigit((unsigned char) (s[++i] = (char) (c = getch())))) {
            ;
        }
    }

    if (c == '.') {
        while (isdigit((unsigned char) (s[++i] = (char) (c = getch())))) {
            ;
        }
    }

    s[i] = '\0';

    if (c != EOF) {
        ungetch(c);
    }

    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    if (bufp > 0) {
        --bufp;
        return buf[bufp];
    }

    return getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp] = (char) c;
        ++bufp;
    }
}

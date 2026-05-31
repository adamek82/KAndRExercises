#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]);
void push(double f);
double pop(void);
int getch(void);
void ungetch(int c);

/*
 * Exercise 4-3.
 *
 * Extend the reverse Polish calculator by adding the modulus operator and
 * support for negative numbers.
 *
 * A minus sign is treated as part of a number only when it is followed by a
 * digit or a decimal point. Otherwise it remains the subtraction operator.
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

int getop(char s[])
{
    int i, c, next;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        ;
    }

    s[1] = '\0';

    if (c == '-') {
        next = getch();

        if (!isdigit((unsigned char) next) && next != '.') {
            if (next != EOF) {
                ungetch(next);
            }

            return c;
        }

        s[1] = next;
        i = 1;
        c = next;
    } else if (!isdigit((unsigned char) c) && c != '.') {
        return c;
    } else {
        i = 0;
    }

    if (isdigit((unsigned char) c)) {
        while (isdigit((unsigned char) (s[++i] = c = getch()))) {
            ;
        }
    }

    if (c == '.') {
        while (isdigit((unsigned char) (s[++i] = c = getch()))) {
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
        buf[bufp] = c;
        ++bufp;
    }
}

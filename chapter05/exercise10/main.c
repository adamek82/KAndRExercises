#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXVAL 100

#define NUMBER '0'

int getop(char *s);
void push(double f);
double pop(void);
int stack_size(void);
int is_number(char *s);

int sp = 0;
double val[MAXVAL];

int main(int argc, char *argv[])
{
    int type;
    double op2;

    while (--argc > 0) {
        type = getop(*++argv);

        switch (type) {
        case NUMBER:
            push(atof(*argv));
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
                return 1;
            }

            break;

        default:
            printf("error: unknown command %s\n", *argv);
            return 1;
        }
    }

    if (stack_size() != 1) {
        printf("error: expression leaves %d values on stack\n", stack_size());
        return 1;
    }

    printf("%.8g\n", pop());

    return 0;
}

int getop(char *s)
{
    if (is_number(s)) {
        return NUMBER;
    }

    if (*s != '\0' && *(s + 1) == '\0') {
        return *s;
    }

    return '?';
}

int is_number(char *s)
{
    int c;
    int saw_digit;

    if (*s == '+' || *s == '-') {
        ++s;
    }

    saw_digit = 0;

    while (isdigit((unsigned char) *s)) {
        saw_digit = 1;
        ++s;
    }

    if (*s == '.') {
        ++s;

        while (isdigit((unsigned char) *s)) {
            saw_digit = 1;
            ++s;
        }
    }

    c = *s;

    return saw_digit && c == '\0';
}

void push(double f)
{
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, cannot push %g\n", f);
        exit(1);
    }
}

double pop(void)
{
    if (sp > 0) {
        return val[--sp];
    }

    printf("error: stack empty\n");
    exit(1);
}

int stack_size(void)
{
    return sp;
}

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define NAME 'n'
#define ASSIGN ':'

int getop(char s[]);
void push(double f);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);
void assign_variable(char name);
void mathfn(char s[]);
void print_value(double f);
int stack_count(void);
int getch(void);
void ungetch(int c);

double variable[26];
double last_printed = 0.0;

/*
 * Exercise 4-6.
 *
 * Add commands for handling variables. The calculator provides twenty-six
 * variables named A through Z, and v stores the most recently printed value.
 *
 * Variables:
 *
 *     A..Z   push the value of a variable
 *     :A     assign the top stack value to variable A without popping it
 *     v      push the most recently printed value
 *
 * The previous calculator features are preserved: %, negative numbers, stack
 * commands, and library functions such as sin, exp, and pow.
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

        case NAME:
            mathfn(s);
            break;

        case ASSIGN:
            assign_variable(s[1]);
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

        case 'v':
            push(last_printed);
            break;

        case '\n':
            if (stack_count() > 0) {
                print_value(pop());
            } else {
                printf("error: stack empty\n");
            }
            break;

        default:
            if (type >= 'A' && type <= 'Z') {
                push(variable[type - 'A']);
            } else {
                printf("error: unknown command %s\n", s);
            }
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

int stack_count(void)
{
    return sp;
}

void print_value(double f)
{
    last_printed = f;
    printf("\t%.8g\n", f);
}

void print_top(void)
{
    if (sp > 0) {
        print_value(val[sp - 1]);
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

void assign_variable(char name)
{
    if (name >= 'A' && name <= 'Z') {
        if (sp > 0) {
            variable[name - 'A'] = val[sp - 1];
        } else {
            printf("error: stack empty\n");
        }
    } else {
        printf("error: invalid variable name %c\n", name);
    }
}

void mathfn(char s[])
{
    double op2;

    if (strcmp(s, "sin") == 0) {
        push(sin(pop()));
    } else if (strcmp(s, "cos") == 0) {
        push(cos(pop()));
    } else if (strcmp(s, "exp") == 0) {
        push(exp(pop()));
    } else if (strcmp(s, "pow") == 0) {
        op2 = pop();
        push(pow(pop(), op2));
    } else {
        printf("error: unknown function %s\n", s);
    }
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

    if (c == ':') {
        next = getch();

        if (next >= 'A' && next <= 'Z') {
            s[1] = (char) next;
            s[2] = '\0';
            return ASSIGN;
        }

        if (next != EOF) {
            ungetch(next);
        }

        return c;
    }

    if (islower((unsigned char) c)) {
        i = 0;

        while ((c = getch()) != EOF && islower((unsigned char) c)) {
            s[++i] = (char) c;
        }

        s[i + 1] = '\0';

        if (c != EOF) {
            ungetch(c);
        }

        if (i > 0) {
            return NAME;
        }

        return s[0];
    }

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
        while ((c = getch()) != EOF && isdigit((unsigned char) c)) {
            s[++i] = (char) c;
        }

        if (c == '.') {
            s[++i] = (char) c;

            while ((c = getch()) != EOF && isdigit((unsigned char) c)) {
                s[++i] = (char) c;
            }
        }
    } else if (c == '.') {
        while ((c = getch()) != EOF && isdigit((unsigned char) c)) {
            s[++i] = (char) c;
        }
    }

    s[i + 1] = '\0';

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

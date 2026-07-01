#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LINES 10
#define MAXLINES 1000
#define MAXLEN 1000
#define MAXSTOR 100000

int get_line(char *s, int lim);
int parse_count(int argc, char *argv[]);
void store_line(char *lineptr[], char *linestor, int *pstore, int index, char *line, int len);
void print_tail(char *lineptr[], int nlines, int next_index, int requested);

int main(int argc, char *argv[])
{
    int n;
    int len;
    int nlines, index, store;
    char line[MAXLEN];
    char *lineptr[MAXLINES];
    char linestor[MAXSTOR];

    n = parse_count(argc, argv);

    if (n < 0) {
        printf("usage: tail [-n]\n");
        return 1;
    }

    nlines = 0;
    index = 0;
    store = 0;

    while ((len = get_line(line, MAXLEN)) > 0) {
        if (store + len + 1 > MAXSTOR) {
            store = 0;
        }

        store_line(lineptr, linestor, &store, index, line, len);

        index = (index + 1) % MAXLINES;

        if (nlines < MAXLINES) {
            ++nlines;
        }
    }

    print_tail(lineptr, nlines, index, n);

    return 0;
}

int get_line(char *s, int lim)
{
    int c = EOF;
    char *start = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        *s++ = (char) c;
    }

    if (c == '\n') {
        *s++ = (char) c;
    }

    *s = '\0';

    return s - start;
}

int parse_count(int argc, char *argv[])
{
    char *end;
    long n;

    if (argc == 1) {
        return DEFAULT_LINES;
    }

    if (argc != 2 || argv[1][0] != '-') {
        return -1;
    }

    n = strtol(argv[1] + 1, &end, 10);

    if (*end != '\0' || n < 0) {
        return -1;
    }

    if (n > MAXLINES) {
        return MAXLINES;
    }

    return (int) n;
}

void store_line(char *lineptr[], char *linestor, int *pstore, int index, char *line, int len)
{
    lineptr[index] = linestor + *pstore;
    strcpy(lineptr[index], line);
    *pstore += len + 1;
}

void print_tail(char *lineptr[], int nlines, int next_index, int requested)
{
    int i;
    int first;

    if (requested > nlines) {
        requested = nlines;
    }

    if (requested == 0) {
        return;
    }

    first = next_index - requested;

    if (first < 0) {
        first += MAXLINES;
    }

    for (i = 0; i < requested; ++i) {
        printf("%s", lineptr[(first + i) % MAXLINES]);
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXSTOR 200000

#define NUMERIC 1
#define REVERSE 2

int get_line(char *s, int lim);
int readlines(char *lineptr[], int maxlines, char storage[], int maxstor);
void writelines(char *lineptr[], int nlines, int reverse);
void quick_sort(char *v[], int left, int right,
                int (*comp)(const char *, const char *));
void swap(char *v[], int i, int j);
int numcmp(const char *s1, const char *s2);
int parse_options(int argc, char *argv[], int *options);

/*
 * Exercise 5-14.
 *
 * Modify the sort program to handle a -r flag, which indicates sorting in
 * reverse (decreasing) order. Be sure that -r works with -n.
 */
int main(int argc, char *argv[])
{
    static char storage[MAXSTOR];
    char *lineptr[MAXLINES];
    int nlines;
    int options;
    int (*comp)(const char *, const char *);

    if (!parse_options(argc, argv, &options)) {
        fprintf(stderr, "usage: sort [-n] [-r]\n");
        return 1;
    }

    nlines = readlines(lineptr, MAXLINES, storage, MAXSTOR);
    if (nlines < 0) {
        fprintf(stderr, "sort: input exceeds configured limits\n");
        return 1;
    }

    comp = (options & NUMERIC) ? numcmp : strcmp;
    quick_sort(lineptr, 0, nlines - 1, comp);
    writelines(lineptr, nlines, options & REVERSE);

    return 0;
}

int parse_options(int argc, char *argv[], int *options)
{
    int i;
    char *p;

    *options = 0;

    for (i = 1; i < argc; ++i) {
        if (argv[i][0] != '-' || argv[i][1] == '\0') return 0;

        for (p = argv[i] + 1; *p != '\0'; ++p) {
            if (*p == 'n') *options |= NUMERIC;
            else if (*p == 'r') *options |= REVERSE;
            else return 0;
        }
    }

    return 1;
}

int get_line(char *s, int lim)
{
    int c;
    int too_long = 0;
    char *start = s;
    char *end = s + lim - 1;

    while ((c = getchar()) != EOF && c != '\n') {
        if (s < end) *s++ = (char) c;
        else too_long = 1;
    }

    if (c == '\n') {
        if (s < end) *s++ = (char) c;
        else too_long = 1;
    }

    *s = '\0';

    return too_long ? -1 : (int) (s - start);
}

int readlines(char *lineptr[], int maxlines, char storage[], int maxstor)
{
    int len;
    int nlines = 0;
    int used = 0;
    char line[MAXLEN];

    while ((len = get_line(line, MAXLEN)) != 0) {
        if (len < 0) return -1;

        if (line[len - 1] == '\n') {
            line[--len] = '\0';
        }

        if (nlines >= maxlines || len + 1 > maxstor - used) {
            return -1;
        }

        lineptr[nlines++] = storage + used;
        strcpy(storage + used, line);
        used += len + 1;
    }

    return nlines;
}

void writelines(char *lineptr[], int nlines, int reverse)
{
    int i;

    if (reverse) {
        for (i = nlines - 1; i >= 0; --i) {
            puts(lineptr[i]);
        }
    } else {
        for (i = 0; i < nlines; ++i) {
            puts(lineptr[i]);
        }
    }
}

void quick_sort(char *v[], int left, int right,
                int (*comp)(const char *, const char *))
{
    int i;
    int last;

    if (left >= right) return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; ++i) {
        if (comp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    quick_sort(v, left, last - 1, comp);
    quick_sort(v, last + 1, right, comp);
}

void swap(char *v[], int i, int j)
{
    char *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(const char *s1, const char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

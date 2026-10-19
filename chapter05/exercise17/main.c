#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXSTOR 200000
#define MAXKEYS 16

#define NUMERIC 1
#define REVERSE 2
#define FOLD 4
#define DIRECTORY 8

static int key_starts[MAXKEYS];
static int key_ends[MAXKEYS];
static int key_options[MAXKEYS];
static int nkeys;
static int options;

int get_line(char *s, int lim);
int readlines(char *lineptr[], int maxlines, char storage[], int maxstor);
void writelines(char *lineptr[], int nlines);
void quick_sort(char *v[], int left, int right,
                int (*comp)(const char *, const char *));
void swap(char *v[], int i, int j);
int parse_options(int argc, char *argv[]);
int parse_key(const char *s, int *start, int *end, int *flags);
int parse_flags(const char *s, int *flags);
void get_field(const char *line, int start, int end,
               const char **field, size_t *length);
int next_char(const char **s, size_t *length, int flags);
int compare_text(const char *a, size_t alen,
                 const char *b, size_t blen, int flags);
double field_number(const char *s, size_t length);
int compare_fields(const char *a, size_t alen,
                   const char *b, size_t blen, int flags);
int compare_lines(const char *a, const char *b);

/*
 * Exercise 5-17.
 *
 * Add a field-handling capability, so sorting may be done on fields within
 * lines, each field sorted according to an independent set of options.
 * (The index for this book was sorted with -df for the index category and
 * -n for the page numbers.)
 */
int main(int argc, char *argv[])
{
    static char storage[MAXSTOR];
    char *lineptr[MAXLINES];
    int nlines;

    if (!parse_options(argc, argv)) {
        fprintf(stderr, "usage: sort [-n] [-r] [-f] [-d]\n"
                        "       sort -k START:END:FLAGS [-k START:END:FLAGS ...]\n");
        return 1;
    }

    nlines = readlines(lineptr, MAXLINES, storage, MAXSTOR);
    if (nlines < 0) {
        fprintf(stderr, "sort: input exceeds configured limits\n");
        return 1;
    }

    quick_sort(lineptr, 0, nlines - 1, compare_lines);
    writelines(lineptr, nlines);
    return 0;
}

int parse_flags(const char *s, int *flags)
{
    for (; *s != '\0'; ++s) {
        switch (*s) {
        case 'n': *flags |= NUMERIC; break;
        case 'r': *flags |= REVERSE; break;
        case 'f': *flags |= FOLD; break;
        case 'd': *flags |= DIRECTORY; break;
        default: return 0;
        }
    }
    return 1;
}

int parse_key(const char *s, int *start, int *end, int *flags)
{
    char *tail;
    long position;

    if (!isdigit((unsigned char) *s)) return 0;
    errno = 0;
    position = strtol(s, &tail, 10);
    if (errno == ERANGE || position > INT_MAX) return 0;

    *start = (int) position;
    *end = -1;
    *flags = 0;

    if (*tail == '\0') return 1;
    if (*tail++ != ':') return 0;

    if (isdigit((unsigned char) *tail)) {
        s = tail;
        errno = 0;
        position = strtol(s, &tail, 10);
        if (errno == ERANGE || position > INT_MAX || position < *start) return 0;
        *end = (int) position;
    }

    if (*tail == '\0') return 1;
    if (*tail++ != ':') return 0;
    return parse_flags(tail, flags);
}

int parse_options(int argc, char *argv[])
{
    int i;

    nkeys = 0;
    options = 0;

    for (i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-k") == 0) {
            if (++i >= argc || nkeys >= MAXKEYS ||
                !parse_key(argv[i], &key_starts[nkeys], &key_ends[nkeys],
                           &key_options[nkeys])) return 0;
            ++nkeys;
        } else {
            if (argv[i][0] != '-' || argv[i][1] == '\0' ||
                !parse_flags(argv[i] + 1, &options)) return 0;
        }
    }

    return nkeys == 0 || options == 0;
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

        if (line[len - 1] == '\n') line[--len] = '\0';

        if (nlines >= maxlines || len + 1 > maxstor - used) return -1;

        lineptr[nlines++] = storage + used;
        strcpy(storage + used, line);
        used += len + 1;
    }

    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; ++i) puts(lineptr[i]);
}

void get_field(const char *line, int start, int end,
               const char **field, size_t *length)
{
    size_t n = strlen(line);
    size_t first = (size_t) start < n ? (size_t) start : n;
    size_t last = end < 0 || (size_t) end > n ? n : (size_t) end;

    if (last < first) last = first;
    *field = line + first;
    *length = last - first;
}

int next_char(const char **s, size_t *length, int flags)
{
    while (*length > 0) {
        int c = (unsigned char) **s;
        ++*s;
        --*length;

        if ((flags & DIRECTORY) && !isalnum(c) && !isblank(c)) continue;
        return (flags & FOLD) ? tolower(c) : c;
    }
    return 0;
}

int compare_text(const char *a, size_t alen,
                 const char *b, size_t blen, int flags)
{
    int c1;
    int c2;

    for (;;) {
        c1 = next_char(&a, &alen, flags);
        c2 = next_char(&b, &blen, flags);
        if (c1 != c2) return (c1 > c2) - (c1 < c2);
        if (c1 == 0) return 0;
    }
}

double field_number(const char *s, size_t length)
{
    char text[MAXLEN];

    memcpy(text, s, length);
    text[length] = '\0';
    return atof(text);
}

int compare_fields(const char *a, size_t alen,
                   const char *b, size_t blen, int flags)
{
    int result;

    if (flags & NUMERIC) {
        double v1 = field_number(a, alen);
        double v2 = field_number(b, blen);
        result = (v1 > v2) - (v1 < v2);
    } else {
        result = compare_text(a, alen, b, blen, flags);
    }
    return (flags & REVERSE) ? -result : result;
}

int compare_lines(const char *a, const char *b)
{
    int i;
    int result;
    const char *field_a;
    const char *field_b;
    size_t len_a;
    size_t len_b;

    if (nkeys == 0) {
        return compare_fields(a, strlen(a), b, strlen(b), options);
    }

    for (i = 0; i < nkeys; ++i) {
        get_field(a, key_starts[i], key_ends[i], &field_a, &len_a);
        get_field(b, key_starts[i], key_ends[i], &field_b, &len_b);
        result = compare_fields(field_a, len_a, field_b, len_b, key_options[i]);
        if (result != 0) return result;
    }

    return 0;
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
        if (comp(v[i], v[left]) < 0) swap(v, ++last, i);
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

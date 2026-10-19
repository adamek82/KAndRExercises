
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

struct Field {
    const char *start;
    size_t length;
};

struct SortKey {
    size_t start;
    size_t end;
    int has_end;
    int options;
};

struct SortConfig {
    struct SortKey keys[MAXKEYS];
    int nkeys;
    int options;
};

int get_line(char *s, int lim);
int readlines(char *lineptr[], int maxlines, char storage[], int maxstor);
void writelines(char *lineptr[], int nlines);
void quick_sort(char *v[], int left, int right,
                int (*comp)(const char *, const char *, const struct SortConfig *),
                const struct SortConfig *config);
void swap(char *v[], int i, int j);
int parse_options(int argc, char *argv[], struct SortConfig *config);
int parse_key(const char *s, struct SortKey *key);
int parse_flags(const char *s, int *options);
struct Field get_field(const char *line, const struct SortKey *key);
int next_char(struct Field *field, int options);
int compare_text(struct Field a, struct Field b, int options);
double field_number(struct Field field);
int compare_fields(struct Field a, struct Field b, int options);
int compare_lines(const char *a, const char *b, const struct SortConfig *config);

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
    struct SortConfig config;
    int nlines;

    if (!parse_options(argc, argv, &config)) {
        fprintf(stderr, "usage: sort [-n] [-r] [-f] [-d]\n"
                        "       sort -k START:END:FLAGS [-k START:END:FLAGS ...]\n");
        return 1;
    }

    nlines = readlines(lineptr, MAXLINES, storage, MAXSTOR);
    if (nlines < 0) {
        fprintf(stderr, "sort: input exceeds configured limits\n");
        return 1;
    }

    quick_sort(lineptr, 0, nlines - 1, compare_lines, &config);
    writelines(lineptr, nlines);
    return 0;
}

int parse_flags(const char *s, int *options)
{
    for (; *s != '\0'; ++s) {
        switch (*s) {
        case 'n': *options |= NUMERIC; break;
        case 'r': *options |= REVERSE; break;
        case 'f': *options |= FOLD; break;
        case 'd': *options |= DIRECTORY; break;
        default: return 0;
        }
    }
    return 1;
}

int parse_key(const char *s, struct SortKey *key)
{
    char *end;
    long position;

    if (!isdigit((unsigned char) *s)) return 0;
    errno = 0;
    position = strtol(s, &end, 10);
    if (errno == ERANGE || position > INT_MAX) return 0;

    key->start = (size_t) position;
    key->end = 0;
    key->has_end = 0;
    key->options = 0;

    if (*end == '\0') return 1;
    if (*end++ != ':') return 0;

    if (isdigit((unsigned char) *end)) {
        s = end;
        errno = 0;
        position = strtol(s, &end, 10);
        if (errno == ERANGE || position > INT_MAX ||
            (size_t) position < key->start) return 0;
        key->end = (size_t) position;
        key->has_end = 1;
    }

    if (*end == '\0') return 1;
    if (*end++ != ':') return 0;
    return parse_flags(end, &key->options);
}

int parse_options(int argc, char *argv[], struct SortConfig *config)
{
    int i;

    config->nkeys = 0;
    config->options = 0;

    for (i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-k") == 0) {
            if (++i >= argc || config->nkeys >= MAXKEYS ||
                !parse_key(argv[i], &config->keys[config->nkeys])) return 0;
            ++config->nkeys;
        } else {
            if (argv[i][0] != '-' || argv[i][1] == '\0' ||
                !parse_flags(argv[i] + 1, &config->options)) return 0;
        }
    }

    return config->nkeys == 0 || config->options == 0;
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

struct Field get_field(const char *line, const struct SortKey *key)
{
    size_t length = strlen(line);
    size_t start = key->start < length ? key->start : length;
    size_t end = length;
    struct Field field;

    if (key->has_end && key->end < end) end = key->end;
    if (end < start) end = start;

    field.start = line + start;
    field.length = end - start;
    return field;
}

int next_char(struct Field *field, int options)
{
    while (field->length > 0) {
        int c = (unsigned char) *field->start++;
        --field->length;

        if ((options & DIRECTORY) && !isalnum(c) && !isblank(c)) continue;
        return (options & FOLD) ? tolower(c) : c;
    }
    return 0;
}

int compare_text(struct Field a, struct Field b, int options)
{
    int c1;
    int c2;

    for (;;) {
        c1 = next_char(&a, options);
        c2 = next_char(&b, options);
        if (c1 != c2) return (c1 > c2) - (c1 < c2);
        if (c1 == 0) return 0;
    }
}

double field_number(struct Field field)
{
    char text[MAXLEN];

    memcpy(text, field.start, field.length);
    text[field.length] = '\0';
    return atof(text);
}

int compare_fields(struct Field a, struct Field b, int options)
{
    int result;

    if (options & NUMERIC) {
        double v1 = field_number(a);
        double v2 = field_number(b);
        result = (v1 > v2) - (v1 < v2);
    } else {
        result = compare_text(a, b, options);
    }
    return (options & REVERSE) ? -result : result;
}

int compare_lines(const char *a, const char *b, const struct SortConfig *config)
{
    int i;
    int result;

    if (config->nkeys == 0) {
        struct Field f1 = {a, strlen(a)};
        struct Field f2 = {b, strlen(b)};
        return compare_fields(f1, f2, config->options);
    }

    for (i = 0; i < config->nkeys; ++i) {
        const struct SortKey *key = &config->keys[i];
        result = compare_fields(get_field(a, key), get_field(b, key), key->options);
        if (result != 0) return result;
    }

    return 0;
}

void quick_sort(char *v[], int left, int right,
                int (*comp)(const char *, const char *, const struct SortConfig *),
                const struct SortConfig *config)
{
    int i;
    int last;

    if (left >= right) return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; ++i) {
        if (comp(v[i], v[left], config) < 0) swap(v, ++last, i);
    }

    swap(v, left, last);
    quick_sort(v, left, last - 1, comp, config);
    quick_sort(v, last + 1, right, comp, config);
}

void swap(char *v[], int i, int j)
{
    char *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

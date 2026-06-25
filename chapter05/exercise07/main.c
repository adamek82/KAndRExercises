#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef MAXLINES
#define MAXLINES 5000
#endif

#ifndef MAXLEN
#define MAXLEN 100
#endif

#ifndef MAXSTOR
#define MAXSTOR 500000
#endif

#ifndef BENCH_LINES
#define BENCH_LINES 1000
#endif

#ifndef BENCH_REPEAT
#define BENCH_REPEAT 100
#endif

int get_line(char *line, int maxlen);
void reset_source(int lines);

int readlines_alloc(char *lineptr[], int maxlines);
int readlines_store(char *lineptr[], char *linestor, int maxlines, int storesize);

char *alloc(int n);
void alloc_reset(void);

clock_t benchmark_alloc(void);
clock_t benchmark_store(void);
int check_readlines(void);
int same_lines(char *left[], char *right[], int n);

volatile int result_sink;

/*
 * Exercise 5-7.
 *
 * Rewrite readlines so that it stores lines in an array supplied by main,
 * rather than in storage maintained by alloc.
 *
 * This program keeps both versions:
 *
 *     readlines_alloc()   K&R-style version using alloc()
 *     readlines_store()   version using storage supplied by main()
 *
 * The benchmark uses generated input lines so that both versions read the same
 * data without measuring terminal or file I/O.
 */

char *lineptr_alloc[MAXLINES];
char *lineptr_store[MAXLINES];

char allocbuf[MAXSTOR];
char *allocp = allocbuf;

char linestor[MAXSTOR];

int source_index;
int source_lines;

int main(void)
{
    int nlines;
    clock_t alloc_time;
    clock_t store_time;

    reset_source(3);
    nlines = readlines_store(lineptr_store, linestor, MAXLINES, MAXSTOR);

    printf("readlines_store sample count: %d\n", nlines);
    printf("first sample line: %s\n", lineptr_store[0]);
    printf("last sample line: %s\n", lineptr_store[nlines - 1]);

    if (!check_readlines()) {
        printf("readlines checks: failed\n");
        return 1;
    }

    printf("readlines checks: ok\n");

    alloc_time = benchmark_alloc();
    store_time = benchmark_store();

    printf("benchmark lines: %d\n", BENCH_LINES);
    printf("benchmark repeats: %d\n", BENCH_REPEAT);
    printf("alloc clocks: %ld, seconds: %.6f\n",
           (long) alloc_time, (double) alloc_time / CLOCKS_PER_SEC);
    printf("store clocks: %ld, seconds: %.6f\n",
           (long) store_time, (double) store_time / CLOCKS_PER_SEC);

    if (store_time > 0) {
        printf("store/alloc ratio: %.3f\n", (double) store_time / alloc_time);
    }

    return 0;
}

void reset_source(int lines)
{
    source_index = 0;
    source_lines = lines;
}

int get_line(char *line, int maxlen)
{
    int len;

    if (source_index >= source_lines) {
        return 0;
    }

    len = snprintf(line, maxlen,
                   "line %05d: quick brown fox jumps %03d\n",
                   source_index, source_index % 997);

    ++source_index;

    return len;
}

int readlines_alloc(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p;
    char line[MAXLEN];

    nlines = 0;

    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        }

        line[len - 1] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;
    }

    return nlines;
}

int readlines_store(char *lineptr[], char *linestor, int maxlines, int storesize)
{
    int len, nlines;
    char *p;
    char *linestop;
    char line[MAXLEN];

    p = linestor;
    linestop = linestor + storesize;
    nlines = 0;

    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p + len > linestop) {
            return -1;
        }

        line[len - 1] = '\0';
        strcpy(p, line);
        lineptr[nlines++] = p;
        p += len;
    }

    return nlines;
}

char *alloc(int n)
{
    if (allocbuf + MAXSTOR - allocp >= n) {
        allocp += n;
        return allocp - n;
    }

    return NULL;
}

void alloc_reset(void)
{
    allocp = allocbuf;
}

clock_t benchmark_alloc(void)
{
    int i, nlines;
    clock_t start;

    result_sink = 0;
    start = clock();

    for (i = 0; i < BENCH_REPEAT; ++i) {
        alloc_reset();
        reset_source(BENCH_LINES);

        nlines = readlines_alloc(lineptr_alloc, MAXLINES);

        if (nlines != BENCH_LINES) {
            result_sink = -1;
            return clock() - start;
        }

        result_sink += lineptr_alloc[0][0];
    }

    return clock() - start;
}

clock_t benchmark_store(void)
{
    int i, nlines;
    clock_t start;

    result_sink = 0;
    start = clock();

    for (i = 0; i < BENCH_REPEAT; ++i) {
        reset_source(BENCH_LINES);

        nlines = readlines_store(lineptr_store, linestor, MAXLINES, MAXSTOR);

        if (nlines != BENCH_LINES) {
            result_sink = -1;
            return clock() - start;
        }

        result_sink += lineptr_store[0][0];
    }

    return clock() - start;
}

int check_readlines(void)
{
    int nalloc, nstore;
    char *alloc_lines[10];
    char *store_lines[10];
    char small_store[20];

    alloc_reset();
    reset_source(5);
    nalloc = readlines_alloc(alloc_lines, 10);

    reset_source(5);
    nstore = readlines_store(store_lines, linestor, 10, MAXSTOR);

    if (nalloc != 5 || nstore != 5) {
        return 0;
    }

    if (!same_lines(alloc_lines, store_lines, 5)) {
        return 0;
    }

    alloc_reset();
    reset_source(3);
    if (readlines_alloc(alloc_lines, 2) != -1) {
        return 0;
    }

    reset_source(1);
    if (readlines_store(store_lines, small_store, 10, (int) sizeof small_store) != -1) {
        return 0;
    }

    return 1;
}

int same_lines(char *left[], char *right[], int n)
{
    while (n-- > 0) {
        if (strcmp(*left++, *right++)) {
            return 0;
        }
    }

    return 1;
}

#include <stdio.h>
#include <time.h>

#ifndef BENCH_SIZE
#define BENCH_SIZE 32768
#endif

#ifndef BENCH_REPEAT
#define BENCH_REPEAT 50000
#endif

int binsearch_original(int x, int v[], int n);
int binsearch_one_test(int x, int v[], int n);
int check_correctness(void);
void init_values(void);
clock_t benchmark(int (*search)(int, int[], int), int mode);

static int values[BENCH_SIZE];
volatile int result_sink;

/*
 * Exercise 3-1.
 *
 * The original binary search performs two comparisons with v[mid] inside the
 * loop: x < v[mid] and x > v[mid]. This version uses a lower_bound-style search
 * and performs only one such comparison inside the loop.
 *
 * The price is that equality is checked after the loop. This can be faster or
 * slower depending on data, compiler, optimization level and branch prediction.
 */
int main(void)
{
    clock_t original_found, one_test_found;
    clock_t original_missing, one_test_missing;

    init_values();

    if (!check_correctness()) {
        printf("correctness checks: failed\n");
        return 1;
    }

    printf("correctness checks: ok\n");

    original_found = benchmark(binsearch_original, 0);
    one_test_found = benchmark(binsearch_one_test, 0);

    original_missing = benchmark(binsearch_original, 1);
    one_test_missing = benchmark(binsearch_one_test, 1);

    printf("benchmark iterations: %d\n", BENCH_REPEAT);

    printf("original found clocks: %ld, seconds: %.6f\n",
           (long) original_found,
           (double) original_found / CLOCKS_PER_SEC);

    printf("one-test found clocks: %ld, seconds: %.6f\n",
           (long) one_test_found,
           (double) one_test_found / CLOCKS_PER_SEC);

    printf("original missing clocks: %ld, seconds: %.6f\n",
           (long) original_missing,
           (double) original_missing / CLOCKS_PER_SEC);

    printf("one-test missing clocks: %ld, seconds: %.6f\n",
           (long) one_test_missing,
           (double) one_test_missing / CLOCKS_PER_SEC);

    return 0;
}

/*
 * Original K&R-style binary search.
 */
int binsearch_original(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = low + (high - low) / 2;

        if (x < v[mid]) {
            high = mid - 1;
        } else if (x > v[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

/*
 * Binary search with only one comparison against v[mid] inside the loop.
 *
 * This finds the first position at which x could appear. If x is present,
 * low will point to it after the loop. If not, low will point to the first
 * greater element, or the search will fail the final equality check.
 */
int binsearch_one_test(int x, int v[], int n)
{
    int low, high, mid;

    if (n <= 0) {
        return -1;
    }

    low = 0;
    high = n - 1;

    while (low < high) {
        mid = low + (high - low) / 2;

        if (v[mid] < x) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    if (v[low] == x) {
        return low;
    }

    return -1;
}

int check_correctness(void)
{
    int sample[] = { 1, 3, 5, 7, 9, 11 };
    int n;

    n = (int) (sizeof sample / sizeof sample[0]);

    if (binsearch_one_test(1, sample, n) != 0) {
        return 0;
    }

    if (binsearch_one_test(7, sample, n) != 3) {
        return 0;
    }

    if (binsearch_one_test(11, sample, n) != 5) {
        return 0;
    }

    if (binsearch_one_test(0, sample, n) != -1) {
        return 0;
    }

    if (binsearch_one_test(6, sample, n) != -1) {
        return 0;
    }

    if (binsearch_one_test(12, sample, n) != -1) {
        return 0;
    }

    if (binsearch_one_test(5, sample, 0) != -1) {
        return 0;
    }

    return 1;
}

void init_values(void)
{
    int i;

    for (i = 0; i < BENCH_SIZE; ++i) {
        values[i] = i * 2;
    }
}

/*
 * mode == 0: search for existing even values.
 * mode == 1: search for missing odd values between existing elements.
 *
 * The accumulated result is stored in a volatile global so that an optimizing
 * compiler cannot freely discard the search calls as unused.
 */
clock_t benchmark(int (*search)(int, int[], int), int mode)
{
    int i, key, sum;
    clock_t start, elapsed;

    sum = 0;
    start = clock();

    for (i = 0; i < BENCH_REPEAT; ++i) {
        key = ((i * 37) % BENCH_SIZE) * 2;

        if (mode == 1) {
            key = key + 1;
        }

        sum = sum + search(key, values, BENCH_SIZE);
    }

    elapsed = clock() - start;
    result_sink = sum;

    return elapsed;
}

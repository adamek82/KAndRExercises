#include <float.h>
#include <limits.h>
#include <stdio.h>

/*
 * Exercise 2-1.
 *
 * Determine the ranges of char, short, int, and long variables, both signed
 * and unsigned, by printing values from standard headers and by direct
 * computation.
 *
 * This program intentionally stays close to the classic K&R exercise. It does
 * not cover later C types such as long long, fixed-width integer types, size_t,
 * or C23 _BitInt types.
 *
 * Floating-point ranges are printed from <float.h>. Computing them directly is
 * a harder optional part of the exercise and is not attempted here.
 */
int main(void)
{
    int mismatches;

    unsigned char uchar_max;
    signed char schar_min, schar_max;
    char plain_char_min, plain_char_max;

    unsigned short ushort_max;
    short short_min, short_max;

    unsigned int uint_max;
    int int_min, int_max;

    unsigned long ulong_max;
    long long_min, long_max;

    mismatches = 0;

    uchar_max = (unsigned char) ~0u;
    schar_max = (signed char) (uchar_max >> 1);
    schar_min = (signed char) (-schar_max - 1);

    if ((char) -1 < 0) {
        plain_char_min = (char) schar_min;
        plain_char_max = (char) schar_max;
    } else {
        plain_char_min = 0;
        plain_char_max = (char) uchar_max;
    }

    ushort_max = (unsigned short) ~0u;
    short_max = (short) (ushort_max >> 1);
    short_min = (short) (-short_max - 1);

    uint_max = ~0u;
    int_max = (int) (uint_max >> 1);
    int_min = -int_max - 1;

    ulong_max = ~0ul;
    long_max = (long) (ulong_max >> 1);
    long_min = -long_max - 1L;

    printf("Integer ranges from <limits.h> and direct computation:\n\n");

    printf("plain char header:   %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("plain char computed: %d to %d\n\n",
           (int) plain_char_min, (int) plain_char_max);

    printf("signed char header:   %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("signed char computed: %d to %d\n\n",
           (int) schar_min, (int) schar_max);

    printf("unsigned char header:   0 to %u\n", (unsigned int) UCHAR_MAX);
    printf("unsigned char computed: 0 to %u\n\n", (unsigned int) uchar_max);

    printf("short header:   %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("short computed: %d to %d\n\n", (int) short_min, (int) short_max);

    printf("unsigned short header:   0 to %u\n", (unsigned int) USHRT_MAX);
    printf("unsigned short computed: 0 to %u\n\n", (unsigned int) ushort_max);

    printf("int header:   %d to %d\n", INT_MIN, INT_MAX);
    printf("int computed: %d to %d\n\n", int_min, int_max);

    printf("unsigned int header:   0 to %u\n", UINT_MAX);
    printf("unsigned int computed: 0 to %u\n\n", uint_max);

    printf("long header:   %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("long computed: %ld to %ld\n\n", long_min, long_max);

    printf("unsigned long header:   0 to %lu\n", ULONG_MAX);
    printf("unsigned long computed: 0 to %lu\n\n", ulong_max);

    if ((int) plain_char_min != CHAR_MIN || (int) plain_char_max != CHAR_MAX) {
        ++mismatches;
    }

    if ((int) schar_min != SCHAR_MIN || (int) schar_max != SCHAR_MAX) {
        ++mismatches;
    }

    if ((unsigned int) uchar_max != UCHAR_MAX) {
        ++mismatches;
    }

    if ((int) short_min != SHRT_MIN || (int) short_max != SHRT_MAX) {
        ++mismatches;
    }

    if ((unsigned int) ushort_max != USHRT_MAX) {
        ++mismatches;
    }

    if (int_min != INT_MIN || int_max != INT_MAX) {
        ++mismatches;
    }

    if (uint_max != UINT_MAX) {
        ++mismatches;
    }

    if (long_min != LONG_MIN || long_max != LONG_MAX) {
        ++mismatches;
    }

    if (ulong_max != ULONG_MAX) {
        ++mismatches;
    }

    if (mismatches == 0) {
        printf("Integer range checks: ok\n\n");
    } else {
        printf("Integer range checks: failed\n\n");
    }

    printf("Floating-point ranges from <float.h>:\n\n");

    printf("float min positive:       %e\n", (double) FLT_MIN);
    printf("float max:                %e\n", (double) FLT_MAX);
    printf("float decimal digits:     %d\n\n", FLT_DIG);

    printf("double min positive:      %e\n", DBL_MIN);
    printf("double max:               %e\n", DBL_MAX);
    printf("double decimal digits:    %d\n\n", DBL_DIG);

    printf("long double min positive: %Le\n", LDBL_MIN);
    printf("long double max:          %Le\n", LDBL_MAX);
    printf("long double decimal digits: %d\n", LDBL_DIG);

    return mismatches == 0 ? 0 : 1;
}

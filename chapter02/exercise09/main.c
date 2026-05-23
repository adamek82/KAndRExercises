#include <stdio.h>

int bitcount(unsigned int x);
int bitcount_slow(unsigned int x);

/*
 * Exercise 2-9.
 *
 * In a two's complement number system, x &= (x - 1) deletes the rightmost
 * 1-bit in x. Explain why. Use this observation to write a faster version
 * of bitcount.
 */
int main(void)
{
    int failed;

    failed = 0;

    printf("bitcount(0x00000000) = %d\n", bitcount(0x00000000u));
    printf("bitcount(0x00000001) = %d\n", bitcount(0x00000001u));
    printf("bitcount(0x00000009) = %d\n", bitcount(0x00000009u));
    printf("bitcount(0x0000000f) = %d\n", bitcount(0x0000000fu));
    printf("bitcount(0xffffffff) = %d\n", bitcount(0xffffffffu));
    printf("bitcount(0x12345678) = %d\n", bitcount(0x12345678u));

    if (bitcount(0x00000000u) != bitcount_slow(0x00000000u)) {
        ++failed;
    }

    if (bitcount(0x00000001u) != bitcount_slow(0x00000001u)) {
        ++failed;
    }

    if (bitcount(0x00000009u) != bitcount_slow(0x00000009u)) {
        ++failed;
    }

    if (bitcount(0x0000000fu) != bitcount_slow(0x0000000fu)) {
        ++failed;
    }

    if (bitcount(0xffffffffu) != bitcount_slow(0xffffffffu)) {
        ++failed;
    }

    if (bitcount(0x12345678u) != bitcount_slow(0x12345678u)) {
        ++failed;
    }

    if (failed == 0) {
        printf("bitcount checks: ok\n");
    } else {
        printf("bitcount checks: failed\n");
    }

    return failed == 0 ? 0 : 1;
}

/*
 * Count 1-bits in x.
 *
 * Suppose the rightmost 1-bit of x is at position k. Then all bits to its
 * right are 0, so the value looks like this:
 *
 *     high bits  1  00...00
 *                ^  k lower zero bits
 *
 * Subtracting 1 leaves the high bits unchanged, changes that rightmost 1 to 0,
 * and changes all lower zero bits to 1:
 *
 *     high bits  0  11...11
 *
 * Therefore x & (x - 1) preserves all high bits, clears the rightmost 1-bit,
 * and keeps all lower bits at 0. Repeating this operation once per 1-bit counts
 * the set bits directly.
 */
int bitcount(unsigned int x)
{
    int count;

    count = 0;

    while (x != 0u) {
        x = x & (x - 1u);
        ++count;
    }

    return count;
}

/*
 * Straightforward reference version: test every bit by shifting x right.
 */
int bitcount_slow(unsigned int x)
{
    int count;

    count = 0;

    while (x != 0u) {
        if ((x & 1u) != 0u) {
            ++count;
        }

        x = x >> 1;
    }

    return count;
}

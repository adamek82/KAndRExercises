#include <limits.h>
#include <stdio.h>

unsigned int rightrot(unsigned int x, int n);
unsigned int rightrot_slow(unsigned int x, int n);
int unsigned_width(void);

/*
 * Exercise 2-8.
 *
 * Write a function rightrot(x, n) that returns x rotated to the right by
 * n bit positions.
 *
 * The rotation is performed over all bits of unsigned int. The number of bits
 * in unsigned int is computed from sizeof(unsigned int) and CHAR_BIT.
 */
int main(void)
{
    int failed;

    failed = 0;

    printf("unsigned int width: %d\n", unsigned_width());

    printf("rightrot(0x00000001, 1) = 0x%08x\n",
           rightrot(0x00000001u, 1));

    printf("rightrot(0x80000000, 1) = 0x%08x\n",
           rightrot(0x80000000u, 1));

    printf("rightrot(0x12345678, 4) = 0x%08x\n",
           rightrot(0x12345678u, 4));

    printf("rightrot(0x12345678, 8) = 0x%08x\n",
           rightrot(0x12345678u, 8));

    printf("rightrot(0x12345678, 32) = 0x%08x\n",
           rightrot(0x12345678u, 32));

    if (rightrot(0x00000001u, 1) != rightrot_slow(0x00000001u, 1)) {
        ++failed;
    }

    if (rightrot(0x80000000u, 1) != rightrot_slow(0x80000000u, 1)) {
        ++failed;
    }

    if (rightrot(0x12345678u, 4) != rightrot_slow(0x12345678u, 4)) {
        ++failed;
    }

    if (rightrot(0x12345678u, 8) != rightrot_slow(0x12345678u, 8)) {
        ++failed;
    }

    if (rightrot(0x12345678u, 32) != rightrot_slow(0x12345678u, 32)) {
        ++failed;
    }

    if (failed == 0) {
        printf("rightrot checks: ok\n");
    } else {
        printf("rightrot checks: failed\n");
    }

    return failed == 0 ? 0 : 1;
}

/*
 * Rotate x right by n bit positions.
 */
unsigned int rightrot(unsigned int x, int n)
{
    int width;

    width = unsigned_width();
    n = n % width;

    if (n == 0) {
        return x;
    }

    return (x >> n) | (x << (width - n));
}

/*
 * Slow reference implementation used only for checking the result.
 */
unsigned int rightrot_slow(unsigned int x, int n)
{
    int width;
    unsigned int right_bit;

    width = unsigned_width();
    n = n % width;

    while (n > 0) {
        right_bit = x & 1u;
        x = x >> 1;

        if (right_bit != 0u) {
            x = x | (1u << (width - 1));
        }

        --n;
    }

    return x;
}

int unsigned_width(void)
{
    return (int) (sizeof(unsigned int) * CHAR_BIT);
}

#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);

/*
 * Exercise 2-6.
 *
 * Write a function setbits(x, p, n, y) that returns x with the n bits that
 * begin at position p set to the rightmost n bits of y, leaving the other
 * bits unchanged.
 *
 * Bit positions are counted from the right, starting at 0.
 */
int main(void)
{
    printf("setbits(0xffff, 7, 4, 0x0) = 0x%04x\n",
           setbits(0xffffu, 7, 4, 0x0u));

    printf("setbits(0x0000, 7, 4, 0xf) = 0x%04x\n",
           setbits(0x0000u, 7, 4, 0xfu));

    printf("setbits(0xaaaa, 7, 4, 0x5) = 0x%04x\n",
           setbits(0xaaaau, 7, 4, 0x5u));

    printf("setbits(0x1234, 11, 4, 0xf) = 0x%04x\n",
           setbits(0x1234u, 11, 4, 0xfu));

    printf("setbits(0x1234, 3, 4, 0x0) = 0x%04x\n",
           setbits(0x1234u, 3, 4, 0x0u));

    return 0;
}

/*
 * Replace n bits in x, ending at bit position p, with the rightmost n bits of y.
 */
unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
    unsigned int mask;

    mask = ~(~0u << n) << (p + 1 - n);

    return (x & ~mask) | ((y << (p + 1 - n)) & mask);
}

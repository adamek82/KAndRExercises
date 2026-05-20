#include <stdio.h>

unsigned int invert(unsigned int x, int p, int n);

/*
 * Exercise 2-7.
 *
 * Write a function invert(x, p, n) that returns x with the n bits that begin
 * at position p inverted, leaving the other bits unchanged.
 *
 * Bit positions are counted from the right, starting at 0. The position p is
 * the leftmost, most significant bit of the selected n-bit field.
 */
int main(void)
{
    printf("invert(0x0000, 7, 4) = 0x%04x\n",
           invert(0x0000u, 7, 4));

    printf("invert(0xffff, 7, 4) = 0x%04x\n",
           invert(0xffffu, 7, 4));

    printf("invert(0xaaaa, 7, 4) = 0x%04x\n",
           invert(0xaaaau, 7, 4));

    printf("invert(0x1234, 11, 4) = 0x%04x\n",
           invert(0x1234u, 11, 4));

    printf("invert(0x1234, 3, 4) = 0x%04x\n",
           invert(0x1234u, 3, 4));

    return 0;
}

/*
 * Invert n bits in x, ending at bit position p.
 */
unsigned int invert(unsigned int x, int p, int n)
{
    unsigned int mask;

    mask = ~(~0u << n) << (p + 1 - n);

    return x ^ mask;
}

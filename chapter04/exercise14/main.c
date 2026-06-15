#include <stdio.h>
#include <string.h>

#define swap(t, x, y)       \
    do {                    \
        t swap_temp = (x);  \
        (x) = (y);          \
        (y) = swap_temp;    \
    } while (0)

int check_swap(void);

/*
 * Exercise 4-14.
 *
 * Define a macro swap(t, x, y) that interchanges two arguments of type t.
 *
 * The macro uses a block so that the temporary variable has block scope.
 * The do-while(0) wrapper makes the macro behave like a single statement.
 *
 * This macro is intended for simple assignable objects of the same type, such
 * as variables or array elements. As usual with macros, arguments with side
 * effects should be avoided.
 */
int main(void)
{
    int ix = 42;
    int iy = 69;
    double dx = 123.0;
    double dy = 321.0;
    char *px = "hello";
    char *py = "world";

    swap(int, ix, iy);
    swap(double, dx, dy);
    swap(char *, px, py);

    printf("ints: %d %d\n", ix, iy);
    printf("doubles: %.1f %.1f\n", dx, dy);
    printf("pointers: %s %s\n", px, py);

    if (!check_swap()) {
        printf("swap checks: failed\n");
        return 1;
    }

    printf("swap checks: ok\n");

    return 0;
}

int check_swap(void)
{
    int a = 1;
    int b = 2;
    double x = 1.5;
    double y = 2.5;
    char *left = "left";
    char *right = "right";
    int values[] = { 10, 20, 30 };

    swap(int, a, b);
    if (a != 2 || b != 1) {
        return 0;
    }

    swap(double, x, y);
    if (x != 2.5 || y != 1.5) {
        return 0;
    }

    swap(char *, left, right);
    if (strcmp(left, "right") != 0 || strcmp(right, "left") != 0) {
        return 0;
    }

    swap(int, values[0], values[2]);
    if (values[0] != 30 || values[1] != 20 || values[2] != 10) {
        return 0;
    }

    return 1;
}

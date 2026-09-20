#include <stdio.h>

int main()
{
    int a = 10, b = 20, c = 30;
    int *x, *y, *z;

    printf("Value of a Before: %d\n", a);
    printf("Value of b Before: %d\n", b);
    printf("Value of c Before: %d\n", c);

    x = &a;
    y = &b;
    z = &c;

    *x = 100;
    *y = 200;
    *z = 300;

    printf("Value of a After: %d\n", a);
    printf("Value of b After: %d\n", b);
    printf("Value of c After: %d\n", c);

    return 0;
}
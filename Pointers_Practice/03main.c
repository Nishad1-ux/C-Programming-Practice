#include <stdio.h>

int main()
{
    int a = 10, b = 20;
    int *p, *o;
    p = &a;
    o = &b;
    printf("Value of a: %d\n", *p);
    printf("Address of a: %p\n", p);
    printf("Value of b: %d\n", *o);
    printf("Address of b: %p\n", o);

    return 0;
}
#include <stdio.h>

int main()
{
    int n = 10;
    int *p;
    p = &n;
    printf("Before: %d\n", *p);
    *p = 50;
    printf("After: %d\n", *p);
    return 0;
}
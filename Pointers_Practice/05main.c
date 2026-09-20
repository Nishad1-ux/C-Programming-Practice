#include <stdio.h>

int swapTwoNumbers(int *a, int *b)
{
    int result;

    result = *a;
    *a = *b;
    *b = result;

    return result;
}

int main()
{
    int a = 10, b = 20;

    printf("Value of a & b Before: %d and %d\n", a, b);

    swapTwoNumbers(&a, &b);

    printf("Value of a & b After: %d and %d", a, b);

    return 0;
}
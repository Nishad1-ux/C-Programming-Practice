#include <stdio.h>

void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a = 1;
    int b = 2;

    printf("Before: a = %d, b = %d\n", a, b);

    swap(&a, &b);

    printf("After: a = %d, b = %d\n", a, b);

    return 0;
}
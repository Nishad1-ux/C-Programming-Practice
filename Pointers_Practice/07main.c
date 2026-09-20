#include <stdio.h>

int DoubleNumber(int *a)
{
    *a = *a * 2;
}

int main()
{
    int a;

    printf("Enter the Number: \n");
    scanf("%d", &a);

    printf("Original Number: %d\n", a);

    DoubleNumber(&a);
    
    printf("Doubled Number: %d\n", a);

    return 0;
}
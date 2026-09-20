#include <stdio.h>

int main()
{
    int i;
    long long fact = 1;

    printf("Printing 1! to 10!\n");

    for (i = 1; i <= 10; i++)
    {
        fact = fact * i;
        printf("%d! = %lld\n", i, fact);
    }

    return 0;
}
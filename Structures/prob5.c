#include <stdio.h>

typedef struct vector
{
    int i;
    int j;
} vec;

vec sumvector(vec v1, vec v2)
{
    vec v3 = {v1.i + v2.i, v1.j + v2.j};
    return v3;
}

int main()
{
    vec v1 = {1, 5};
    vec v2 = {8, 9};
    
    vec v3 = sumvector(v1, v2);
    
    printf("Sum Vector: %d i + %d j", v3.i, v3.j);
    
    return 0;
}
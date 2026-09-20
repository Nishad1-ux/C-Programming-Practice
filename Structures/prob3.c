#include <stdio.h>

struct complex
{
    int x;
    int y;
};

int main()
{
    struct complex a;

    printf("Enter the Real Value: ");
    scanf("%d", &a.x);

    printf("Enter the Imaginary Value: ");
    scanf("%d", &a.y);

    printf("Complex Number: %d + %di", a.x, a.y);

    return 0;
}
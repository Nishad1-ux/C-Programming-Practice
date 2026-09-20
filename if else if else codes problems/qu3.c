#include <stdio.h>
int main () {
    int a;
    int b;
    printf("Largest Number\n");
    printf("Enter the First Number: \n");
    scanf("%d", &a);
    printf("Enter the Second Number: \n");
    scanf("%d", &b);
    if (a > b) {
        printf("%d is bigger than %d", a,b);
    }
    else if (a < b) {
        printf("%d is bigger than %d", b,a);
    }
    else {
        printf("Both Numbers are equal!");
    }
    return 0;
}   
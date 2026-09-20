#include <stdio.h>
int main () {
    int a;
    printf("Leap year Checker!\n");
    printf("Enter the year: \n");
    scanf("%d", &a);
    if (a%400 == 0) {
        printf("%d is a LEAP YEAR!", a);
    }
    else if (a%100 == 0) {
        printf("%d is NOT a LEAP YEAR!", a);
    }
    else if (a%4 == 0) {
        printf("%d is a LEAP YEAR!", a);
    }
    else {
        printf("%d is NOT a LEAP YEAR!", a);
    }
    return 0;
}
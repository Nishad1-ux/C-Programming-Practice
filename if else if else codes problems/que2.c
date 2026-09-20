#include <stdio.h>
int main () {
    printf("Even or Odd?\n");
    int a;
    printf("Please Enter Your Number: ");
    scanf("%d", &a);
    if (a%2 == 0) {
        printf("This Number is an Even Number!");   
    }
    else {
        printf("This Number is a Odd Number!");
    }
    return 0;
}
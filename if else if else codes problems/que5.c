#include <stdio.h>
int main () {
    int a;
    printf("Voting Eligibility Test!\n");
    printf("Please Enter your Age: \n");
    scanf("%d", &a);
    if (a >= 18) {
        printf("You're Eligible to Vote!");
    }
    else if (a <= 0) {
        printf("Invalid Age!");
    }
    else {
        printf("You're not Eligible to Vote!");
    }
    return 0;
}
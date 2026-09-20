#include <stdio.h>
int main () {
    int a;
    printf("Electricity Bill\n");
    printf("Please enter the number of electricity units consumed: ");
    scanf("%d", &a);
    if (a <= 100) {
        printf("Your bill is: Rs.%d", a*5);
    }
    else if (a > 100 && a <= 200) {
        printf("Your bill is: Rs.%d", a*7);
    }
    else if (a > 200) {
        printf("Your bill is: Rs.%d", a*10);
    }
    return 0;
}
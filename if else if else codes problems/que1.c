#include <stdio.h>
int main() {
    int a;
    printf("Enter Number: ");
    scanf("%d", &a);
    if (a > 0) {
        printf("The Number is Positive!\n");
    }
    else if (a < 0) {
        printf("The Number is Negative!");
    }
    else {
        printf("The Number is Zero!");
    }

    return 0;
}

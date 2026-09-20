#include <stdio.h>
int main () {
    int a;
    printf("Grading System\n");
    printf("Enter your Marks: \n");
    scanf("%d", &a);
    if (a == 100) {
        printf("You've got A Grade!, You have scored Full Marks! CHAMP!");
    }
    else if (a >= 90) {
        printf("You've got A Grade!");
    }   
    else if (a >= 80 && a < 90) {
        printf("You've got B Grade!");
    }
    else if (a >= 70 && a < 80) {
        printf("You've got C Grade!");
    }
    else if (a >= 60 && a < 70) {
        printf("You've got D Grade!");
    }
    else {
        printf("Sorry, You've Failed and got E Grade!");
    }
    return 0;
}

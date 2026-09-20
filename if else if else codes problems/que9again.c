#include <stdio.h>

int main()
{
    int a, b, choice;
    printf("===Simple Calculator===\n");
    printf("Enter First Number: \n");
    scanf("%d", &a);
    printf("Enter Second Number: \n");
    scanf("%d", &b);

    printf("Choose Operation\n");
    printf("1. Addition\t(+)\n");
    printf("2. Subtraction\t(-)\n");
    printf("3. Product\t(*)\n");
    printf("4. Division\t(/)\n");
    
    printf("Enter your choice: \n");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("The Addition of %d and %d is: %d", a, b, a + b);
    }
    else if (choice == 2) {
        printf("The Difference between %d and %d is: %d", a, b, a-b);
    }
    else if (choice == 3) {
        printf("The Product of %d and %d is: %d", a, b, a*b);
    }
    else if (choice == 4) {
        if (b != 0)
        printf("The Quotient of %d and %d is: %d", a, b, a / b);
        else
        printf("Error! Division by zero is not allowed.");
    }
    else {
        printf("Invalid Choice!");
    }
    return 0;
}
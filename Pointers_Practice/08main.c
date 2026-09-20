#include <stdio.h>

int add(int *a, int *b)
{
    int result;
    result = (*a) + (*b);
    return result;
}
int subtract(int *a, int *b)
{
    int result;
    result = (*a) - (*b);
    return result;
}
int multiply(int *a, int *b)
{
    int result;
    result = (*a) * (*b);
    return result;
}
float divide(int *a, int *b)
{
    return (float)(*a) / (*b); 
}
int getRemainder(int *a, int *b)
{
    int result;
    result = (*a) % (*b);
    return result;
}
int power(int *a, int *b)
{
    int i, result = 1;
    for (i = 1; i <= *b; i++)
    {
        result = (result) * (*a);
    }

    return result;
}

int main()
{
    int a, b, choice;

    printf("=======Working Calculator using Pointers=======\n");

    while (1)
    {

        printf("Enter First Number: ");
        scanf("%d", &a);
        printf("Enter Second Number: ");
        scanf("%d", &b);

        printf("1.\tAdd\t(+)\n");
        printf("2.\tSubtract\t(-)\n");
        printf("3.\tMultiply\t(*)\n");
        printf("4.\tDivide\t(/)\n");
        printf("5.\tRemainder\t(%%)\n");
        printf("6.\tPower\t(^)\n");
        printf("0.\tExit\t\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Result: %d\n", add(&a, &b));
        }
        else if (choice == 2)
        {
            printf("Result: %d\n", subtract(&a, &b));
        }
        else if (choice == 3)
        {
            printf("Result: %d\n", multiply(&a, &b));
        }
        else if (choice == 4)
        {
            if (b != 0)
            {
                printf("Result: %.2f\n", divide(&a, &b));
            }
            else
            {
                printf("Cannot divide by Zero!\n");
                break;
            }
        }
        else if (choice == 5)
        {
            if (b != 0)
            {
                printf("Result: %d\n", getRemainder(&a, &b));
            }
            else
            {
                printf("Cannot get Remainder when Divisor is  Zero!\n");
                break;
            }
        }
        else if (choice == 6)
        {
            printf("Result: %d\n", power(&a, &b));
        }
        else if (choice == 0)
        {
            break;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}
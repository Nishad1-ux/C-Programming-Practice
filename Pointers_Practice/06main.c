#include <stdio.h>

int addTwoNumbers(int *a, int *b)
{
    int result;
    result = (*a) + (*b);
    return result;
}

int main()
{
    while (1)
    {
        int a, b, choice;

        printf("Enter First Number: \n");
        scanf("%d", &a);

        printf("Enter Second Number: \n");
        scanf("%d", &b);

        printf("%d + %d = %d\n", a, b, addTwoNumbers(&a, &b));

        printf("Enter 0 to Exit\n");
        printf("Enter 1 to Continue\n");

        printf("Enter your choice: \n");
        scanf("%d", &choice);

        if (choice == 1)
        {
            continue;
        }
        else
        {
            break;
        }
    }

    return 0;
}
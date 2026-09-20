#include <stdio.h>

int main()
{
    printf("Printing the Second Largest Number in Array!\n");

    int arr[5];

    printf("Enter First Number in Array: ");
    scanf("%d", &arr[0]);

    printf("Enter Second Number in Array: ");
    scanf("%d", &arr[1]);

    printf("Enter Third Number in Array: ");
    scanf("%d", &arr[2]);

    printf("Enter Fourth Number in Array: ");
    scanf("%d", &arr[3]);

    printf("Enter Fifth Number in Array: ");
    scanf("%d", &arr[4]);

    int largest = arr[0];
    int secondLargest = arr[0];

    for (int i = 1; i < 5; i++)
    {
        if (arr[i] > largest)
        {
            secondLargest = largest;
            largest = arr[i];
        }
        else if (arr[i] > secondLargest && arr[i] != largest)
        {
            secondLargest = arr[i];
        }
    }

    printf("The Second Largest Number is: %d\n", secondLargest);

    return 0;
}
#include <stdio.h>

int main()
{
    int map[6];

    printf("Enter First Number in Array: \n");
    scanf("%d", &map[0]);
    printf("Enter Second Number in Array: \n");
    scanf("%d", &map[1]);
    printf("Enter Third Number in Array: \n");
    scanf("%d", &map[2]);
    printf("Enter Fourth Number in Array: \n");
    scanf("%d", &map[3]);
    printf("Enter Fifth Number in Array: \n");
    scanf("%d", &map[4]);

    printf("The Value of %d + %d is: %d", map[1], map[2], map[1] + map[2]);

    return 0;
}
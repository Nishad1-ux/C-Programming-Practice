#include <stdio.h>
#include <string.h>

void reverse(char str[])
{
    int length = 0;

    while (str[length] != '\0')
    {
        length++;
    }

    int start = 0;
    int end = length - 1;

    while (start < end)
    {
        char temp;
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}

int main()
{
    char mystring[100];

    printf("Enter Your String: ");
    fgets(mystring, sizeof(mystring), stdin);

    printf("Original String: %s", mystring);

    reverse(mystring);

    printf("Reversed String: %s", mystring);

    return 0;
}
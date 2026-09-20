#include <stdio.h>

int mystrlen(char str[])
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
    }
    return i;
}

int main()
{
    char mystring[100];

    printf("Enter your String: ");
    fgets(mystring, sizeof(mystring), stdin);

    int len = mystrlen(mystring);

    if (len > 0 && mystring[len - 1] == '\n')
    {
        len--;
    }

    printf("Length of String: %d\n", len);
    return 0;
}
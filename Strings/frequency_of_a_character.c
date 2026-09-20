#include <stdio.h>
#include <string.h>

int main()
{
    char mystring[100] = "";

    printf("String Input: ");
    fgets(mystring, sizeof(mystring), stdin);

    char char_search;

    printf("Character: ");
    scanf(" %c", &char_search);

    int counter = 0;

    for (int i = 0; mystring[i] != '\0'; i++)
    {
        if (mystring[i] == char_search)
        {
            counter++;
        }
    }

    printf("Frequency: %d", counter);

    return 0;
}
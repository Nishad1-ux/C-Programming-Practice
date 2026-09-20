#include <stdio.h>
#include <string.h>

int stringLength(char str[])
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
    }
    return i;
}

int main()
{
    char mystring[100] = "";

    printf("Input: ");
    fgets(mystring, sizeof(mystring), stdin);

    int len = stringLength(mystring);
    printf("Length of String: %d\n", len);

    printf("\n");

    int vowel_count = 0;
    int consonant_count = 0;
    int digit_count = 0;
    int space_count = 0;

    for (int i = 0; mystring[i] != '\0'; i++)
    {
        if (mystring[i] == 'A' || mystring[i] == 'E' || mystring[i] == 'I' || mystring[i] == 'O' || mystring[i] == 'U' || mystring[i] == 'a' || mystring[i] == 'e' || mystring[i] == 'i' || mystring[i] == 'o' || mystring[i] == 'u')
        {
            vowel_count++;
        }
    }

    printf("Vowel Count: %d\n", vowel_count);

    for (int i = 0; mystring[i] != '\0'; i++)
    {
        if (((mystring[i] >= 'A' && mystring[i] <= 'Z') || (mystring[i] >= 'a' && mystring[i] <= 'z')) && mystring[i] != 'A' && mystring[i] != 'E' && mystring[i] != 'I' && mystring[i] != 'O' && mystring[i] != 'U' &&
            mystring[i] != 'a' && mystring[i] != 'e' && mystring[i] != 'i' && mystring[i] != 'o' && mystring[i] != 'u')

        {
            consonant_count++;
        }
    }

    printf("Consonant Count: %d\n", consonant_count);

    for (int i = 0; mystring[i] != '\0'; i++)
    {
        if (mystring[i] == ' ')
        {
            space_count++;
        }
    }

    printf("Space Count: %d\n", space_count);

    for (int i = 0; i < mystring[i] != '\0'; i++)
    {
        if (mystring[i] >= '0' && mystring[i] <= '9')
        {
            digit_count++;
        }

    }

    printf("Digit Count: %d\n", digit_count);

    return 0;
}
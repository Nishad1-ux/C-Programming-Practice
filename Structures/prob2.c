#include <stdio.h>
#include <string.h>

struct book
{
    char book_name[100];
    char author_name[100];
    int book_price;
};

int main()
{
    struct book a;
    strcpy(a.book_name, "Fairy Tales in Wonderland");
    strcpy(a.author_name, "D. Anna");
    a.book_price = 300;

    printf("Book Name: %s\n", a.book_name);
    printf("Author: %s\n", a.author_name);
    printf("Price: %d\n", a.book_price);
    return 0;
}
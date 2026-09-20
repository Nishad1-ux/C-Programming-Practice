#include <stdio.h>

struct students
{
    char name[100];
    int id;
    float marks;
};

int main()
{
    struct students a[6];

    for (int i = 0; i < 6; i++)
    {
        printf("Enter Student's Name: ");
        scanf("%s", a[i].name);

        printf("Enter Student's ID: ");
        scanf("%d", &a[i].id);

        printf("Enter Student's Marks: ");
        scanf("%f", &a[i].marks);

        printf("\n");
    }

    int highest = 0;

    for (int i = 1; i < 6; i++)
    {
        if (a[i].marks > a[highest].marks)
        {
            highest = i;
        }
    }

    printf("Student with Highest Marks: %s\n", a[highest].name);

    return 0;
}
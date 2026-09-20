#include <stdio.h>

int main()
{
	int nis[6];
	int val = 0, i;

	for (int i = 0; i < 6; i++)
	{
		printf("Enter the Number %d: \n", i + 1);
		scanf("%d", &nis[i]);
	}
	for (int i = 0; i < 6; i++)
	{
		printf("Array's Value %d: %d\n", i + 1 ,nis[i]);
	}

	for (int i = 0; i < 6; i++)
	{
		val = val + nis[i];
	}
	printf("Sum of all Values: %d\n", val);

	printf("Average of all Numbers: %d\n");
	

	return 0;
}


#include <stdio.h>

void printStrategy(int n)
{
    if (n == 2)
    {
        printf("1 1\n");
        return;
    }

    // Forward sweep
    for (int i = 2; i <= n - 1; i++)
        printf("%d ", i);

    // Reverse sweep
    for (int i = n - 1; i >= 2; i--)
        printf("%d ", i);

    printf("\n");
}

int main()
{
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1)
    {
        printf("n must be greater than 1.\n");
        return 0;
    }

    printf("\nGuaranteed shooting sequence:\n");

    printStrategy(n);

    if (n == 2)
        printf("Number of shots = 2\n");
    else
        printf("Number of shots = %d\n",
               2 * (n - 2));

    return 0;
}
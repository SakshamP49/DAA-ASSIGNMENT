#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;

    printf("Enter number of children: ");
    scanf("%d", &n);

    int *rating = malloc(n * sizeof(int));
    int *candy = malloc(n * sizeof(int));

    if (rating == NULL || candy == NULL)
        return 1;

    printf("Enter ratings:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &rating[i]);

    for (int i = 0; i < n; i++)
        candy[i] = 1;

    for (int i = 1; i < n; i++)
    {
        if (rating[i] > rating[i - 1])
        {
            candy[i] = candy[i - 1] + 1;
        }
    }

    for (int i = n - 2; i >= 0; i--)
    {
        if (rating[i] > rating[i + 1])
        {
            if (candy[i] < candy[i + 1] + 1)
                candy[i] = candy[i + 1] + 1;
        }
    }

    long long total = 0;

    printf("\nCandies:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", candy[i]);
        total += candy[i];
    }

    printf("\n\nMinimum total candies = %lld\n",
           total);

    free(rating);
    free(candy);

    return 0;
}
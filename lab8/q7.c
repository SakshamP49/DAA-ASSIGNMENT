#include <stdio.h>
#include <stdlib.h>

long long rodCutting(int price[], int n, int cut[])
{
    long long *dp =
        malloc((n + 1) * sizeof(long long));

    if (dp == NULL)
        return -1;

    dp[0] = 0;

    cut[0] = 0;

    for (int length = 1; length <= n; length++)
    {
        dp[length] = price[length - 1];
        cut[length] = length;

        for (int firstPiece = 1;
             firstPiece < length;
             firstPiece++)
        {
            long long current =
                price[firstPiece - 1] +
                dp[length - firstPiece];

            if (current > dp[length])
            {
                dp[length] = current;
                cut[length] = firstPiece;
            }
        }
    }

    long long answer = dp[n];

    free(dp);

    return answer;
}

int main()
{
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    int *price = malloc(n * sizeof(int));
    int *cut = malloc((n + 1) * sizeof(int));

    if (price == NULL || cut == NULL)
        return 1;

    printf("Enter prices for lengths 1 to %d:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &price[i]);

    long long maximumRevenue =
        rodCutting(price, n, cut);

    printf("\nMaximum revenue = %lld\n",
           maximumRevenue);

    printf("Optimal pieces = ");

    int remaining = n;

    while (remaining > 0)
    {
        printf("%d ", cut[remaining]);

        remaining -= cut[remaining];
    }

    printf("\n");

    free(price);
    free(cut);

    return 0;
}
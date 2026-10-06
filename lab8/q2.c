#include <stdio.h>
#include <stdlib.h>

long long countWays(int coins[], int n, int V)
{
    long long *dp = malloc((V + 1) * sizeof(long long));

    if (dp == NULL)
        return -1;

    for (int i = 0; i <= V; i++)
        dp[i] = 0;

    dp[0] = 1;

    for (int i = 0; i < n; i++)
    {
        for (int amount = coins[i]; amount <= V; amount++)
        {
            dp[amount] =
                dp[amount] + dp[amount - coins[i]];
        }
    }

    long long answer = dp[V];

    free(dp);

    return answer;
}

int main()
{
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int *coins = malloc(n * sizeof(int));

    printf("Enter coin denominations:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    long long answer = countWays(coins, n, V);

    printf("Total number of ways = %lld\n", answer);

    free(coins);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int minCoins(int coins[], int n, int V)
{
    int *dp = malloc((V + 1) * sizeof(int));

    if (dp == NULL)
        return -1;

    dp[0] = 0;

    for (int i = 1; i <= V; i++)
        dp[i] = V + 1;

    for (int amount = 1; amount <= V; amount++)
    {
        for (int i = 0; i < n; i++)
        {
            if (coins[i] <= amount &&
                dp[amount - coins[i]] != V + 1)
            {
                int current = dp[amount - coins[i]] + 1;

                if (current < dp[amount])
                    dp[amount] = current;
            }
        }
    }

    int answer;

    if (dp[V] == V + 1)
        answer = -1;
    else
        answer = dp[V];

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

    int answer = minCoins(coins, n, V);

    printf("Minimum number of coins = %d\n", answer);

    free(coins);

    return 0;
}
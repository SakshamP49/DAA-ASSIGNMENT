#include <stdio.h>
#include <limits.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int eggDrop(int eggs, int floors)
{
    int dp[eggs + 1][floors + 1];

    // 0 floors require 0 trials
    for (int e = 1; e <= eggs; e++)
        dp[e][0] = 0;

    // 1 floor requires 1 trial
    for (int e = 1; e <= eggs; e++)
        dp[e][1] = 1;

    // With one egg, we have to try every floor
    for (int f = 0; f <= floors; f++)
        dp[1][f] = f;

    // Fill DP table
    for (int e = 2; e <= eggs; e++)
    {
        for (int f = 2; f <= floors; f++)
        {
            dp[e][f] = INT_MAX;

            for (int x = 1; x <= f; x++)
            {
                int trials;

                trials = 1 + max(
                    dp[e - 1][x - 1],
                    dp[e][f - x]
                );

                if (trials < dp[e][f])
                    dp[e][f] = trials;
            }
        }
    }

    return dp[eggs][floors];
}

int main()
{
    int eggs, floors;

    printf("Enter number of eggs: ");
    scanf("%d", &eggs);

    printf("Enter number of floors: ");
    scanf("%d", &floors);

    printf("Minimum number of drops = %d\n",
           eggDrop(eggs, floors));

    return 0;
}
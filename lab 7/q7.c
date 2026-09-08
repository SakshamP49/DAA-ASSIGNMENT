#include <stdio.h>
#include <limits.h>

int dp[100][100];
int split[100][100];

void printOptimalOrder(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");

    printOptimalOrder(i, split[i][j]);

    printf(" x ");

    printOptimalOrder(split[i][j] + 1, j);

    printf(")");
}

int matrixChain(int p[], int n)
{
    /*
       n = number of matrices
       p has n+1 dimensions
    */

    for (int i = 1; i <= n; i++)
        dp[i][i] = 0;

    // length = number of matrices in the chain
    for (int length = 2; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            dp[i][j] = INT_MAX;

            for (int k = i; k < j; k++)
            {
                int cost =
                    dp[i][k] +
                    dp[k + 1][j] +
                    p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }

    return dp[1][n];
}

int main()
{
    int n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[n + 1];

    printf("Enter %d dimensions:\n", n + 1);

    for (int i = 0; i <= n; i++)
        scanf("%d", &p[i]);

    int minimumCost = matrixChain(p, n);

    printf("\nMinimum scalar multiplications = %d\n",
           minimumCost);

    printf("Optimal parenthesization = ");

    printOptimalOrder(1, n);

    printf("\n");

    return 0;
}
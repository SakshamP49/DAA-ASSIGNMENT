#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printLCS(char X[], char Y[])
{
    int m = strlen(X);
    int n = strlen(Y);

    int *dp = malloc((m + 1) * (n + 1) * sizeof(int));

    if (dp == NULL)
        return;

    #define DP(i, j) dp[(i) * (n + 1) + (j)]

    for (int i = 0; i <= m; i++)
        DP(i, 0) = 0;

    for (int j = 0; j <= n; j++)
        DP(0, j) = 0;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                DP(i, j) = DP(i - 1, j - 1) + 1;
            }
            else
            {
                if (DP(i - 1, j) > DP(i, j - 1))
                    DP(i, j) = DP(i - 1, j);
                else
                    DP(i, j) = DP(i, j - 1);
            }
        }
    }

    int lcsLength = DP(m, n);

    char *lcs = malloc((lcsLength + 1) * sizeof(char));

    if (lcs == NULL)
    {
        free(dp);
        return;
    }

    lcs[lcsLength] = '\0';

    int i = m;
    int j = n;
    int index = lcsLength - 1;

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index] = X[i - 1];
            index--;
            i--;
            j--;
        }
        else if (DP(i - 1, j) >= DP(i, j - 1))
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("LCS length = %d\n", lcsLength);
    printf("LCS = %s\n", lcs);

    free(lcs);
    free(dp);
}

int main()
{
    char X[1000];
    char Y[1000];

    printf("Enter first sequence: ");
    scanf("%999s", X);

    printf("Enter second sequence: ");
    scanf("%999s", Y);

    printLCS(X, Y);

    return 0;
}
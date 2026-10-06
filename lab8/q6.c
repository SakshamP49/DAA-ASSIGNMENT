#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char type;
    char from;
    char to;
} Operation;

void printEditOperations(char A[], char B[])
{
    int m = strlen(A);
    int n = strlen(B);

    int *dp = malloc((m + 1) * (n + 1) * sizeof(int));

    if (dp == NULL)
        return;

    #define DP(i, j) dp[(i) * (n + 1) + (j)]

    for (int i = 0; i <= m; i++)
        DP(i, 0) = i;

    for (int j = 0; j <= n; j++)
        DP(0, j) = j;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                DP(i, j) = DP(i - 1, j - 1);
            }
            else
            {
                int insertCost = DP(i, j - 1);
                int deleteCost = DP(i - 1, j);
                int replaceCost = DP(i - 1, j - 1);

                int minimum = insertCost;

                if (deleteCost < minimum)
                    minimum = deleteCost;

                if (replaceCost < minimum)
                    minimum = replaceCost;

                DP(i, j) = minimum + 1;
            }
        }
    }

    printf("Edit distance = %d\n", DP(m, n));

    Operation *operations =
        malloc((m + n + 1) * sizeof(Operation));

    int count = 0;

    int i = m;
    int j = n;

    while (i > 0 || j > 0)
    {
        if (i > 0 && j > 0 &&
            A[i - 1] == B[j - 1])
        {
            i--;
            j--;
        }
        else if (i > 0 && j > 0 &&
                 DP(i, j) == DP(i - 1, j - 1) + 1)
        {
            operations[count].type = 'S';
            operations[count].from = A[i - 1];
            operations[count].to = B[j - 1];

            count++;

            i--;
            j--;
        }
        else if (i > 0 &&
                 DP(i, j) == DP(i - 1, j) + 1)
        {
            operations[count].type = 'D';
            operations[count].from = A[i - 1];
            operations[count].to = '-';

            count++;

            i--;
        }
        else
        {
            operations[count].type = 'I';
            operations[count].from = '-';
            operations[count].to = B[j - 1];

            count++;

            j--;
        }
    }

    printf("\nTraceback:\n");

    for (int k = count - 1; k >= 0; k--)
    {
        if (operations[k].type == 'S')
        {
            printf("Substitute %c -> %c\n",
                   operations[k].from,
                   operations[k].to);
        }
        else if (operations[k].type == 'D')
        {
            printf("Delete %c\n",
                   operations[k].from);
        }
        else
        {
            printf("Insert %c\n",
                   operations[k].to);
        }
    }

    free(operations);
    free(dp);
}

int main()
{
    char A[1000];
    char B[1000];

    printf("Enter first string: ");
    scanf("%999s", A);

    printf("Enter second string: ");
    scanf("%999s", B);

    printEditOperations(A, B);

    return 0;
}
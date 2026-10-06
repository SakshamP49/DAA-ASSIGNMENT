#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAX 100

double e[MAX + 2][MAX + 1];
double w[MAX + 2][MAX + 1];
int root[MAX + 1][MAX + 1];

void optimalBST(double p[], double q[], int n)
{
    /*
        p[1..n] = probabilities of successful searches
        q[0..n] = probabilities of unsuccessful searches

        e[i][j] = minimum expected search cost
                  for keys Ki ... Kj

        w[i][j] = total probability of keys Ki...Kj
                  and dummy keys Di-1...Dj

        root[i][j] = root of optimal subtree Ki...Kj
    */

    for (int i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int length = 1; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            e[i][j] = DBL_MAX;

            w[i][j] =
                w[i][j - 1] +
                p[j] +
                q[j];

            for (int r = i; r <= j; r++)
            {
                double cost =
                    e[i][r - 1] +
                    e[r + 1][j] +
                    w[i][j];

                if (cost < e[i][j])
                {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }
}

void printTree(int i, int j, int parent, char side[])
{
    if (i > j)
    {
        printf("d%d is the %s child of K%d\n",
               j, side, parent);
        return;
    }

    int r = root[i][j];

    if (parent == 0)
    {
        printf("K%d is the root\n", r);
    }
    else
    {
        printf("K%d is the %s child of K%d\n",
               r, side, parent);
    }

    printTree(i, r - 1, r, "left");
    printTree(r + 1, j, r, "right");
}

int main()
{
    int n;

    double p[MAX + 1];
    double q[MAX + 1];

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter probabilities p1 to p%d:\n", n);

    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);

    printf("Enter probabilities q0 to q%d:\n", n);

    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    optimalBST(p, q, n);

    printf("\nMinimum expected search cost = %.6lf\n",
           e[1][n]);

    printf("\nOptimal Binary Search Tree:\n");

    printTree(1, n, 0, "");

    return 0;
}
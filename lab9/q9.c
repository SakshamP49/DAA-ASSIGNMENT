#include <stdio.h>
#include <stdlib.h>

#define MAX 100

#define TERMINAL 0
#define INTERNAL 1
#define NONE 2

long long weight[MAX];
int state[MAX];
int root[MAX];

int leftChild[2 * MAX];
int rightChild[2 * MAX];

int nodeCount;

void buildHuTucker(long long w[], int n)
{
    for (int i = 0; i < n; i++)
    {
        weight[i] = w[i];
        state[i] = TERMINAL;
        root[i] = i;
    }

    nodeCount = n;

    for (int step = 0; step < n - 1; step++)
    {
        long long bestSum =
            9223372036854775807LL;

        int bestI = -1;
        int bestJ = -1;

        for (int i = 0; i < n; i++)
        {
            if (state[i] == NONE)
                continue;

            for (int j = i + 1; j < n; j++)
            {
                if (state[j] == NONE)
                    continue;

                int valid = 1;

                for (int k = i + 1; k < j; k++)
                {
                    if (state[k] == TERMINAL)
                    {
                        valid = 0;
                        break;
                    }
                }

                if (!valid)
                    continue;

                long long sum =
                    weight[i] + weight[j];

                if (sum < bestSum)
                {
                    bestSum = sum;
                    bestI = i;
                    bestJ = j;
                }
                else if (sum == bestSum)
                {
                    if (bestI == -1 ||
                        i < bestI ||
                        (i == bestI && j < bestJ))
                    {
                        bestI = i;
                        bestJ = j;
                    }
                }
            }
        }

        if (bestI == -1)
            return;

        int newNode = nodeCount++;

        leftChild[newNode] =
            root[bestI];

        rightChild[newNode] =
            root[bestJ];

        root[bestI] = newNode;

        weight[bestI] += weight[bestJ];

        state[bestI] = INTERNAL;
        state[bestJ] = NONE;
    }
}

void findDepths(int node,
                int depth,
                int n,
                int depths[])
{
    if (node < n)
    {
        depths[node] = depth;
        return;
    }

    findDepths(leftChild[node],
               depth + 1,
               n,
               depths);

    findDepths(rightChild[node],
               depth + 1,
               n,
               depths);
}

void printTree(int node, int n)
{
    if (node < n)
    {
        printf("K%d", node + 1);
        return;
    }

    printf("(");

    printTree(leftChild[node], n);

    printf(" , ");

    printTree(rightChild[node], n);

    printf(")");
}

int main()
{
    int n;

    printf("Enter number of ordered keys: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of keys.\n");
        return 0;
    }

    long long w[n];

    printf("Enter weights:\n");

    for (int i = 0; i < n; i++)
        scanf("%lld", &w[i]);

    buildHuTucker(w, n);

    int depths[MAX];

    for (int i = 0; i < n; i++)
        depths[i] = 0;

    findDepths(root[0], 0, n, depths);

    long long minimumCost = 0;

    for (int i = 0; i < n; i++)
    {
        minimumCost +=
            w[i] * depths[i];
    }

    printf("\nMinimum weighted path length = %lld\n",
           minimumCost);

    printf("\nOptimal alphabetic tree:\n");
    printTree(root[0], n);

    printf("\n\nDepths:\n");

    for (int i = 0; i < n; i++)
    {
        printf("K%d -> depth %d\n",
               i + 1,
               depths[i]);
    }

    return 0;
}
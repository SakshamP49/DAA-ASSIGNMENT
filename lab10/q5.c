#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int parent;
    int rank;
} DSU;

int find(DSU dsu[], int x)
{
    if (dsu[x].parent == x)
        return x;

    dsu[x].parent = find(dsu, dsu[x].parent);
    return dsu[x].parent;
}

void unite(DSU dsu[], int a, int b)
{
    int ra = find(dsu, a);
    int rb = find(dsu, b);

    if (ra == rb)
        return;

    if (dsu[ra].rank < dsu[rb].rank)
    {
        dsu[ra].parent = rb;
    }
    else if (dsu[ra].rank > dsu[rb].rank)
    {
        dsu[rb].parent = ra;
    }
    else
    {
        dsu[rb].parent = ra;
        dsu[ra].rank++;
    }
}

int compareInt(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n, m;

    printf("Enter n: ");
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));

    printf("Enter permutation A:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    printf("Enter number of allowed swaps: ");
    scanf("%d", &m);

    DSU *dsu = malloc(n * sizeof(DSU));

    for (int i = 0; i < n; i++)
    {
        dsu[i].parent = i;
        dsu[i].rank = 0;
    }

    printf("Enter allowed swap edges:\n");

    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        u--;
        v--;

        if (u >= 0 && u < n &&
            v >= 0 && v < n)
        {
            unite(dsu, u, v);
        }
    }

    int **indices = malloc(n * sizeof(int *));
    int **values = malloc(n * sizeof(int *));
    int *count = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++)
    {
        indices[i] = malloc(n * sizeof(int));
        values[i] = malloc(n * sizeof(int));
    }

    // Collect indices and values for each component
    for (int i = 0; i < n; i++)
    {
        int root = find(dsu, i);

        indices[root][count[root]] = i;
        values[root][count[root]] = A[i];

        count[root]++;
    }

    // Sort indices and values within each component
    for (int i = 0; i < n; i++)
    {
        if (count[i] == 0)
            continue;

        qsort(indices[i],
              count[i],
              sizeof(int),
              compareInt);

        qsort(values[i],
              count[i],
              sizeof(int),
              compareInt);
    }

    int *answer = malloc(n * sizeof(int));

    // Assign smallest values to smallest indices
    for (int root = 0; root < n; root++)
    {
        for (int j = 0; j < count[root]; j++)
        {
            answer[indices[root][j]] =
                values[root][j];
        }
    }

    printf("\nLexicographically smallest permutation:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", answer[i]);

    printf("\n");

    for (int i = 0; i < n; i++)
    {
        free(indices[i]);
        free(values[i]);
    }

    free(indices);
    free(values);
    free(count);
    free(answer);
    free(A);
    free(dsu);

    return 0;
}
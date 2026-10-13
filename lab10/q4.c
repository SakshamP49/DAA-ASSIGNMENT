#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int parent;
    int size;
    long long sum;
} DSU;

int find(DSU dsu[], int x)
{
    if (dsu[x].parent == x)
        return x;

    dsu[x].parent = find(dsu, dsu[x].parent);
    return dsu[x].parent;
}

void unite(DSU dsu[], int a, int b, long long *maximum)
{
    int ra = find(dsu, a);
    int rb = find(dsu, b);

    if (ra == rb)
        return;

    if (dsu[ra].size < dsu[rb].size)
    {
        int temp = ra;
        ra = rb;
        rb = temp;
    }

    dsu[rb].parent = ra;
    dsu[ra].size += dsu[rb].size;
    dsu[ra].sum += dsu[rb].sum;

    if (dsu[ra].sum > *maximum)
        *maximum = dsu[ra].sum;
}

int main()
{
    int V;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    int *weight = malloc(V * sizeof(int));

    printf("Enter vertex weights:\n");

    for (int i = 0; i < V; i++)
        scanf("%d", &weight[i]);

    int **adj = malloc(V * sizeof(int *));

    for (int i = 0; i < V; i++)
        adj[i] = calloc(V, sizeof(int));

    int E;

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges:\n");

    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        u--;
        v--;

        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    int *order = malloc(V * sizeof(int));

    printf("Enter deletion order:\n");

    for (int i = 0; i < V; i++)
    {
        scanf("%d", &order[i]);
        order[i]--;
    }

    DSU *dsu = malloc(V * sizeof(DSU));
    int *active = calloc(V, sizeof(int));
    long long *answer = malloc((V + 1) * sizeof(long long));

    for (int i = 0; i < V; i++)
    {
        dsu[i].parent = i;
        dsu[i].size = 1;
        dsu[i].sum = weight[i];
    }

    long long maximum = 0;

    answer[V] = 0;

    for (int i = V - 1; i >= 0; i--)
    {
        int v = order[i];

        active[v] = 1;

        dsu[v].parent = v;
        dsu[v].size = 1;
        dsu[v].sum = weight[v];

        if (weight[v] > maximum)
            maximum = weight[v];

        for (int u = 0; u < V; u++)
        {
            if (adj[v][u] && active[u])
                unite(dsu, v, u, &maximum);
        }

        answer[i] = maximum;
    }

    printf("\nMaximum component sum after each deletion:\n");

    for (int i = 1; i <= V; i++)
        printf("After deleting %d: %lld\n",
               order[i - 1] + 1,
               answer[i]);

    free(weight);
    free(order);
    free(active);
    free(answer);
    free(dsu);

    for (int i = 0; i < V; i++)
        free(adj[i]);

    free(adj);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int parent;
    int size;
    long long weight;
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

    if (dsu[ra].size < dsu[rb].size)
    {
        int temp = ra;
        ra = rb;
        rb = temp;
    }

    dsu[rb].parent = ra;
    dsu[ra].size += dsu[rb].size;
    dsu[ra].weight += dsu[rb].weight;
}

long long getMaximumWeight(DSU dsu[], int n, int K)
{
    long long maximum = 0;

    for (int i = 0; i < n; i++)
    {
        if (dsu[i].parent == i &&
            dsu[i].size <= K)
        {
            if (dsu[i].weight > maximum)
                maximum = dsu[i].weight;
        }
    }

    return maximum;
}

int main()
{
    int V, E, K;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter size threshold K: ");
    scanf("%d", &K);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    DSU *dsu = malloc(V * sizeof(DSU));

    printf("Enter vertex weights:\n");

    for (int i = 0; i < V; i++)
    {
        long long w;
        scanf("%lld", &w);

        dsu[i].parent = i;
        dsu[i].size = 1;
        dsu[i].weight = w;
    }

    printf("Maximum valid component weight initially: %lld\n",
           getMaximumWeight(dsu, V, K));

    printf("Enter edges:\n");

    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        u--;
        v--;

        if (u >= 0 && u < V &&
            v >= 0 && v < V)
        {
            unite(dsu, u, v);
        }

        printf("Maximum valid component weight = %lld\n",
               getMaximumWeight(dsu, V, K));
    }

    free(dsu);

    return 0;
}
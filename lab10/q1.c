#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int parent;
    int rank;
    int parity;   // parity[x] = color[x] ^ color[parent[x]]
} DSU;

int find(DSU dsu[], int x)
{
    if (dsu[x].parent == x)
        return x;

    int parent = dsu[x].parent;
    dsu[x].parent = find(dsu, parent);
    dsu[x].parity ^= dsu[parent].parity;

    return dsu[x].parent;
}

int addEdge(DSU dsu[], int u, int v)
{
    int ru = find(dsu, u);
    int pv = dsu[u].parity;

    int rv = find(dsu, v);
    int qv = dsu[v].parity;

    // Same component
    if (ru == rv)
    {
        // Edge must connect opposite colors
        if ((pv ^ qv) == 0)
            return 0;

        return 1;
    }

    // Merge the two components
    if (dsu[ru].rank < dsu[rv].rank)
    {
        dsu[ru].parent = rv;
        dsu[ru].parity = pv ^ qv ^ 1;
    }
    else if (dsu[ru].rank > dsu[rv].rank)
    {
        dsu[rv].parent = ru;
        dsu[rv].parity = pv ^ qv ^ 1;
    }
    else
    {
        dsu[rv].parent = ru;
        dsu[rv].parity = pv ^ qv ^ 1;
        dsu[ru].rank++;
    }

    return 1;
}

int main()
{
    int V, E;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    DSU *dsu = malloc(V * sizeof(DSU));

    for (int i = 0; i < V; i++)
    {
        dsu[i].parent = i;
        dsu[i].rank = 0;
        dsu[i].parity = 0;
    }

    printf("Enter edges (u v):\n");

    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        u--;
        v--;

        if (u < 0 || u >= V || v < 0 || v >= V)
        {
            printf("Edge %d skipped: invalid vertices\n", i + 1);
            continue;
        }

        if (addEdge(dsu, u, v))
            printf("Edge (%d, %d) added: graph remains bipartite\n",
                   u + 1, v + 1);
        else
            printf("Edge (%d, %d) rejected: violates bipartiteness\n",
                   u + 1, v + 1);
    }

    free(dsu);

    return 0;
}
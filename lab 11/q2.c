/* Q2. Multi-Source BFS for Radius-Constrained Voronoi Partition */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int to;
    int next;
} Edge;

int main()
{
    int V, E, K, R;
    printf("Enter number of vertices, edges, number of hubs, and radius R: ");
    scanf("%d %d", &V, &E);
    scanf("%d %d", &K, &R);

    int *head = malloc(V * sizeof(int));
    Edge *edges = malloc(2 * E * sizeof(Edge));

    for (int i = 0; i < V; i++)
        head[i] = -1;

    int edgeCount = 0;

    for (int i = 0; i < E; i++)
    {
        int u, v; printf("Enter edge %d (u v): ", i + 1);
        scanf("%d %d", &u, &v);

        u--;
        v--;

        edges[edgeCount].to = v;
        edges[edgeCount].next = head[u];
        head[u] = edgeCount++;

        edges[edgeCount].to = u;
        edges[edgeCount].next = head[v];
        head[v] = edgeCount++;
    }

    scanf("%d", &K);

    int *hub = malloc(K * sizeof(int));

    for (int i = 0; i < K; i++)
    {   printf("Enter hub %d: ", i + 1); 
        scanf("%d", &hub[i]);
        hub[i]--;
    }

    scanf("%d", &R);

    int *owner = malloc(V * sizeof(int));
    int *dist = malloc(V * sizeof(int));
    int *queue = malloc(V * sizeof(int));

    for (int i = 0; i < V; i++)
    {
        owner[i] = -1;
        dist[i] = -1;
    }

    int front = 0;
    int rear = 0;

    for (int i = 0; i < K; i++)
    {
        int h = hub[i];

        if (owner[h] == -1)
        {
            owner[h] = i + 1;
            dist[h] = 0;
            queue[rear++] = h;
        }
    }

    while (front < rear)
    {
        int u = queue[front++];

        if (dist[u] == R)
            continue;

        for (int e = head[u]; e != -1; e = edges[e].next)
        {
            int v = edges[e].to;

            if (owner[v] == -1)
            {
                owner[v] = owner[u];
                dist[v] = dist[u] + 1;
                queue[rear++] = v;
            }
        }
    }

    printf("Vertex\tOwner\tDistance\n");

    for (int i = 0; i < V; i++)
    {
        if (owner[i] == -1)
            printf("%d\t-1\t-1\n", i + 1);
        else
            printf("%d\t%d\t%d\n",
                   i + 1,
                   owner[i],
                   dist[i]);
    }

    free(owner);
    free(dist);
    free(queue);
    free(hub);
    free(head);
    free(edges);

    return 0;
}
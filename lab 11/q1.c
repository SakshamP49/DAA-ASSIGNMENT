/* Q1. Shortest Path on Parity-Constrained Graphs via 0-1 BFS */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int to;
    int weight;
    int next;
} Edge;

typedef struct
{
    int *data;
    int front;
    int back;
    int capacity;
} Deque;

void initDeque(Deque *dq, int capacity)
{
    dq->data = malloc(capacity * sizeof(int));
    dq->front = capacity / 2;
    dq->back = dq->front;
    dq->capacity = capacity;
}

void pushFront(Deque *dq, int value)
{
    dq->data[--dq->front] = value;
}

void pushBack(Deque *dq, int value)
{
    dq->data[dq->back++] = value;
}

int popFront(Deque *dq)
{
    return dq->data[dq->front++];
}

int empty(Deque *dq)
{
    return dq->front == dq->back;
}

int main()
{
    int V, E, S;
    long long C;
    printf("Enter number of vertices, edges, starting vertex, and cost C: ");
    scanf("%d %d", &V, &E); 
    scanf("%d %lld", &S, &C); // lld is the accepted format specifier for long long in C

    S--;

    int *head = malloc(V * sizeof(int));
    Edge *edges = malloc(E * sizeof(Edge));

    for (int i = 0; i < V; i++)
        head[i] = -1;

    int edgeCount = 0;

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        printf("Enter edge %d (u v w): ", i + 1);
        scanf("%d %d %d", &u, &v, &w);

        u--;
        v--;

        edges[edgeCount].to = v;
        edges[edgeCount].weight = w;
        edges[edgeCount].next = head[u];
        head[u] = edgeCount++;

    }

    int states = 2 * V;
    long long INF = LLONG_MAX / 4;

    long long *dist = malloc(states * sizeof(long long));

    for (int i = 0; i < states; i++)
        dist[i] = INF;

    Deque dq;
    initDeque(&dq, 4 * states + 10);

    int sourceState = 2 * S;

    dist[sourceState] = 0;
    pushFront(&dq, sourceState);

    while (!empty(&dq))
    {
        int state = popFront(&dq);

        int u = state / 2;
        int parity = state % 2;

        for (int e = head[u]; e != -1; e = edges[e].next)
        {
            int v = edges[e].to;
            int w = edges[e].weight;

            int newParity = parity ^ w;
            int newState = 2 * v + newParity;

            if (dist[u * 2 + parity] + w < dist[newState])
            {
                dist[newState] =
                    dist[u * 2 + parity] + w;

                if (w == 0)
                    pushFront(&dq, newState);
                else
                    pushBack(&dq, newState);
            }
        }
    }

    printf("Vertex\tMinimum Cost\n");

    for (int v = 0; v < V; v++)
    {
        long long answer = INF;

        if (dist[2 * v] < answer)
            answer = dist[2 * v];

        if (dist[2 * v + 1] != INF &&
            dist[2 * v + 1] + C < answer)
        {
            answer = dist[2 * v + 1] + C;
        }

        if (answer == INF)
            printf("%d\tUnreachable\n", v + 1);
        else
            printf("%d\t%lld\n", v + 1, answer);
    }

    free(dq.data);
    free(dist);
    free(head);
    free(edges);

    return 0;
}
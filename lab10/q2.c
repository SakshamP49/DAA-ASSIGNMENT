#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int parent;
    int size;
} DSU;

int find(DSU dsu[], int x)
{
    if (dsu[x].parent == x)
        return x;

    dsu[x].parent = find(dsu, dsu[x].parent);
    return dsu[x].parent;
}

int unite(DSU dsu[], int a, int b)
{
    int ra = find(dsu, a);
    int rb = find(dsu, b);

    if (ra == rb)
        return 0;

    if (dsu[ra].size < dsu[rb].size)
    {
        int temp = ra;
        ra = rb;
        rb = temp;
    }

    dsu[rb].parent = ra;
    dsu[ra].size += dsu[rb].size;

    return 1;
}

int main()
{
    int R, C, K;

    printf("Enter rows and columns: ");
    scanf("%d %d", &R, &C);

    printf("Enter number of land additions: ");
    scanf("%d", &K);

    int total = R * C;

    DSU *dsu = malloc(total * sizeof(DSU));
    int *land = calloc(total, sizeof(int));

    for (int i = 0; i < total; i++)
    {
        dsu[i].parent = i;
        dsu[i].size = 1;
    }

    int components = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    printf("Enter land positions (row column):\n");

    for (int op = 0; op < K; op++)
    {
        int r, c;
        scanf("%d %d", &r, &c);

        if (r < 0 || r >= R || c < 0 || c >= C)
        {
            printf("Invalid position -> %d\n", components);
            continue;
        }

        int id = r * C + c;

        if (land[id])
        {
            printf("%d\n", components);
            continue;
        }

        land[id] = 1;
        components++;

        for (int d = 0; d < 4; d++)
        {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr < 0 || nr >= R ||
                nc < 0 || nc >= C)
                continue;

            int neighbor = nr * C + nc;

            if (land[neighbor])
            {
                if (unite(dsu, id, neighbor))
                    components--;
            }
        }

        printf("%d\n", components);
    }

    free(dsu);
    free(land);

    return 0;
}
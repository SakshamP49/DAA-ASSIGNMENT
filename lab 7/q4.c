#include <stdio.h>
#include <stdlib.h>

int isLegal(int state, int n, int pos)
{
    // Rightmost switch can always be toggled
    if (pos == n - 1)
        return 1;

    // Immediate right switch must be ON
    if ((state & (1 << (pos + 1))) == 0)
        return 0;

    // Every switch further right must be OFF
    for (int j = pos + 2; j < n; j++)
    {
        if (state & (1 << j))
            return 0;
    }

    return 1;
}

void printState(int state, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (state & (1 << i))
            printf("1 ");
        else
            printf("0 ");
    }

    printf("\n");
}

int main()
{
    int n;

    printf("Enter number of switches (<= 20): ");
    scanf("%d", &n);

    int totalStates = 1 << n;
    int start = totalStates - 1;
    int goal = 0;

    int *distance = malloc(totalStates * sizeof(int));
    int *parent = malloc(totalStates * sizeof(int));
    int *moveUsed = malloc(totalStates * sizeof(int));
    int *queue = malloc(totalStates * sizeof(int));

    for (int i = 0; i < totalStates; i++)
    {
        distance[i] = -1;
        parent[i] = -1;
        moveUsed[i] = -1;
    }

    int front = 0;
    int rear = 0;

    queue[rear++] = start;
    distance[start] = 0;

    while (front < rear)
    {
        int state = queue[front++];

        if (state == goal)
            break;

        for (int pos = 0; pos < n; pos++)
        {
            if (!isLegal(state, n, pos))
                continue;

            int nextState = state ^ (1 << pos);

            if (distance[nextState] == -1)
            {
                distance[nextState] =
                    distance[state] + 1;

                parent[nextState] = state;
                moveUsed[nextState] = pos;

                queue[rear++] = nextState;
            }
        }
    }

    printf("\nMinimum number of moves = %d\n",
           distance[goal]);

    printf("\nMinimum sequence:\n");

    int pathSize = distance[goal];
    int *path = malloc(pathSize * sizeof(int));

    int current = goal;

    for (int i = pathSize - 1; i >= 0; i--)
    {
        path[i] = moveUsed[current];
        current = parent[current];
    }

    current = start;

    printState(current, n);

    for (int i = 0; i < pathSize; i++)
    {
        printf("Toggle switch %d\n", path[i] + 1);

        current ^= (1 << path[i]);

        printState(current, n);
    }

    free(distance);
    free(parent);
    free(moveUsed);
    free(queue);
    free(path);

    return 0;
}
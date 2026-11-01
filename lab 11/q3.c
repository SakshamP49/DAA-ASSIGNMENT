/* Q3. Bidirectional BFS for Shortest Transformation Sequence */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 10
#define MAXN 100001
#define HASH_SIZE 524291

int hashWord(const char *s)
{
    unsigned long long hash = 1469598103934665603ULL;

    while (*s)
    {
        hash ^= (unsigned char)(*s);
        hash *= 1099511628211ULL;
        s++;
    }

    return (int)(hash % HASH_SIZE);
}

int findWord(char words[][MAXL + 1],
             int hashTable[],
             const char *word)
{
    int pos = hashWord(word);

    while (hashTable[pos] != -1)
    {
        int index = hashTable[pos];

        if (strcmp(words[index], word) == 0)
            return index;

        pos++;

        if (pos == HASH_SIZE)
            pos = 0;
    }

    return -1;
}

void insertWord(char words[][MAXL + 1],
                int hashTable[],
                int index)
{
    int pos = hashWord(words[index]);

    while (hashTable[pos] != -1)
    {
        pos++;

        if (pos == HASH_SIZE)
            pos = 0;
    }

    hashTable[pos] = index;
}

int expandFrontier(
    char words[][MAXL + 1],
    int hashTable[],
    int length,
    int frontier[],
    int frontierSize,
    int distThis[],
    int distOther[],
    int nextFrontier[])
{
    int nextSize = 0;

    for (int f = 0; f < frontierSize; f++)
    {
        int current = frontier[f];

        for (int pos = 0; pos < length; pos++)
        {
            char original = words[current][pos];

            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                if (ch == original)
                    continue;

                words[current][pos] = ch;

                int next =
                    findWord(words, hashTable,
                             words[current]);

                words[current][pos] = original;

                if (next == -1)
                    continue;

                if (distOther[next] != -1)
                {
                    return distThis[current]
                           + 1
                           + distOther[next];
                }

                if (distThis[next] == -1)
                {
                    distThis[next] =
                        distThis[current] + 1;

                    nextFrontier[nextSize++] = next;
                }
            }
        }
    }

    return -(nextSize + 1);
}

int main()
{
    int N, L;

    scanf("%d %d", &N, &L);

    if (L > MAXL)
    {
        printf("-1\n");
        return 0;
    }

    char (*words)[MAXL + 1] =
        malloc((N + 1) * sizeof(*words));

    int *hashTable =
        malloc(HASH_SIZE * sizeof(int));

    for (int i = 0; i < HASH_SIZE; i++)
        hashTable[i] = -1;

    for (int i = 0; i < N; i++)
    {
        scanf("%10s", words[i]);
        insertWord(words, hashTable, i);
    }

    char A[MAXL + 1];
    char B[MAXL + 1];

    scanf("%10s", A);
    scanf("%10s", B);

    if (strcmp(A, B) == 0)
    {
        printf("0\n");

        free(words);
        free(hashTable);

        return 0;
    }

    int start = findWord(words, hashTable, A);
    int target = findWord(words, hashTable, B);

    if (target == -1)
    {
        printf("-1\n");

        free(words);
        free(hashTable);

        return 0;
    }

    if (start == -1)
    {
        start = N;

        strcpy(words[start], A);

        insertWord(words, hashTable, start);

        N++;
    }

    int *distA = malloc(N * sizeof(int));
    int *distB = malloc(N * sizeof(int));

    int *frontA = malloc(N * sizeof(int));
    int *frontB = malloc(N * sizeof(int));

    int *nextA = malloc(N * sizeof(int));
    int *nextB = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
    {
        distA[i] = -1;
        distB[i] = -1;
    }

    int sizeA = 1;
    int sizeB = 1;

    frontA[0] = start;
    frontB[0] = target;

    distA[start] = 0;
    distB[target] = 0;

    int answer = -1;

    while (sizeA > 0 && sizeB > 0)
    {
        int result;

        if (sizeA <= sizeB)
        {
            result = expandFrontier(
                words,
                hashTable,
                L,
                frontA,
                sizeA,
                distA,
                distB,
                nextA
            );

            if (result >= 0)
            {
                answer = result;
                break;
            }

            sizeA = -(result + 1);

            for (int i = 0; i < sizeA; i++)
                frontA[i] = nextA[i];
        }
        else
        {
            result = expandFrontier(
                words,
                hashTable,
                L,
                frontB,
                sizeB,
                distB,
                distA,
                nextB
            );

            if (result >= 0)
            {
                answer = result;
                break;
            }

            sizeB = -(result + 1);

            for (int i = 0; i < sizeB; i++)
                frontB[i] = nextB[i];
        }
    }

    printf("%d\n", answer);

    free(words);
    free(hashTable);
    free(distA);
    free(distB);
    free(frontA);
    free(frontB);
    free(nextA);
    free(nextB);

    return 0;
}
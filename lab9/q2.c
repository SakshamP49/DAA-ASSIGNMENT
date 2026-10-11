#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 256
#define MAX_NODES 512
#define MAX_CODE_LEN 512

typedef struct
{
    char symbol;
    long long freq;
    int left;
    int right;
} Node;

typedef struct
{
    int data[MAX_NODES];
    int size;
} MinHeap;

typedef struct
{
    char symbol;
    long long freq;
    int length;
    char code[MAX_CODE_LEN];
} SymbolInfo;

Node nodes[MAX_NODES];
int nodeCount = 0;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int compareNodes(int a, int b)
{
    if (nodes[a].freq != nodes[b].freq)
        return nodes[a].freq < nodes[b].freq;

    return nodes[a].symbol < nodes[b].symbol;
}

void push(MinHeap *heap, int index)
{
    int i = heap->size++;

    heap->data[i] = index;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (compareNodes(heap->data[parent],
                         heap->data[i]))
            break;

        swap(&heap->data[parent],
             &heap->data[i]);

        i = parent;
    }
}

int pop(MinHeap *heap)
{
    int result = heap->data[0];

    heap->size--;

    if (heap->size > 0)
    {
        heap->data[0] =
            heap->data[heap->size];

        int i = 0;

        while (1)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < heap->size &&
                compareNodes(heap->data[left],
                             heap->data[smallest]))
            {
                smallest = left;
            }

            if (right < heap->size &&
                compareNodes(heap->data[right],
                             heap->data[smallest]))
            {
                smallest = right;
            }

            if (smallest == i)
                break;

            swap(&heap->data[i],
                 &heap->data[smallest]);

            i = smallest;
        }
    }

    return result;
}

void findLengths(int root, int depth,
                 SymbolInfo info[])
{
    if (root == -1)
        return;

    if (nodes[root].left == -1 &&
        nodes[root].right == -1)
    {
        int index = (unsigned char)nodes[root].symbol;

        info[index].symbol =
            nodes[root].symbol;

        info[index].freq =
            nodes[root].freq;

        info[index].length =
            (depth == 0) ? 1 : depth;

        return;
    }

    findLengths(nodes[root].left,
                depth + 1,
                info);

    findLengths(nodes[root].right,
                depth + 1,
                info);
}

int compareSymbols(const void *a, const void *b)
{
    const SymbolInfo *x = a;
    const SymbolInfo *y = b;

    if (x->length != y->length)
        return x->length - y->length;

    return (unsigned char)x->symbol -
           (unsigned char)y->symbol;
}

void setZeros(char code[], int length)
{
    for (int i = 0; i < length; i++)
        code[i] = '0';

    code[length] = '\0';
}

void incrementBinary(char code[], int length)
{
    int i = length - 1;

    while (i >= 0 && code[i] == '1')
    {
        code[i] = '0';
        i--;
    }

    if (i >= 0)
        code[i] = '1';
}

int main()
{
    int n;

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    MinHeap heap;
    heap.size = 0;

    SymbolInfo info[MAX_SYMBOLS];

    for (int i = 0; i < MAX_SYMBOLS; i++)
    {
        info[i].symbol = 0;
        info[i].freq = 0;
        info[i].length = 0;
        info[i].code[0] = '\0';
    }

    for (int i = 0; i < n; i++)
    {
        char symbol;
        long long freq;

        printf("Enter symbol and frequency: ");
        scanf(" %c %lld", &symbol, &freq);

        nodes[nodeCount].symbol = symbol;
        nodes[nodeCount].freq = freq;
        nodes[nodeCount].left = -1;
        nodes[nodeCount].right = -1;

        push(&heap, nodeCount);

        nodeCount++;
    }

    if (n == 0)
        return 0;

    while (heap.size > 1)
    {
        int a = pop(&heap);
        int b = pop(&heap);

        nodes[nodeCount].symbol =
            (nodes[a].symbol < nodes[b].symbol)
            ? nodes[a].symbol
            : nodes[b].symbol;

        nodes[nodeCount].freq =
            nodes[a].freq + nodes[b].freq;

        nodes[nodeCount].left = a;
        nodes[nodeCount].right = b;

        push(&heap, nodeCount);

        nodeCount++;
    }

    int root = pop(&heap);

    findLengths(root, 0, info);

    SymbolInfo list[MAX_SYMBOLS];
    int count = 0;

    for (int i = 0; i < MAX_SYMBOLS; i++)
    {
        if (info[i].length > 0)
        {
            list[count++] = info[i];
        }
    }

    qsort(list, count,
          sizeof(SymbolInfo),
          compareSymbols);

    char currentCode[MAX_CODE_LEN];
    currentCode[0] = '\0';

    int previousLength = 0;

    for (int i = 0; i < count; i++)
    {
        int len = list[i].length;

        if (i == 0)
        {
            setZeros(currentCode, len);
        }
        else
        {
            incrementBinary(currentCode,
                            previousLength);

            int currentLength =
                strlen(currentCode);

            while (currentLength < len)
            {
                currentCode[currentLength] = '0';
                currentLength++;
                currentCode[currentLength] = '\0';
            }
        }

        strcpy(list[i].code, currentCode);

        previousLength = len;
    }

    printf("\nCanonical Huffman Codebook:\n");

    for (int i = 0; i < count; i++)
    {
        printf("%c  Frequency=%lld  Code=%s\n",
               list[i].symbol,
               list[i].freq,
               list[i].code);
    }

    return 0;
}
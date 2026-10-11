#include <stdio.h>
#include <string.h>

#define MAX 1000
#define CHARSET 256

typedef struct
{
    unsigned char ch;
    int count;
} HeapNode;

typedef struct
{
    unsigned char ch;
    int count;
    int readyPosition;
} CooldownNode;

HeapNode heap[CHARSET];
int heapSize = 0;

void swap(HeapNode *a, HeapNode *b)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(HeapNode node)
{
    int i = heapSize++;

    heap[i] = node;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (heap[parent].count > heap[i].count)
            break;

        if (heap[parent].count == heap[i].count &&
            heap[parent].ch < heap[i].ch)
            break;

        swap(&heap[parent], &heap[i]);

        i = parent;
    }
}

HeapNode pop()
{
    HeapNode result = heap[0];

    heapSize--;

    if (heapSize > 0)
    {
        heap[0] = heap[heapSize];

        int i = 0;

        while (1)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;

            if (left < heapSize)
            {
                if (heap[left].count > heap[largest].count ||
                    (heap[left].count == heap[largest].count &&
                     heap[left].ch > heap[largest].ch))
                {
                    largest = left;
                }
            }

            if (right < heapSize)
            {
                if (heap[right].count > heap[largest].count ||
                    (heap[right].count == heap[largest].count &&
                     heap[right].ch > heap[largest].ch))
                {
                    largest = right;
                }
            }

            if (largest == i)
                break;

            swap(&heap[i], &heap[largest]);

            i = largest;
        }
    }

    return result;
}

int main()
{
    char S[MAX];
    int K;

    printf("Enter string: ");
    scanf("%999s", S);

    printf("Enter K: ");
    scanf("%d", &K);

    if (K <= 1)
    {
        printf("Reorganised string = %s\n", S);
        return 0;
    }

    int frequency[CHARSET] = {0};

    int length = strlen(S);

    for (int i = 0; i < length; i++)
        frequency[(unsigned char)S[i]]++;

    heapSize = 0;

    for (int i = 0; i < CHARSET; i++)
    {
        if (frequency[i] > 0)
        {
            HeapNode node;

            node.ch = i;
            node.count = frequency[i];

            push(node);
        }
    }

    CooldownNode queue[MAX];
    int front = 0;
    int rear = 0;

    char result[MAX];
    int resultIndex = 0;

    for (int position = 0;
         position < length;
         position++)
    {
        while (front < rear &&
               queue[front].readyPosition <= position)
        {
            HeapNode node;

            node.ch = queue[front].ch;
            node.count = queue[front].count;

            push(node);

            front++;
        }

        if (heapSize == 0)
        {
            printf("Reorganised string = \n");
            return 0;
        }

        HeapNode current = pop();

        result[resultIndex++] = current.ch;
        current.count--;

        if (current.count > 0)
        {
            queue[rear].ch = current.ch;
            queue[rear].count = current.count;
            queue[rear].readyPosition = position + K;

            rear++;
        }
    }

    result[resultIndex] = '\0';

    printf("Reorganised string = %s\n",
           result);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct Event {
    int time;
    int type;   // +1 = entry, -1 = exit
};

int compare(const void *a, const void *b) {
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;

    return e1->time - e2->time;
}

int main() {
    int n;

    printf("Enter number of people: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    printf("Enter entry and exit times:\n");

    for (int i = 0; i < n; i++) {
        int a, b;

        scanf("%d %d", &a, &b);

        events[2 * i].time = a;
        events[2 * i].type = 1;

        events[2 * i + 1].time = b;
        events[2 * i + 1].type = -1;
    }

    qsort(events, 2 * n, sizeof(struct Event), compare);

    int current = 0;
    int maximum = 0;
    int maxTime = 0;

    for (int i = 0; i < 2 * n; i++) {
        current += events[i].type;

        if (current > maximum) {
            maximum = current;
            maxTime = events[i].time;
        }
    }

    printf("Maximum number of people = %d\n", maximum);
    printf("Time = %d\n", maxTime);

    return 0;
}
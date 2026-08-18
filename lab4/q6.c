#include <stdio.h>
#include <stdlib.h>

struct Event {
    int point;
    int type;   // +1 = start, -1 = end
};

int compare(const void *a, const void *b) {
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;

    if (e1->point != e2->point)
        return e1->point - e2->point;

    // Start must come before end
    return e2->type - e1->type;
}

int main() {
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    printf("Enter intervals:\n");

    for (int i = 0; i < n; i++) {
        int l, r;

        scanf("%d %d", &l, &r);

        events[2 * i].point = l;
        events[2 * i].type = 1;

        events[2 * i + 1].point = r;
        events[2 * i + 1].type = -1;
    }

    qsort(events, 2 * n, sizeof(struct Event), compare);

    int current = 0;
    int maximum = 0;
    int answerPoint = 0;

    for (int i = 0; i < 2 * n; i++) {

        current += events[i].type;

        if (current > maximum) {
            maximum = current;
            answerPoint = events[i].point;
        }
    }

    printf("Point with maximum overlap = %d\n", answerPoint);
    printf("Maximum number of intervals = %d\n", maximum);

    return 0;
}
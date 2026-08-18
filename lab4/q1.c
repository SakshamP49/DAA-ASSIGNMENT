#include <stdio.h>

struct Item {
    int number;
    char color;
};

int main() {
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item red[n], blue[n], yellow[n];
    int r = 0, b = 0, y = 0;

    printf("Enter number and color (R/B/Y):\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %c", &red[0].number, &red[0].color);

        if (red[0].color == 'R' || red[0].color == 'r') {
            red[r++] = red[0];
        }
        else if (red[0].color == 'B' || red[0].color == 'b') {
            blue[b].number = red[0].number;
            blue[b].color = red[0].color;
            b++;
        }
        else if (red[0].color == 'Y' || red[0].color == 'y') {
            yellow[y].number = red[0].number;
            yellow[y].color = red[0].color;
            y++;
        }
    }

    printf("\nSorted by colour:\n");

    for (int i = 0; i < r; i++)
        printf("(%d, R) ", red[i].number);

    for (int i = 0; i < b; i++)
        printf("(%d, B) ", blue[i].number);

    for (int i = 0; i < y; i++)
        printf("(%d, Y) ", yellow[i].number);

    printf("\n");

    return 0;
}
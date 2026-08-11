#include <stdio.h>

long long toh_moves(int n, char from, char to, char aux) {
    if (n == 1) {
        return 1;
    }
    long long m1 = toh_moves(n - 1, from, aux, to);
    long long m2 = 1; // move nth disc
    long long m3 = toh_moves(n - 1, aux, to, from);
    return m1 + m2 + m3;
}

int main() {
    int n = 4;
    long long total_moves = toh_moves(n, 'A', 'C', 'B');
    printf("Total moves required for %d discs: %lld\n", n, total_moves);
    return 0;
}
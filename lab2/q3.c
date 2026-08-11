#include <stdio.h>
#include <stdlib.h>

// Simulation of Merging k sorted arrays complexities
int main() {
    int k = 8;
    int n = 100;

    long long method1_ops = (long long)n * k * k; // O(n * k^2)
    long long method2_ops = (long long)n * k * log2(k); // O(kn log k)

    printf("For k = %d, n = %d:\n", k, n);
    printf("Method 1 (Repeated Merge) Estimated Cost: %lld operations\n", method1_ops);
    printf("Method 2 (Pairwise Merge Tree) Estimated Cost: %lld operations\n", method2_ops);

    return 0;
}
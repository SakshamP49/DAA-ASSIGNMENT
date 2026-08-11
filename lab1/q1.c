#include <stdio.h>
#include <math.h>

double f1(double n) { return 1.0 / n; }
double f2(double n) { return log2(n); }
double f3(double n) { return 4294967296.0 * n; } // 2^32 * n
double f4(double n) { return 12 * sqrt(n); }
double f5(double n) { return 50 * pow(n, 0.5); }
double f6(double n) { return pow(n, 0.51); }
double f7(double n) { return n * log2(n); }
double f8(double n) { return 100 * n * n + 6 * n; }
double f9(double n) { return n * n - 324; }
double f10(double n) { return pow(n, log2(n)); }
double f11(double n) { return 2 * pow(n, 3); }
double f12(double n) { return pow(3, n); }

int main() {
    double n = 1000.0;
    printf("Evaluating functions at n = %.1f\n", n);
    // Print or verify order programmatically
    return 0;
}
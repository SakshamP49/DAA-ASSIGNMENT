#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846

void fft(double complex *a, int n, int invert) {
    if (n == 1) return;
    
    double complex a0[n/2], a1[n/2];
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    
    fft(a0, n/2, invert);
    fft(a1, n/2, invert);
    
    double angle = 2 * PI / n * (invert ? -1 : 1);
    double complex w = 1, wn = cexp(I * angle);
    
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

void convolve(double *A, int m, double *B, int n, double *C) {
    int size = 1;
    while (size < n + m - 1) size *= 2;
    
    double complex *cA = calloc(size, sizeof(double complex));
    double complex *cB = calloc(size, sizeof(double complex));
    
    for (int i = 0; i < m; i++) cA[i] = A[i];
    for (int i = 0; i < n; i++) cB[i] = B[i];
    
    fft(cA, size, 0);
    fft(cB, size, 0);
    
    for (int i = 0; i < size; i++) cA[i] *= cB[i];
    
    fft(cA, size, 1);
    
    for (int i = 0; i < n + m - 1; i++) C[i] = creal(cA[i]);
    
    free(cA);
    free(cB);
}

int main() {
    double A[] = {1, 2, 3}; // Size m=3
    double B[] = {4, 5, 6, 7}; // Size n=4
    int m = 3, n = 4;
    double C[6] = {0}; // m+n-1 = 6
    
    convolve(A, m, B, n, C);
    
    printf("Convolution result: ");
    for(int i=0; i<m+n-1; i++) printf("%.2f ", C[i]);
    return 0;
}
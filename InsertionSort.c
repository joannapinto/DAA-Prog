#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int *A, int n) {
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

int main() {
    FILE *fp = fopen("time_vs_n_insertion.csv", "w");
    if (!fp) return 1;
    fprintf(fp, "n,time_taken\n");
    srand(time(NULL));
    for (int n = 100; n <= 2000; n += 100) {
        int *A = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) A[i] = rand() % 1000;
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        insertionSort(A, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        fprintf(fp, "%d,%.6f\n", n, time_taken);
        free(A);
    }
    fclose(fp);
    return 0;
}

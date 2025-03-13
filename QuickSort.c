#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int *A, int low, int high) {
    int pivot = A[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp = A[i + 1];
    A[i + 1] = A[high];
    A[high] = temp;
    return i + 1;
}

void quickSort(int *A, int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high);
        quickSort(A, low, pi - 1);
        quickSort(A, pi + 1, high);
    }
}

int main() {
    FILE *fp = fopen("time_vs_n_quick.csv", "w");
    if (!fp) return 1;
    fprintf(fp, "n,time_taken\n");
    srand(time(NULL));
    for (int n = 100; n <= 2000; n += 100) {
        int *A = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) A[i] = rand() % 1000;
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        quickSort(A, 0, n - 1);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        fprintf(fp, "%d,%.6f\n", n, time_taken);
        free(A);
    }
    fclose(fp);
    return 0;
}

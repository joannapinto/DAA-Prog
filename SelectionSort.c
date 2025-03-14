#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int *A, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[minIdx]) {
                minIdx = j;
            }
        }
        int temp = A[i];
        A[i] = A[minIdx];
        A[minIdx] = temp;
    }
}

int main() {
    FILE *fp = fopen("time_vs_n_selection.csv", "w");
    if (!fp) return 1;
    fprintf(fp, "n,time_taken\n");
    srand(time(NULL));
    for (int n = 100; n <= 2000; n += 100) {
        int *A = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) A[i] = rand() % 1000;
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        selectionSort(A, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        fprintf(fp, "%d,%.6f\n", n, time_taken);
        free(A);
    }
    fclose(fp);
    return 0;
}

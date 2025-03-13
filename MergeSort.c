#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int *A, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = A[left + i];
    for (int i = 0; i < n2; i++) R[i] = A[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) A[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];
    free(L);
    free(R);
}

void mergeSort(int *A, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}

int main() {
    FILE *fp = fopen("time_vs_n_merge.csv", "w");
    if (!fp) return 1;
    fprintf(fp, "n,time_taken\n");
    srand(time(NULL));
    for (int n = 100; n <= 2000; n += 100) {
        int *A = (int *)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) A[i] = rand() % 1000;
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        mergeSort(A, 0, n - 1);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        fprintf(fp, "%d,%.6f\n", n, time_taken);
        free(A);
    }
    fclose(fp);
    return 0;
}

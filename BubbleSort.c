#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() 
{
    FILE *fp = fopen("time_vs_n_bubble.csv", "w");
    if (!fp) 
    { 
        printf("Error opening file.\n"); 
        return 1; 
    }
    fprintf(fp, "n,time_taken\n");
    srand(time(NULL));
    for (int n = 100; n <= 2000; n += 100) 
    {
        int *A = (int *)malloc(n * sizeof(int));
        if (!A) 
        {
            printf("Memory allocation failed.\n");
            fclose(fp);
            return 1;
        }
        for (int i = 0; i < n; i++) 
        {
            A[i] = rand() % 1000;
        }
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - 1 - i; j++) 
            {
                if (A[j + 1] < A[j]) 
                { 
                    int temp = A[j]; 
                    A[j] = A[j + 1]; 
                    A[j + 1] = temp; 
                }
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        fprintf(fp, "%d,%.6f\n", n, time_taken);
        free(A);
    }
    fclose(fp);
    printf("Experiment completed. Results saved to time_vs_n_bubble.csv.\n");
    return 0;
}


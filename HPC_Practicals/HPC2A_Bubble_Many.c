#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int main()
{
    // set no. of threads to use
    omp_set_num_threads(6);

    int SIZE = 100000;
    int i, j;
    int A[SIZE];
    for (i = 0; i < SIZE; i++)
    {
        A[i] = rand() % SIZE;
    }

    int N = SIZE;
    i = 0;
    j = 0;
    int first;
    double start, end;
    start = omp_get_wtime();
    for (i = 0; i < N - 1; i++)
    {
        first = i % 2;
#pragma omp parallel for default(none), shared(A, first, N)
        for (j = first; j < N - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                swap(&A[j], &A[j + 1]);
            }
        }
    }

    end = omp_get_wtime();
    
    for (i = 0; i < N; i++)
    {
        printf(" %d", A[i]);
    }

    printf("\n-------------------------\n Time Parallel= %f", (end - start));
}

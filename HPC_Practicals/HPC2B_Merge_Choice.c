#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int array[], int low, int mid, int high)
{
    int temp[high - low + 1]; // Declare temp array with appropriate size

    int i = low, j = mid + 1, k = 0;

    // Merge two subarrays into temp array
    while (i <= mid && j <= high)
    {
        if (array[i] <= array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }

    // Copy remaining elements from the first subarray
    while (i <= mid)
        temp[k++] = array[i++];

    // Copy remaining elements from the second subarray
    while (j <= high)
        temp[k++] = array[j++];

    // Copy elements from temp array back to original array
    for (i = low, k = 0; i <= high; i++, k++)
        array[i] = temp[k];
}

void mergesort(int array[], int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;

#pragma omp parallel sections num_threads(8)
        {
#pragma omp section
            {
                mergesort(array, low, mid);
            }

#pragma omp section
            {
                mergesort(array, mid + 1, high);
            }
        }
        merge(array, low, mid, high);
    }
}

int main()
{
    
    int *arr, n;
    int choice;
    
    double start, end;
    printf("\n1. Manual Entry\n2. Create unsorted array of given size\n");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            printf("Enter the total number of elements: ");
            scanf("%d", &n);
            arr = (int *) malloc(n * sizeof(int));
            printf("Enter elements: ");
            for (int i = 0; i < n; i++) {
                scanf("%d", &arr[i]);
            }
            break;

        case 2:
            printf("Enter the size of the array: ");
            scanf("%d", &n);
            arr = (int *) malloc(n *sizeof(int));
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % n;
            }
            break;

        default:
            printf("Try Again");
    }

    start = omp_get_wtime();

    mergesort(arr, 0, n - 1); 
    printf("Sorted Elements as follows:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);

    end = omp_get_wtime();

    printf("\n-------------------------\n Time Parallel= %f", (end - start));

    return 0;
}
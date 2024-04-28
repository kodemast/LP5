#include<iostream>
#include<omp.h>
#include <stdlib.h>

using namespace std;

int k = 0;

class Sorter {
    public:
        int partition(int arr[], int low_index, int high_index){
            int i, j, temp, key;
            key = arr[low_index];
            i = low_index + 1;
            j = high_index;

            while(1){
                while(i < high_index && key >= arr[i]){
                    i++;
                }
                while(key<arr[j]){
                    j--;
                }
                if(i < j){
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                } else {
                    temp = arr[low_index];
                    arr[low_index] = arr[j];
                    arr[j] = temp;
                    return(j);
                }
            }
        }
        void quicksort(int arr[], int low_index, int high_index){
            int j;

            if(low_index < high_index){
                j = partition(arr, low_index, high_index);
                cout<<"Pivot element with index " << j << " has been found out by thread " << k << "\n";

                #pragma omp parallel sections
                {
                    #pragma omp section
                    {
                        k = k + 1;
                        quicksort(arr, low_index, j - 1);
                    }
                    
                    #pragma omp section
                    {
                        k = k + 1;
                        quicksort(arr, j + 1, high_index);
                    }
                }
            }
        }
};

int main(){
    Sorter a;

    int *arr, n;
    int choice;
    
    double start, end;
    cout<<"\n1. Manual Entry\n2. Create unsorted array of given size\n";
    cin >> choice;
    switch(choice){
        case 1:
            cout<<"Enter the total number of elements: ";
            cin>>n;
            arr = new int(n);
            cout<<"Enter elements: ";
            for (int i = 0; i < n; i++) {
                cin>>arr[i];
            }
            break;

        case 2:
            cout<<"Enter the size of the array: ";
            cin>>n;
            arr = new int[n];
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % n;
            }
            break;

        default:
            cout<<"Try Again";
    }
    start = omp_get_wtime();

    a.quicksort(arr, 0, n - 1);

    cout<<"Sorted Elements as follows:\n";
    for (int i = 0; i < n; i++)
        cout<<arr[i]<< " ";
    cout<<endl;

    end = omp_get_wtime();

    cout<<"\n-------------------------\n Time for Parallel execution = " << (end - start);
    return 0;
}

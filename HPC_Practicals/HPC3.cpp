#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <climits>


using namespace std;

void min_reduction(int arr[], int n)
{
    int min_value = INT_MAX;
#pragma omp parallel for reduction(min : min_value)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min_value)
        {
            min_value = arr[i];
        }
    }
    cout << "Minimum value: " << min_value << endl;
}

void max_reduction(int arr[], int n)
{
    int max_value = INT_MIN;
#pragma omp parallel for reduction(max : max_value)
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_value)
        {
            max_value = arr[i];
        }
    }
    cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(int arr[], int n)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}

void average_reduction(int arr[], int n)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    cout << "Average: " << (double)sum / (n - 1) << endl;
}

int main()
{
    int *arr, n;
    int choice;

    cout<<"\n1. Manual Entry\n2. Create unsorted array of given size\n";
    cin>>choice;
    switch(choice){
        case 1:
            cout << "\nEnter total no of elements=>";
            cin >> n;
            arr = new int[n];
            cout << "\nEnter elements=> ";
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            break;
        
        case 2:
            cout<<"Enter the size of array: ";
            cin>>n;
            arr = new int[n];
            for (int i = 0; i < n; i++)
            {
                arr[i] = rand() % n;
            }
            break;
        
        default:
            cout<<"Try Again";
    }


    for(int i = 0; i < n; i++){
        cout<<arr[i]<< " ";
    }
    cout<<"\n";
    min_reduction(arr, n);
    max_reduction(arr, n);
    sum_reduction(arr, n);
    average_reduction(arr, n);
}
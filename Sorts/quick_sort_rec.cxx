#include <cstdlib>
#include <iostream>
#include <chrono>

using namespace std;

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    
    int i = low;
    
    int temp;
    
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
          //  if (i != j)
         //   {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
         //   }
            
            i++;
        }
    }
    
    temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;
    
    return i;
}

void quick_sort(int arr[], int low, int high)
{
    int pi;
    
    if (low < high)
    {

        pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);

        quick_sort(arr, pi + 1, high);

    }
}

int main(int argc, char** argv) 
{
    int n, number;

    cin >> n;

    int arr[n];

    for (int i = 0 ; i < n; i++)
    {
        cin >> number;
        arr[i] = number;
    }



    auto start = chrono::system_clock::now();
    
    quick_sort(arr, 0, n - 1);
    
    auto end = chrono::system_clock::now();
        chrono::duration<double> diff = end-start;
    cout << n << " " << diff.count() << endl;
    
    // for (int i = 0 ; i < n; i++)
    // {
    //     cout << arr[i] << endl;
    // }
    
    return 0;
}


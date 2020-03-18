#include <cstdlib>
#include <iostream>
#include <chrono>

using namespace std;

void merge(int arr[], int left_idx, int middle_idx, int right_idx)
{
    int left_size = middle_idx - left_idx + 1;
    int right_size = right_idx - middle_idx;
    
    int Left_arr[left_size], Right_arr[right_size];
    
    // kopiowanie elementow z przedzialu do nowych tablic

    for (int i = 0; i < left_size; i++)
        Left_arr[i] = arr[left_idx + i];

    for (int i = 0; i < right_size; i++)
        Right_arr[i] = arr[middle_idx + i + 1];    

    // sortowanie nowych tablic

    int i = 0, j = 0, k = left_idx;
    
    while (i < left_size && j < right_size)
    {
        if (Left_arr[i] <= Right_arr[j])
        {
            arr[k] = Left_arr[i];
            i++;
        }
        
        else
        {
            arr[k] = Right_arr[j];
            j++;
        }
    
        k++;
    }
    
    // kopiuje pozostale elementy
    while (i < left_size)
    {
        arr[k] = Left_arr[i];
        i++;
        k++;
    }
    
    while (j < right_size)
    {
        arr[k] = Right_arr[j];
        j++;
        k++;
    }    
    
}

void merge_sort(int arr[], int left_idx, int right_idx)
{
    if (left_idx < right_idx)
    {
        int middle_idx = (left_idx + right_idx)/2;
        
        merge_sort(arr, middle_idx + 1, right_idx);
        merge_sort(arr, left_idx, middle_idx);
        
        merge(arr, left_idx, middle_idx, right_idx);
    }
    
}
int main(int argc, char** argv) 
{
    int n, number;
    cin >> n;

    int arr[n];
    
    for (int i = 0;i < n; i++)
    {
        cin >> number;
        arr[i] = number;
    }
    
    auto start = chrono::system_clock::now();
    
    merge_sort(arr, 0, n - 1);
    
    auto end = chrono::system_clock::now();
        chrono::duration<double> diff = end-start;
    cout << n << " " << diff.count() << endl;
    
    // for (int i = 0 ; i < n; i++)
    // {
    //     cout << arr[i] << endl;
    // }
    
    return 0;
}


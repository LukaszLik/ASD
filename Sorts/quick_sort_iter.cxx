/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   quick_sort_iter.cpp
 * Author: frsh
 *
 * Created on December 1, 2018, 11:50 AM
 */

#include <cstdlib>
#include <iostream>
#include <stack>
#include <chrono>

using namespace std;

int partition(int arr[], int left, int right)
{
    int pivot = arr[right];
    int i = left;
    
    int temp;
    
    for (int j = left; j < right; j++)
    {
        if (arr[j] <= pivot)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }

    temp = arr[i];
    arr[i] = arr[right];
    arr[right] = temp;
    
    return i;
}

int main(int argc, char** argv) 
{
    int n, number;

    cin >> n;

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        cin >> number;
        arr[i] = number;
    }

    auto start = chrono::system_clock::now();


    int left, right;
    int top = -1;
    stack <int> stack;
    
    stack.push(n - 1);
    stack.push(0);
    
    while (!stack.empty())
    {
        left = stack.top();
        stack.pop();

        right = stack.top();
        stack.pop();
        
        int p = partition(arr, left, right);

        
        if (p - 1 > left)
        {
            stack.push(p-1);
    
            stack.push(left);
        }
  
        if (p + 1 < right)
        {
            stack.push(right);
    
            stack.push(p+1);
        }     
        
    }
    
    auto end = chrono::system_clock::now();
        chrono::duration<double> diff = end-start;
    cout << n << " " << diff.count() << endl;
    
    return 0;
}


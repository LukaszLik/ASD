/* 
 * File:   radix_sort.cpp
 * Author: fresh222
 *
 * Created on November 25, 2018, 12:51 PM
 */

#include <cstdlib>
#include <iostream>
#include <chrono>
#include "queue.hxx"

using namespace std;

int main(int argc, char** argv) 
{
    int range, number, n;
    int max;
    cin >> range;
    cin >> n;
    
    Queue q_arr[10];;
    int arr[n], size[10];
    max = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> number;
        arr[i] = number;
    	
	if (number > max)
		max = number;
    }
    
    
    //for (int i = 1; i < (range*10); i*=10)
    //{
    // pierwszaa iteracja wpisujemy rzeczy do kolejek
    
    auto start = std::chrono::system_clock::now();

    for(int i = 0; i < n; i++)
    {
        q_arr[arr[i] % 10].push(arr[i]);    
    }
       
  //  for (int i = 0; i < 10; i++)
   // {
       // cout << "[" << i << "]" << endl;
  //      q_arr[i].print_q();
   // }
    
    //cout <<endl<<endl;
    
    // kolejne iteracja - dzialania na kolejkach
    int temp, temp2;
    range = max;
    for (int i = 1; i <= (range*10); i*=10)
    {
        for (int l = 0; l < 10; l++)
        {
            size[l] = q_arr[l].size();
        }
        
        for (int j = 0; j < 10; j++)
        {
            for (int k = 0; k < size[j]; k++)
            {
                temp = q_arr[j].pop();
                temp2 = temp;
                
                q_arr[(temp/i) % 10].push(temp2);
            }
            
        }
        
    }
    
	auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end-start;

	cout << n << " " << diff.count() << endl;

//    for (int i = 0; i < 10; i++)
//    {
//        cout << "[" << i << "]" << endl;
//        q_arr[i].print_q();
//    }
        
    //}  
    return 0;
}


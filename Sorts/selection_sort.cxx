#include <iostream>
#include <chrono>

using namespace std;

int main()
{
	int n, number, min, temp;
	int k = 0;
	cin >> n;
	cin >> n;
	
	int arr[n];

	for (int i = 0; i < n; i++)
	{	
		cin >> number;	
		arr [i] = number;
	}

	//Selection sort
	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < n - 1; i++)
	{	
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[min] > arr[j])
			{	
				min = j; 
			}
		}	
		
		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
		
	//	k++;
	}
	auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end-start;
	
	cout << n << " " << diff.count() << endl;

//	for (int i = 0; i < n; i++)
//		cout << arr[i] << endl;
}

#include <iostream>
#include <algorithm>
#include <array>
#include <chrono>

using namespace std;

int main()
{	
	int n, number;

	cin >> n;
	cin >> n;


	int arr[n];

	for (int i = 0; i < n; i++)
	{
		cin >> number;
		arr[i] = number;
	}

	auto start = std::chrono::system_clock::now();
	
	sort(arr, arr + n);

	auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end-start;
	
	cout << n << " " << diff.count() << endl;

//	for (int i = 0; i < n; i++)
//		cout << arr[i] << endl;

}

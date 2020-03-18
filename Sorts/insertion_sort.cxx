#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char** argv)
{
	int n = 1;
	cin >> n;	
	cin >> n;

	//int arr [n];
	int sort_arr [n];
	int temp;
	int number;

	cin >> number;
	//InsertionSort
	auto start = chrono::system_clock::now();
	sort_arr[0] = number;
	for (int i = 1; i < n ;i++)
	{
		cin >> number;

		if (number >= sort_arr[i - 1])
		{
			sort_arr[i] = number;
		}
	
		else
		{
			for (int j = i; j >= 0; j--)
			{
				sort_arr[j+1] = sort_arr[j];
			
				if (j == 0 || number >= sort_arr[j-1])
				{
					sort_arr[j] = number;
					break;
				}
			}
		}
	}

	auto end = chrono::system_clock::now();
        chrono::duration<double> diff = end-start;
	cout << n << " " << diff.count() << endl;

//	cout << "WYPIS" << endl;
//	for (int i = 0; i < n; i++)
//		cout << sort_arr[i] << endl;

return 0;
}

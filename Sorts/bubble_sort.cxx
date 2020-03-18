#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char** argv)
{
	int n = 1;
	cin >> n;	
	cin >> n;

	int arr [n];
	int temp;
	int number;

	for (int i = 0; i < n; i++)
	{
		cin >> number;
		arr[i] = number; 
	}

	//Bubble
//	cout << "bub\n";
	auto start = chrono::system_clock::now();
	for (int i = 0; i < n; i++)
		for (int j = n; j > 0; j--)
		{
//			cout <<"bul\n";
			if (arr[j-1] > arr[j])
			{
				temp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = temp;							
			}
		}
	auto end = chrono::system_clock::now();
        chrono::duration<double> diff = end-start;
	cout << n << " " << diff.count() << endl;
//	for (int i = 0; i < n; i++)
//		cout << arr[i] << endl;

}

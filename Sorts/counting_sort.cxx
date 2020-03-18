#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char** argv)
{
	int n = 1;
	int range = 1;
	
	cin >> range;	
	cin >> n;

	int arr [n];
	int counting_arr[range + 1];

	for (int i = 0 ; i < range + 1; i++)
	{
		counting_arr[i] = 0;
	}
	//...//
	int number;

	//Counting sort
	auto start = std::chrono::system_clock::now();

	for (int i = 0 ; i < n; i++)
	{
//		cout << "for1\n";	
		cin >> number;
		counting_arr[number]++;
	}

        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> diff = end-start;

	cout << n << " " << diff.count() << endl;

//WYPIS
/*	for (int i = 0; i < range + 1; i++)
	{
		while(counting_arr[i] != 0)
		{	
//			cout << "while\n";
			cout << i << endl;
			counting_arr[i]--;
		}
	}
*/
}

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cmath>

class Queue
{
	int arr_size;
	int *arr;
	int head; // the oldest element
	int tail; // the youngest element
	int current_size;

public:
	Queue() : arr_size(2500000), arr(new int [arr_size]), head(0), tail(0), current_size(0)
	{}

	Queue (int N) : arr_size(N), arr(new int [arr_size]), head(0), tail(0), current_size(0)
	{}	

	void push (int x)
	{
		if (current_size == arr_size)
		{
			std::cout << "Queue is full!" << std::endl;
			exit(-2);
		}	
		arr[tail] = x;
		//std::cout << "TAIL: " << tail << " ";
		tail++;

		if (tail == arr_size)
			tail = 0;
		
		current_size++;
	}

	int pop()
	{
		if (current_size == 0)
			std::cout << "EMPTY" << std::endl;
		
		int temp = arr[head];
	//	std::cout << "HEAD: " << head << " ";
		head++;
		
		if (head == arr_size)
			head = 0;
		
		current_size--;
		
		return temp;
	}

	int& front()
	{
		return arr[head];
	}

	int size()
	{
		return current_size;	
	}

	bool empty()
	{
		if (current_size  == 0)
			return true;

		return false;	
	}

        void print_q()
        {
            for (int i = 0; i < current_size; i++)
            {
                std::cout << arr[head + i] << "\n";
            }
        }
        
};

#endif


//       H x x x x T
//       . H x x x T
//       . . H x x T
//       T . H x x x

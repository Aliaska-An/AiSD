#include <iostream>
#include "Stack.cpp" 
using namespace std;
class Queue
{
public:
	char arr[size_1];//массив хранени€ данных
	int work[2];//массив состо€ни€
	void init()//инициализаци€ массива
	{
		for (int i = 0; i < size_1; i++)
			arr[i] = 0;
		work[0] = -1;
		work[1] = -1;
	}
	void push(char a)//помещение элемента в стек
	{
		if (work[1] != size_1 - 1)
		{
			if (work[0] == -1)
			{
				arr[0] = a;
				work[1] = 0;
				work[0] = 0;
			}
			else
			{
				arr[work[1] + 1] = a;
				work[1]++;
			}
		}
		else
			cout << "ќчередь переполнена." << endl;
	}
	bool can_pop()//возможно ли вз€ть
	{
		if (work[0] != -1)
			return 1;
		else
			return 0;
	}
	char pop()//вз€тие элемента из очереди
	{
		if (work[0] != -1)
		{
			if (work[0] != work[1])
			{
				char tmp = arr[work[0]];
				arr[work[0]] = 0;
				work[0]++;
				return tmp;
			}
			else
			{
				char tmp = arr[work[0]];
				arr[work[0]] = 0;
				work[0] = -1;
				work[1] = -1;
				return tmp;
			}
		}
		else
		{
			cout << "Ќе удалось извлечь элемент, очередь пуста." << endl;
			return 0;
		}
	}
	Queue()
	{
		init();
	}
};

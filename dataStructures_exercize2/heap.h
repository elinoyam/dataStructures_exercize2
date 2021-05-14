#pragma once
#include "dynamicArray.h"

typedef struct data {
	long int key;
	int index;
	DynamicArray<long int>* arr;

}Data;


class Heap
{
private:
	int pSize;
	int heapSize;
	Data* ptr;
	bool allocated;

	static int getLeft(int node);
	static int getRight(int node);
	static int getParent(int node);
	void FixHeap(int node);
	void Swap(Data& first, Data& second);

public:
	Heap(int maxSize);
	Heap(Data* arr, int size);
	~Heap();
	Data Min();
	Data deleteMin();
	void insert(Data& item);
	bool isEmpty();
};


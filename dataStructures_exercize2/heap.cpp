#include "heap.h"

int Heap::getLeft(int node) {
	return (2 * node + 1);
}

int Heap::getRight(int node) {
	return(2 * node + 2);
}

int Heap::getParent(int node) {
	return (node - 1) / 2;
}

void Heap::FixHeap(int node) {
	int min;
	int left = getLeft(node);
	int right = getRight(node);
	
	if (left < heapSize && ptr[left].key < ptr[node].key)
		min = left;
	else
		min = node;
	if (right < heapSize && ptr[right].key < ptr[min].key)
		min = right;

	if (min != node) {
		Swap(ptr[node], ptr[min]);
		FixHeap(min);
	}
}

void Heap::Swap(Data& first, Data& second) {
	Data temp = first;
	first = second;
	second = temp;
}


Heap::Heap(int maxSize):allocated(true),pSize(maxSize),heapSize(0) {
	ptr = new Data[pSize];
}

Heap::Heap(Data* arr, int size) : allocated(false),pSize(size),heapSize(size){
	///Floyd algorithm
	ptr = arr;

	for (int i = size / 2 - 1; i >= 0; i -- ) // size iterations
		FixHeap(i);

}
	
Heap::~Heap() {
	if (allocated)
		delete ptr;
	ptr = nullptr;
}

Data Heap::Min() {
	return ptr[0];
}

Data Heap::deleteMin() {
	if (heapSize < 1);
		// handle error
	Data min = ptr[0];
	heapSize--;
	ptr[0] = ptr[heapSize];
	FixHeap(0);
	return min;

}

void Heap::insert(Data& item) {
	if (heapSize == pSize);
		// handle error
	int i = heapSize;
	heapSize++;

	while ((i > 0) && ptr[getParent(i)].key > item.key) {
		ptr[i] = ptr[getParent(i)];
		i = getParent(i);
	}

	ptr[i] = item;
}

bool Heap::isEmpty() {
	return heapSize == 0;		// if the size of the heap is 0 then the heap is empty
}
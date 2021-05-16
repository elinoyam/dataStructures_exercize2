#include <iostream>
#include <fstream>
#include <string>
#include "dynamicArray.h"
#include "heap.h"
using namespace std;



// This function is getting all the needed input from the user so we could get and sort the data.
void getInputFromUser(int& n, int& k, string& inName, string& outName);
// This is partition function is for the quickSort function
int partition(DynamicArray<long int>& arr, int left, int right);
// This function is sorting a given array with the quick sort algorithm
// we'll use this function to sort every array with a size smaller then K
void quickSort(DynamicArray<long int>& arr, int left, int right);
// This function is to get the high and buttom complete values of n / k
// so we would know how many elements to put in each sub-array
void getCompleteValues(int n, int k, int& high, int& buttom);
// This function is diveding the given array to K sub-arrays, sort each of the sub-arrays
// and then merge them all together using heap to one result array in the right order
void kWayMerge(DynamicArray<long int>& arr, int n, int k);


void checkProgram(DynamicArray<long int>& arr, int size) {
	cout <<endl << "checking program.." << endl;
	for (int i = 0; i < size - 1; i++) {
		if (arr[i] > arr[i + 1])
			cout << "problem in: " << i << " and " << i + 1 << endl;
	}
}

int main() {
	
	int n, k;
	long int num;
	string inputName, outputName;
	ifstream inputFile;
	ofstream outputFile;
	
	
	try{
	getInputFromUser(n, k, inputName, outputName);
	DynamicArray<long int> arr(n);
	
	inputFile.open(inputName);

	for (int i = 0; i < n; i++) { //// read all the data
		inputFile >> num;
		arr.push_back(num);
	}
	
	inputFile.close();

	//// call the algorithm to sort the data
	kWayMerge(arr, n, k);
	outputFile.open(outputName);
	
	for (int i = 0; i < n; i++) { //// write the sorted data
		outputFile << arr[i] << endl;
	}
	outputFile.close();
	checkProgram(arr,n);
	} 	catch (invalid_argument e) {
		cout << "wrong input." << endl;
	}	catch (fstream::failure e) {
		cout << "wrong input." << endl;
	}


	return 0;
}


void getInputFromUser(int& n, int& k, string& inName, string& outName) {

	cout << "Please enter the number of elements to enter: " << endl;
	cin >> n;
	if (n < 0)
		throw invalid_argument("The number of elements must be a non-negative number.");

	cout << "Please enter the parameter K: " << endl;
	cin >> k;

	if (k <= 0)
		throw invalid_argument("The number of elements must be a positive number.");


	cout << "Please enter the name of the file of the input: " << endl;
	cin >> inName;
	cout << "Please enter the name of the file you want to get the sorted data into:" << endl;
	cin >> outName;

}

int partition(DynamicArray<long int>& arr, int left, int right) {
	int pivot = left;
	int index = right - 1, tmpIndex;
	long int temp;

	while (pivot != index) {
		if (pivot<index && arr[pivot] >arr[index]) {
			// swap numbers
			temp = arr[pivot];
			arr[pivot] = arr[index];
			arr[index] = temp;
			// swap indexes
			tmpIndex = pivot;
			pivot = index;
			index = tmpIndex + 1; // update to the next number in the array
		}
		else if (pivot > index && arr[pivot] < arr[index]) {
			// swap numbers
			temp = arr[pivot];
			arr[pivot] = arr[index];
			arr[index] = temp;
			// swap indexes
			tmpIndex = pivot;
			pivot = index;
			index = tmpIndex - 1; // update to the next number in the array
		}
		else if (pivot < index && arr[pivot] <= arr[index]) // no need to make a swap
			index--; // updating the index 
		else if (pivot > index && arr[pivot] >= arr[index])// no need to make a swap
			index++; // updating the index 
	} // exit while

	return pivot;
}

void quickSort(DynamicArray<long int>& arr, int left, int right) {
	int pivot;

	if (left < right) {							// there is still elements to sort
		pivot = partition(arr, left, right);
		quickSort(arr, left, pivot);			// sort the elements that are left to the pivot
		quickSort(arr, pivot + 1, right);		// sort the elements that are right to the pivot
	}
}

void kWayMerge(DynamicArray<long int>& arr, int n, int k) {

	if (n <= k || k==1) {					// need to sort the array with quick sort
		quickSort(arr, 0, arr.size());
	}
	else {
	
		Heap mergeHeap(k);
		int high, buttom, readIndex=0;
		getCompleteValues(n, k, high, buttom);

		DynamicArray<DynamicArray<long int>*> subArrays(k);

		for (int i = 0; i < k; i++) {
			subArrays[i] = new DynamicArray<long int>(high);
			for (int j = 0; j < buttom; j++) {
				subArrays[i]->push_back(arr[readIndex++]);
			}
		}
		int j = 0;
		while (readIndex < n && j<k) {
			subArrays[j]->push_back(arr[readIndex++]);
			j++;
		}

		for (int i = 0; i < k; i++) {		// split arr to k sub-arrays
			DynamicArray<long int>* subArr = subArrays[i];
			kWayMerge(*subArr, subArr->size(), k);		// recursive call on the sub-array
			// enter the sub-array to the merge heap :
			Data data;
			data.arr = subArr;
			data.index = 0;
			data.key = (*subArr)[0];
			mergeHeap.insert(data);						
		}

		arr.clear();
		// merge with the heap
		while (!mergeHeap.isEmpty()) {
			Data min = mergeHeap.deleteMin();
			arr.push_back(min.key);
			min.index++;
			if (min.index < min.arr->size()) {
				min.key = (*min.arr)[min.index];
				mergeHeap.insert(min);
			}
		}	

		//for (int i = 0; i < k; i++) 
		//	delete[] subArrays[i];
	
		
	}
}

void getCompleteValues(int n, int k, int& high, int& buttom) {
	if (n % k == 0) {
		high = buttom = n / k;
	}
	else {
		buttom = n / k;
		while (n % k != 0)
			n++;
		high = n / k;
	}
}
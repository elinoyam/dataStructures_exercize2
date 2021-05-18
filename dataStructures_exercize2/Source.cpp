#include "SourceHeader.h"

void getDataFromFile(string inputName, int n, DynamicArray<long int>& arr) {
	ifstream inputFile(inputName);
	long int num;

	for (int i = 0; i < n; i++) { //// read all the data
		string inp;
		getline(inputFile, inp);
		if (!checkIfNumber(inp))
			throw invalid_argument("wrong input.");

		num = atoi(inp.c_str());
		arr.push_back(num);
	}

	if (!inputFile.eof()) {		// check if there is any data in the file unread
		string checkEnd;
		getline(inputFile, checkEnd);	// check if not white space
		if (!inputFile.eof())
			throw invalid_argument("wrong input.");
	}

	inputFile.close();
}

bool checkIfNumber(string str) {
	if (str.empty())			// check that the file didn't end
		return false;
	int size = str.size();
	int i = 0;
	if (str[0] == '-')
		i++;
	for (; i < size; i++)			// check that all the chars are digits
		if (str[i] < '0' || str[i]>'9')
			return false;

	return true;
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
		int high, buttom;
		getCompleteValues(n, k, high, buttom);

		DynamicArray<DynamicArray<long int>*> subArrays(k);
		splitToSubaArrays(arr, subArrays, n, k, high, buttom);
		
		enterSubArraysToHeap(subArrays, n, k, mergeHeap);
		arr.clear();		// empty the array
		
		while (!mergeHeap.isEmpty()) {							// merge all the K sub-arrays to the main array using heap
			Data min = mergeHeap.deleteMin();	  // take out the current minimum value
			arr.push_back(min.key);				  // enter the min value to the main array
			min.index++;						  // update the index to the next in the sub-array
			if (min.index < min.arr->size()) {	  // if the index is still in the sub-array boundries
				min.key = (*min.arr)[min.index];  // update the key to the next element
				mergeHeap.insert(min);			  // re-insert the sub-array to the heap
			}
		}	
	}
}

void getCompleteValues(int n, int k, int& high, int& buttom) {
	if (n % k == 0) {				// if n is a multification of k
		high = buttom = n / k;
	}
	else {
		buttom = n / k;		// div
		high =  buttom + 1;
	}
}

void splitToSubaArrays(DynamicArray<long int>& arr, DynamicArray<DynamicArray<long int>*>& subArrays,int n, int k, int high, int buttom) {
	int readIndex = 0;
	for (int i = 0; i < k; i++) {			// allocate the sub-arrays and enter buttom complete values
		subArrays[i] = new DynamicArray<long int>(high);
		for (int j = 0; j < buttom; j++) {
			subArrays[i]->push_back(arr[readIndex++]);
		}
	}
	int j = 0;
	while (readIndex < n && j < k) {			// if there is any elements left, enter one element to each sub-array from the start until in ends
		subArrays[j]->push_back(arr[readIndex++]);
		j++;
	}
}

void enterSubArraysToHeap(DynamicArray<DynamicArray<long int>*>& subArrays, int n, int k, Heap& mergeHeap) {
	for (int i = 0; i < k; i++) {							// for each sub-array
		DynamicArray<long int>* subArr = subArrays[i];
		kWayMerge(*subArr, subArr->size(), k);				// recursive call on the sub-array
		// enter the sub-array to the merge heap :
		Data data;
		data.arr = subArr;
		data.index = 0;
		data.key = (*subArr)[0];
		mergeHeap.insert(data);
	}
}
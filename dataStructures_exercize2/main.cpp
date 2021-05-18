#include <iostream>
#include <fstream>
#include <string>
#include "dynamicArray.h"
#include "heap.h"
#include "SourceHeader.h"
using namespace std;


int main() {

	int n, k;
	string inputName, outputName;
	ofstream outputFile;

	try {
		getInputFromUser(n, k, inputName, outputName);

		DynamicArray<long int> arr(n);
		getDataFromFile(inputName, n, arr);

		kWayMerge(arr, n, k); //// call the algorithm to sort the data

							  //// write the sorted data
		outputFile.open(outputName);
		for (int i = 0; i < n; i++) {
			outputFile << arr[i] << endl;
		}
		outputFile.close();

	}
	catch (invalid_argument e) {
		cout << "wrong input." << endl;
	}
	catch (fstream::failure e) {
		cout << "wrong input." << endl;
	}

	return 0;
}

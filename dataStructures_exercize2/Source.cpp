#include <iostream>
#include <fstream>
#include <string>
using namespace std;



//This function is getting all the needed input from the user so we could get and sort the data.
void getInputFromUser(int& n, int& k, string& inName, string& outName);

int main() {
	
	int n, k;
	string inputName, outputName;
	ifstream inputFile;
	ofstream outputFile;

	try{
	getInputFromUser(n, k, inputName, outputName);
	inputFile.open(inputName);

	//// read all the data

	inputFile.close();

	//// call the algorithm to sort the data

	outputFile.open(outputName);

	//// write the sorted data

	outputFile.close();
	}
	catch (invalid_argument e) {
		cout << "We got an exception." << endl;
		cout << e.what() << endl;
	}


	return 0;
}

void getInputFromUser(int& n, int& k, string& inName, string& outName) {

	cout << "Please enter the number of elements to enter: " << endl;
	cin >> n;
	if (n <= 0)
		throw invalid_argument("The number of elements must be a positive number.");

	cout << "Please enter the parameter K: " << endl;
	cin >> k;

	if (k < 0)
		throw invalid_argument("The number of elements must be a non-negative number.");


	cout << "Please enter the name of the file of the input: " << endl;
	cin >> inName;
	cout << "Please enter the name of the file you want to get the sorted data into:" << endl;
	cin >> outName;

}
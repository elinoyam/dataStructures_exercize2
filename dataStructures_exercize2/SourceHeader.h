#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "dynamicArray.h"
#include "heap.h"
using namespace std;

// This function is getting all the needed input from the user so we could get and sort the data.
void getInputFromUser(int& n, int& k, string& inName, string& outName);
// This function reads all the numbers from the file, and checking that the data in the file is valid
void getDataFromFile(string inputName, int n, DynamicArray<long int>& arr);
// This function is checking that all the chars in the string is digits
// the function also checking that the file didn't end
bool checkIfNumber(string str);
// This is partition function is for the quickSort function
int partition(DynamicArray<long int>& arr, int left, int right);
// This function is sorting a given array with the quick sort algorithm
// we'll use this function to sort every array with a size smaller then K
void quickSort(DynamicArray<long int>& arr, int left, int right);
// This function is to get the high and buttom complete values of n / k
// so we would know how many elements to put in each sub-array
void getCompleteValues(int n, int k, int& high, int& buttom);
// This function splits the main array to K sub-arrays and enter ~n/k elements as needed
void splitToSubaArrays(DynamicArray<long int>& arr, DynamicArray<DynamicArray<long int>*>& subArrays, int n, int k, int high, int buttom);
// This function enters each of the sub arrays to the heap as Data
void enterSubArraysToHeap(DynamicArray<DynamicArray<long int>*>& subArrays, int n, int k, Heap& mergeHeap);
// This function is diveding the given array to K sub-arrays, sort each of the sub-arrays
// and then merge them all together using heap to one result array in the right order
void kWayMerge(DynamicArray<long int>& arr, int n, int k);

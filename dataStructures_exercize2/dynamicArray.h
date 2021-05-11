#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class DynamicArray
{
public:
	DynamicArray(int size = 2) :lSize(0), pSize(size), arr(new T[size]) {}
	DynamicArray(const DynamicArray& other) : arr(nullptr) { *this = other; }
	~DynamicArray() { delete[] arr; }
	int size()const { return lSize; }
	int capacity() const { return pSize; }
	bool isEmpty() const { return lSize == 0; }
	void clear() { lSize = 0; }
	const T& front() const { return arr[0]; }

	const DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			lSize = other.lSize;
			pSize = other.pSize;
			delete[] arr;
			try {
				arr = new T[pSize];
			}
			catch (bad_alloc& ba) {
				cout << ba.what() << "dynamic array h, line 27" << endl;
			}

			for (int i = 0; i < lSize; i++)
				arr[i] = other.arr[i];
		}
		return *this;
	}

	const T& operator[](int i) const { return arr[i]; }
	T& operator[](int i) { return arr[i]; }
	
	const T& at(int i) const;
	T& at(int i);
	void switchTwoIndexes(int firstIndex, int secondIndex);

	void push_back(const T& item) {
		if (lSize == pSize)
			resize();
		arr[lSize++] = item;
	}

	// method to (only) increase the physical size of the array to a wanted new size
	// the method doesn't make the physical size smaller!
	void resize(int newSize) {
		if (newSize > pSize) {
			pSize = newSize;
			T* temp = new T[pSize];
			for (int i = 0; i < lSize; i++)
				temp[i] = arr[i];

			delete[] arr;
			arr = temp;
		}

	}

	void print() const {
		for (int i = 0; i < lSize; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
	class const_iterator; // forward declaration
	class reverse_iterator; // forward declaration

	class iterator {
	public:
		// this is must have settings for iterator class - DON'T EARASE
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;


		iterator(DynamicArray& arr, int i) : a(&arr), index(i) {}
		iterator(const iterator& other) :a(other.a), index(other.index) {}
		const iterator& operator=(const iterator& other) {
			if (*this != other) {
				a = other.a;
				index = other.index;
			}

			return (*this);
		}

		bool operator==(const iterator& other) const {
			return ((a == other.a) && (index == other.index));
		}

		bool operator!=(const iterator& other) const {
			return !(*this == other);
		}

		T& operator*() {
			return a->arr[index];
		}
		T* operator->() {
			return &(a->arr[index]);
		}

		iterator& operator++() {
			++index;
			return *this;
		}
		iterator operator++(int) {
			iterator temp(*this);
			++index;
			return temp;
		}
		iterator& operator--() {
			--index;
			return *this;
		}
		iterator operator--(int) {
			iterator temp(*this);
			--index;
			return temp;
		}

	private:
		DynamicArray* a;
		int index;
		friend class const_iterator;
		friend class reverse_iterator;
		friend class DynamicArray;
	};

	class const_iterator {
	public:

		// this is must have settings for iterator class - DON'T EARASE
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;



		const_iterator(const DynamicArray& arr, int i) : a(&arr), index(i) {}
		const_iterator(const_iterator& other) : a(other.a), index(other.index) {}
		const_iterator(const iterator& other) : a(other.a), index(other.index) {}
		const_iterator& operator=(const iterator& other) {
			if (*this != other) {
				a = other.a;
				index = other.index;
			}

			return (*this);
		}

		bool operator==(const_iterator& other) const {
			return ((a == other.a) && (index == other.index));
		}

		bool operator!=(const_iterator& other) const {
			return !(*this == other);
		}

		const T& operator*() {
			return a->arr[index];
		}
		const T* operator->() {
			return &(a->arr[index]);
		}

		const_iterator& operator++() {
			++index;
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator temp(*this);
			++index;
			return temp;
		}
		const_iterator& operator--() {
			--index;
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator temp(*this);
			--index;
			return temp;
		}


	private:
		const DynamicArray* a;
		int index;

	};

	class reverse_iterator {
	public:

		// this is must have settings for iterator class - DON'T EARASE
		using iterator_category = std::bidirectional_iterator_tag;
		using different_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;



		reverse_iterator(const DynamicArray& arr, int i) : a(&arr), index(i) {}
		reverse_iterator(const iterator& other) : a(other.a), index(other.index) {}
		const reverse_iterator& operator=(const iterator& other) {
			if (*this != other) {
				a = other.a;
				index = other.index;
			}

			return (*this);
		}

		bool operator==(reverse_iterator& other) const {
			return ((a == other.a) && (index == other.index));
		}

		bool operator!=(reverse_iterator& other) const {
			return !(*this == other);
		}

		const T& operator*() {
			return a->arr[index];
		}
		const T* operator->() {
			return &(a->arr[index]);
		}

		reverse_iterator& operator++() {
			--index;
			return *this;
		}
		reverse_iterator operator++(int) {
			reverse_iterator temp(*this);
			--index;
			return temp;
		}
		reverse_iterator& operator--() {
			++index;
			return *this;
		}
		reverse_iterator operator--(int) {
			reverse_iterator temp(*this);
			++index;
			return temp;
		}

	private:
		DynamicArray* a;
		int index;
	};

	iterator begin() {
		return iterator(*this, 0);
	}
	iterator end() {
		return iterator(*this, lSize);
	}
	const_iterator cbegin() const { // to return const_iterator even if the array isn't const
		return const_iterator(*this, 0);
	}
	const_iterator cend() const { // to return const_iterator even if the array isn't const
		return const_iterator(*this, lSize);
	}
	const_iterator begin() const {
		return const_iterator(*this, 0);
	}
	const_iterator end() const {
		return const_iterator(*this, lSize);
	}
	reverse_iterator rbegin() {
		return reverse_iterator(*this, lSize);
	}
	reverse_iterator rend() {
		return reverse_iterator(*this, 0);
	}

	iterator& erase(iterator itr) {
		iterator temp = itr;
		++temp;
		return erase(itr, temp);
	}
	const iterator erase(const iterator& first, const iterator& last)
	{
		iterator tempFirst = first, tempLast = last;
		int count = 0;
		while (tempFirst != tempLast){
			tempFirst++;
			count++;
		}

		tempFirst = first;

		while (tempLast != end()){
			*tempFirst = *tempLast;
			tempFirst++;
			tempLast++;
		}
		lSize -= count;
		iterator returnItr = first;
		returnItr--;

		return returnItr;

	}

	void insert(const iterator& itr, const T& item) {
		if (lSize == pSize)
			resize();

		iterator itrEnd = end();
		iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
		while (itrCurrent != itr)
		{
			*itrCurrent = *itrPrev;
			itrCurrent = itrPrev--;
		}

		iterator p = itr;
		*p = item;
		++lSize;
	}

	//friend class const_iterator;
	//friend class reverse_iterator;
	//friend class iterator;

private:
	T* arr;
	int pSize;
	int lSize;

	void resize() {
		pSize *= 2;
		T* temp;
		try {
			temp = new T[pSize];
		}
		catch (bad_alloc& ba) {
			throw ba;
		}


		for (int i = 0; i < lSize; i++)
			temp[i] = arr[i];

		delete[] arr;
		arr = temp;
	}

};

template<class T>
const T& DynamicArray<T>::at(int i) const {
	if (0 <= i && i < lSize)
		return arr[i];
	else
		throw out_of_range("The given index is out of the array range.");
}

template<class T>
T& DynamicArray<T>::at(int i){

	if (0 <= i && i < lSize)
		return arr[i];
	else
		throw out_of_range("The given index is out of the array range.");
}

template <class T>
void DynamicArray<T>::switchTwoIndexes(int firstIndex, int secondIndex) {
	if (firstIndex >= lSize || secondIndex >= lSize)
		throw out_of_range("One or both of the given indexes is not in the array boundaries.");
	T temp = arr[firstIndex];
	arr[firstIndex] = arr[secondIndex];
	arr[secondIndex] = temp;
}
#ifndef Array_H
#define Array_H

#pragma warning(disable : 4996)
#include "Definitions.h"
#include <ostream>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

template <class T>
class Array
{
private:
	int physicalSize, logicalSize;
	char delimiter;
	T** arr;

public:
	Array(int size = 1, char delimiter = ' ');
	Array(const Array& other);
	~Array();

	const Array& operator=(const Array& other);
	const Array& operator+=(const T& newVal);

	const int& getLogSize() const;
	const int& getPhysicalSize() const;
	T getArrByIndex(const int& index);
	T** getArray();

	friend ostream& operator<<(ostream& os, const Array& arr)
	{
		for (int i = 0; , i < arr.logicalSize; i++)
			os << *(arr.arr[i]) << arr.delimiter;
	}

	void  Array<T>::allocateArray();
};


template<class T>
T Array<T>::getArrByIndex(const int& index)
{
	return *(arr[index]);
}

template<class T>
T** Array<T>::getArray()
{
	return arr;
}

template <class T>
Array<T>::Array(int size, char delimiter) :physicalSize(size), logicalSize(0), delimiter(delimiter)
{
	arr = new T*[physicalSize];//allocation for physicalSize of the class T array
}

template <class T>
Array<T>::Array(const Array& other)
{
	*this = other;//the object will now be the object other (will 'take' all of his var)!
}

template <class T>
Array<T>::~Array()
{
	for (int i = 0; i < logicalSize; i++)
		delete arr[i];
	delete[]arr;
	
}

template <class T>
const Array<T>& Array<T>:: operator=(const Array<T>& other)
{
	if (this != &other)//comparing address of objects--if its the same copy will be useless or its possible to make errors 
	{
		physicalSize = other.physicalSize;
		logicalSize = other.logicalSize;
		delimiter = other.delimiter;
		arr = new T*[physicalSize];//new allocate 
		for (int i = 0; i < logicalSize; i++)
			arr[i] = new T(*(other.arr[i]));//using operator = of product and copy c'tor
	}
	return *this;
}

template <class T>
const Array<T>& Array<T>:: operator+=(const T& newVal)
{
	allocateArray();
	arr[logicalSize] = new T(newVal);
	logicalSize++;
	
	return *this;
}

template<class T>
void  Array<T>::allocateArray()
{
	T** TempArray=NULL;
	if (logicalSize >= physicalSize)//need to increase the array size 
	{
		physicalSize*=2;
		TempArray = new T*[physicalSize];
		for (int i = 0; i < logicalSize; i++)		
			TempArray[i] = new T(*arr[i]);		

		for (int i = 0; i < logicalSize; i++)
			delete arr[i];
		delete[]arr;
		arr = TempArray;
	}
}

template<class T>
const int& Array<T>::getLogSize() const
{
	return logicalSize;
}

template<class T>
const int& Array<T>::getPhysicalSize() const
{
	return physicalSize;
}

#endif
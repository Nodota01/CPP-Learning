#include "pch.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>

using namespace std;


template<typename Object>
class Vector {
private:
	Object *object;
	int theSize;
	int theCapacity;
public:
	Vector(int initsize = 0) :theSize(initsize), theCapacity(initsize + SPARE_CAPACITY) {
		object = new Object[theCapacity];
	}
	Vector(const Vector &vec) :theSize(vec.theSize), theCapacity(vec.theCapacity), object(nullptr) {
		object = new Object[theCapacity];
		for (int i = 0; i < theSize; i++)
			object[i] = vec.object[i];
	}
	Vector & operator=(const Vector & vec) {
		Vector temp(vec);
		swap(*this, temp);
		return *this;
	}
	~Vector() {
		delete []object;
	}
	void reserve(int newCapacity) {
		if (newCapacity > theSize)
			return;
		Object *newArry = new Object[newCapacity];
		for (int i = 0; i < theSize; i++)
			newArry[i] = object[i];
		theCapacity = newCapacity;
		swap(object, newArry);
		delete[]newArry;
	}
	void resize(int newSize) {
		if (newSize > theCapacity)
			reserve(newSize * 2);
		theSize = newSize;
	}
	Object &operator[](int i) {
		return object[i];
	}
	const Object &operator[](int i) const {
		return object[i];
	}
	int size() {
		return theSize;
	}
	bool empty() {
		return theSize == 0;
	}
	void push_back(const Object &a) {
		if (theSize == theCapacity)
			reserve(theCapacity * 2 + 1);
		object[theSize++] = a;
	}
	void pop_back() {
		theSize--;
	}
	Object &front() {
		return object[0];
	}
	Object &back() {
		reutrn object[theSize - 1];
	}
	typedef Object* iterator;
	iterator begin() {
		return &object[0];
	}
	iterator end() {
		return &object[theSize];
	}
	static const int SPARE_CAPACITY = 16;
};

int main() {
	Vector<int> a(10);
	for (int i = 0; i < a.size(); i++)
		a[i] = i;
	for (Vector<int>::iterator it = a.begin(); it != a.end(); it++)
		cout << *it;
 	return 0;
}
#ifndef VECTOR_H
#define VECTOR_H


#include "Deque.h"
#include <string>
#include <iostream>


template<typename T>
class Vector
{
private:
	Deque<T> train;

public:
	void pop_back() {
		train.pop_back();
	}
	void push_back(const T& data) {
		train.push_back(data);
	}
	T& back() {
		return train.back();
	}
	bool empty() {
		return train.empty();
	}
	T& at(size_t index) {
		return train.at(index);
	}
	string toString() {
		return train.toString();
	}
	size_t size() {
		return train.size();
	}
	void deleteData() {
		train.deleteData();
	}
	int find(const T& data) {
		for (int i = train.getCapacity() - 1; i > (train.getCapacity() - this->size() - 1); i--) {
			if (this->at(i) == data) {
				return (i - (train.getCapacity() - 1)) * -1;
			}
		}
		return 100;
	}
};

#endif
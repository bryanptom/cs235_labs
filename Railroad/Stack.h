#ifndef STACK_H
#define STACK_H


#include "Deque.h"
#include <string>
#include <iostream>


template<typename T>
class Stack
{
private:
	Deque<T> stackhouse;

public:
	void pop_front() {
		stackhouse.pop_front();
	}
	void push_front(const T& data) {
		stackhouse.push_front(data);
	}
	T& front() {
		return stackhouse.front();
	}
	bool empty() {
		return stackhouse.empty();
	}
	T& at(size_t index) {
		return stackhouse.at(index);
	}
	string toString() {
		return stackhouse.toString();
	}
	size_t size() {
		return stackhouse.size();
	}
	void deleteData() {
		stackhouse.deleteData();
	}
	int find(const T& data) {
		for (unsigned int i = 0; i < this->size(); i++) {
			if (this->at(i) == data) {
				return i;
			}
		}
		return 100;
	}
};
#endif
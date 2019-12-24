#ifndef QUEUE_H
#define QUEUE_H


#include "Deque.h"
#include <string>
#include <iostream>


template<typename T>
class Queue
{
private:
	Deque<T> roundhouse;
public:
	void pop_front() {
		roundhouse.pop_front();
	}
	void push_back(const T& data) {
		roundhouse.push_back(data);
	}
	T& front() {
		return roundhouse.front();
	}
	bool empty() {
		return roundhouse.empty();
	}
	T& at(size_t index) {
		return roundhouse.at(index);
	}
	string toString() {
		return roundhouse.toString();
	}
	size_t size() {
		return roundhouse.size();
	}
	void deleteData() {
		roundhouse.deleteData();
	}
	int find(const T& data) {
		for (unsigned int i = 0; i < this->size(); i++) {
			if (this->at(i) == data) {
				return (this->size() - 1 - i);
			}
		}
		return 100;
	}
};

#endif // !QUEUE_H

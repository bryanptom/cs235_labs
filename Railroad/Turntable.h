#ifndef TURNTABLE_H
#define TURNTABLE_H

#include "Deque.h"
#include <string>
#include <iostream>
template <typename T>
class Turntable
{
private:
	Deque<T> turntable;

public:
	void push_front(const T& data) {
		if (turntable.size() == 0) {
			turntable.push_front(data);
		}
		else {
			cout << "Full sorry!" << endl;
		}
	}
	void pop_front() {
		turntable.pop_front();
	}
	T& front() {
		return turntable.front();
	}
	bool empty() {
		return turntable.empty();
	}
	string toString() {
		return turntable.toString();
	}
	size_t size() {
		return turntable.size();
	}
	void deleteData() {
		turntable.deleteData();
	}
};

#endif // !TURNTABLE_H

#ifndef DEQUE_H
#define DEQUE_H
#include "DequeInterface.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;


template<typename T>
class Deque :
	public DequeInterface<T>
{
private:
	int capacity;
	int num_items;
	int front_index;
	int rear_index;
	T *the_data;

public:
	Deque(void) :
		capacity(DEFAULT_CAPACITY),
		num_items(0),
		front_index(-1),
		rear_index(-1),
		the_data(new T[DEFAULT_CAPACITY]) {}
	
	void reserve() {
		int new_capacity = capacity * 2;
		T *new_data = (new T[new_capacity]);

		for (int i = 0; i < capacity; i++) {
			front_index++;
			if (front_index > capacity - 1) { front_index = 0; }
			new_data[i] = the_data[front_index];
		}
		front_index = capacity - 1;
		rear_index = - 1;

		capacity = new_capacity;
		delete[] the_data;
		the_data = new_data;
	}


	void push_front(const T& data) {
		if (front_index == -1) {
			front_index = 0;
			the_data[front_index] = data;
		}
		else {

//			if (front_index == rear_index - 1 || (front_index == capacity - 1 && rear_index == -1)) {
			if (num_items == capacity) {
				this->reserve();
			}
				front_index++;

				if (front_index > capacity - 1) {
					front_index = 0;
				}

				the_data[front_index] = data;

		}
		num_items++;
	}

	void push_back(const T& data){
		if (rear_index == -1) {
			rear_index = capacity - 1;
			the_data[rear_index] = data;
		}

		else {

			if (num_items == capacity) {
				this->reserve();
			}

			rear_index--;

			if (rear_index < 0) {
				rear_index = capacity - 1;
			}

			the_data[rear_index] = data;
		}

		num_items++;
	}

	void pop_front() {
		if (front_index == 0) {
			front_index = capacity - 1;
		}
		else if (front_index == -1) {
			front_index = capacity - 2;
		}
		else {
			front_index--;
		}
		num_items--;
	}

	void pop_back() {
		if (rear_index == capacity - 1) { rear_index = 0; }
		else if (rear_index == -1) { rear_index = 1; }
		else { rear_index++; }
		num_items--;

	}

	T& front() { 
		if (front_index != -1) {
			return the_data[front_index];
		}
		else {
			front_index = capacity - 1;
			return the_data[front_index];
		}
		
	}

	T& back() { return the_data[rear_index]; }

	size_t size() const { return num_items; }

	bool empty() const {
		if (num_items == 0) { return true; }
		else { return false; }
	}

	T& at(size_t index) { 
		return the_data[index];
	}

	string toString() const {
		int temp_front;
		if (front_index != -1) { temp_front = front_index; }
		else { temp_front = capacity - 1; }

		ostringstream output;
		for (int i = 0; i < num_items; i++) {
			output << to_string(the_data[temp_front]) << " ";
			if (temp_front == 0) {
				temp_front = capacity - 1;
			}
			else { temp_front--; }
		}

		return output.str();
	}
	void deleteData() {
		delete[] the_data;
	}
	int getCapacity() {
		return capacity;
	}
};


#endif

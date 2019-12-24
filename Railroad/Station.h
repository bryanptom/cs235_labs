#ifndef STATION_H
#define STACTION_H
#include "Turntable.h"
#include "Queue.h"
#include "Vector.h"
#include "Stack.h"
#include <sstream>

class Station
{
private:
	Turntable<unsigned int> turntable;
	Vector<unsigned int> train;
	Queue<unsigned int> roundhouse;
	Stack<unsigned int> stackhouse;

public:
	Station(void) :
		turntable(Turntable<unsigned int>()),
		train(Vector<unsigned int>()),
		roundhouse(Queue<unsigned int>()),
		stackhouse(Stack<unsigned int>()) {}

	string addStation(int car) {
		if (turntable.size() == 0) {
			turntable.push_front(car);
			return "OK";
		}
		else if (turntable.size() == 1) {
			return "Turntable occupied!";
		}
		else {
			return "Error";
		}
	}

	string addStack() {
		if (turntable.size() == 1) {
			stackhouse.push_front(turntable.front());
			turntable.pop_front();
			return "OK";
		}
		else if (turntable.size() == 0) {
			return "Turntable empty!";
		}
		else {
			return "Error";
		}
	}

	string addQueue() {
		if (turntable.size() == 1) {
			roundhouse.push_back(turntable.front());
			turntable.pop_front();
			return "OK";
		}
		else if (turntable.size() == 0) {
			return "Turntable empty!";
		}
		else {
			return "Error";
		}
	}

	string removeStation() {
		if (turntable.size() == 1) {
			train.push_back(turntable.front());
			turntable.pop_front();
			return "OK";
		}
		else if (turntable.size() == 0) {
			return "Turntable empty!";
		}
		else {
			return "Error";
		}
	}

	string removeQueue() {
		if (turntable.size() == 0) {
			if (roundhouse.size() > 0) {
				turntable.push_front(roundhouse.front());
				roundhouse.pop_front();
				return "OK";
			}
			else if (roundhouse.size() == 0) {
				return "Queue empty!";
			}
			else {
				return "Error";
			}
		}
		else if (turntable.size() == 1) {
			return "Turntable occupied!";
		}
		else {
			return "Error";
		}
	}

	string removeStack() {
		if (turntable.size() == 0) {
			if (stackhouse.size() > 0) {
				turntable.push_front(stackhouse.front());
				stackhouse.pop_front();
				return "OK";
			}
			else if (stackhouse.size() == 0) {
				return "Stack empty!";
			}
			else {
				return "Error";
			}
		}
		else if (turntable.size() == 1) {
			return "Turntable occupied!";
		}
		else {
			return "Error";
		}
	}

	string stationTop() {
		if (turntable.size() == 1) {
			return to_string(turntable.front());
		}
		else if (turntable.size() == 0) {
			return "Turntable empty!";
		}
		else {
			return "Error";
		}
	}

	string stackTop() {
		if (stackhouse.size() > 0) {
			return to_string(stackhouse.front());
		}
		else if (stackhouse.size() == 0) {
			return "Stack empty!";
		}
		else {
			return "Error";
		}
	}

	string queueTop() {
		if (roundhouse.size() > 0) {
			return to_string(roundhouse.front());
		}
		else if (roundhouse.size() == 0) {
			return "Queue empty!";
		}
		else {
			return "Error";
		}
	}

	string queueSize() {
		return to_string(roundhouse.size());
	}

	string stackSize() {
		return to_string(stackhouse.size());
	}


	string printTrain() {
		return train.toString();
	}

	string find(unsigned int car) {
		ostringstream out;
		if (train.find(car) != 100) { 
			out << "Train[";
			out << to_string(train.find(car));
			out << "]";
		}
		else if (stackhouse.find(car) != 100 ){
			out << "Stack[";
			out << to_string(stackhouse.find(car));
			out << "]";
		}
		else if (roundhouse.find(car) != 100) {
			out << "Queue[";
			out << to_string(roundhouse.find(car));
			out << "]";
		}
		else if (turntable.front() == car) {
			out << "Turntable";
		}
		else {
			out << "Not Found!";
		}
		return out.str();
	}

	void deleteAll() {
		train.deleteData();
		stackhouse.deleteData();
		roundhouse.deleteData();
		turntable.deleteData();
	}
	 

	
};

#endif
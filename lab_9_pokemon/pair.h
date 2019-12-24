#ifndef PAIR_H
#define PAIR_H

#include <sstream>
#include <string>

/*Pair struct holds two data elements of any type. Can be constructed with 
both data, only one, or zero. */

template <typename K, typename V>
struct Pair {
	K key;
	V value;
	Pair() {}
	Pair(K the_key) {
		key = the_key;
	}

	Pair (K the_key, V the_value) {
		key = the_key;
		value = the_value;
	}

	V getValue() const {
		return value;
	}

	K getKey() const {
		return key;
	}

	//string toString() const {
	//	ostringstream out;
	//	out << "Key: " << key << endl;
	//	out << "Value: " << value << endl;

	//	return out.str();
	//}

};

#endif
#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <cmath>
#include <sstream>
#include <iostream>
#include "HashMapInterface.h"
#include "pair.h"

#define DEFAULT_MAP_HASH_TABLE_SIZE	31
#define HASH_CONSTANT				3
#define LOAD_THRESHOLD				75

using namespace std;

template <typename K, typename V>
class HashMap : public HashMapInterface <K, V>
{
public:
	Pair<K, V>* table;
	size_t capacity = DEFAULT_MAP_HASH_TABLE_SIZE;

	HashMap() {
		table = new Pair<K, V>[capacity]();
	}

	//Read and write access for maps
	V& operator [](const K& key) {
		//gets a hash value using the provided formula
		int hashValue = getHashValue(key);

		//Check if the first entry is empty
		if (table[hashValue].getKey().length() == 0) {
			table[hashValue].key = key;
			return table[hashValue].value;
		}
		else {
			//Either replaces contents if an identical key is found or uses quadratic probing to find an empty index
			int counter = 1;
			int testValue = hashValue;
			while (table[testValue].getKey().length() != 0 && table[testValue].getKey() != key) {
				testValue = hashValue + ((int)pow(counter, 2)); 
				testValue = testValue % capacity;
				counter += 1;
			}
			//If matching key not found
			if (table[testValue].getKey().length() == 0) {
				table[testValue].key = key;
				return table[testValue].value;
			}
			//If matching key found
			else {
				return table[testValue].value;

			}
		}
	}

	//returns the number of entries in the match with keys matching item
	size_t count(const K& item) {
		size_t count = 0;
		for (unsigned int i = 0; i < capacity; i++) {
			if (table[i].getKey() == item) {
				count++;
			}
		}
		return count;
	}

	//Deletes data stored in the sets of a Pair<string, set> array.
	/*This is a pretty ugly solution to avoid memory leaks...I realized late that
	I should have used a double pointer array instead of a regular array, and at that point I either
	needed to rewrite big parts of the lab to adjust or do something like this to fix 
	the memory leaks. So I went with this. */
	void clearSets() {
		for (unsigned int i = 0; i < capacity; i++) {
			if (table[i].getKey().length() != 0) {
				table[i].value.clear();
			}
		}
	}

	//Deletes the table 
	void clear() {
		delete [] table; 
	}

	//Gets a hash value for a string according to the given formula
	int getHashValue(K s) const {
		long long value = 0;
		int count = 1;
		for (unsigned int i = 0; i < s.length(); i++) {
			value += s[i] * pow(HASH_CONSTANT, s.length() - 1 - i);
			count++;
		}
		return ((int) value % capacity);
	}
	//outputs the contents of the map	
	 string toString(void) const {
		ostringstream out;
		for (size_t i = 0; i < capacity; i++) {
			/*out << endl << "#" << i << " : ";*/
			if (table[i].getKey().length() != 0) {
				out << "   [" << i << ":" << table[i].getKey() << "->" << table[i].getValue() << "]" << endl;
			}
		}
		return out.str();
	}
	 //Gets the total number of items in the map
	 size_t size() const {
		 size_t count = 0;
		 for (size_t i = 0; i < capacity; i++) {
			 if (table[i].getKey().length() != 0) { count++; }
		 }
		 return count;
	 }

	 //Gets the maximum number of elements in the map
	 size_t max_size() const {
		 return capacity;
	 }

	 //friend insertion operator
	 friend std::ostream& operator<< (ostream& os, const HashMap& HashMap)
	 {
		 os << HashMap.toString();
		 return os;
	 }


};

#endif

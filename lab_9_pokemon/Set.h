#ifndef SET_H
#define SET_H

#include <string>
#include <sstream>
#include <iostream>

#include "BST.h"
#include "SetInterface.h"

/*Set is just a wrapper class using the BST class from last lab. 
It borrows most of it's functions from that class*/

template <typename T>
class Set: public SetInterface<T>
{
public:
	BST<T> tree;

	Set() {
		tree = BST<T>();
	}
	/** Inserts item into the set, if the container doesn't
		already contain an element with an equivalent value.
		@return: pair.first = pointer to item
				 pair.second = true if successfully inserted, else false. */
				 //virtual Pair<T*, bool> insert(const T& item) = 0;
	bool insert(const T& item) {
		return tree.addNode(item);
	}

	bool remove(const T& item) {
		return tree.removeNode(item);
	}

	/** Removes all items from the set. */
	void clear() {
		if (tree.getSize() > 0) {
			tree.clearTree();
		}
	}

	/** @return: the number of elements contained by the Set. */
	size_t size() const {
		return tree.getSize();
	}

	/** @return: return 1 if contains element equivalent to item, else 0. */
	size_t count(const T& item) {
		if (tree.addNode(item)) {
			tree.removeNode(item);
			return 1;
		}
		else {
			return 0;
		}
	}

	/** @return: string representation of items in Set. */
	string toString() const {
		return tree.getInOrder();
	}

	friend std::ostream& operator<< (ostream& os, const Set& set)
	{
		os << set.toString();
		return os;
	}

};


#endif
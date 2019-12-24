#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkedListInterface.h"
#include "Node.h"
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T>
{
public:
	Node<T>* first_item;



	LinkedList(Node<T>* first = NULL) {
		first_item = first;
	}

	//add a node with data to the front of the list
	void push_front(const T& data) {
		Node<T>* newItem = new Node<T>(data, first_item);
		first_item = newItem;
	}

	//remove the first node in the list
	void pop_front() { 
		Node<T>* toDelete = first_item;
		first_item = first_item->next;
		delete toDelete;
	}

	//return the data from the first node in list
	T& front() {
		return first_item->data;
	}

	//return true if the list is empty, false if it contains one or more nodes. 
	bool empty() const {
		if (first_item == NULL) { return true; }
		return false;
	}

	//remove all nodes with data matching the passed value
	void remove(const T& remove) {

		Node<T>* past_item = NULL;
		Node<T>* cur_item = first_item;

		while (cur_item != NULL) {

			if (cur_item->data == remove) {

				Node<T>* old;
				//Case: first item
				if (past_item == NULL) {
					
					//Case: only item
					if (cur_item->next == NULL) {
						old = cur_item;
						first_item = NULL;
						cur_item = NULL;
						delete old;
					}

					//Case: first of several items
					else if (cur_item->next != NULL) {
						old = first_item;
						first_item = cur_item->next;
						cur_item = first_item;
						delete old;
					}
				}
				//any non-first item
				else {
					old = cur_item;
					past_item->next = cur_item->next;
					Node<T>* Temp = cur_item->next;
					cur_item = Temp;
					delete old;
				}

			}
			else {
				//move past and cur_item to next spots on list
				past_item = cur_item;
				Node<T>* Temp = cur_item->next;
				cur_item = Temp;
			}

		}


	}

	/** Remove all Nodes from linked list */
	void clear() {
		Node<T>* cur_item = first_item;
		Node<T>* toDelete;
		while (cur_item->next != NULL) {
			toDelete = cur_item;
			cur_item = cur_item->next;
			
			delete toDelete;
		}
		delete cur_item;
		first_item = NULL;
	}

	/** Reverse Nodes in linked list */
	void reverse() {
		int listSize = this->size();
		T* dataList = new T[listSize];
		Node<T>* cur_item;

		//temporarily assign all data from the list to a seperate array
		for (int i = 0; i < listSize; i++) {
			cur_item = first_item;
			for (int j = 0; j < i ; j++) {
				Node<T>* temp = cur_item->next;
				cur_item = temp;
			}

			dataList[i] = cur_item->data;
		}
		//clear list
		this->clear();

		//recreate list from saved array, in reverse
		for (int i = 0; i < listSize; i++) {
			this->push_front(dataList[i]);
		}

		//delete temporary array
		delete[] dataList;
	}

	/** Return the number of nodes in the linked list */
	size_t size() const {
		if (this->empty() == 0) {
			size_t listSize = 0;
			Node<T>* cur_item = first_item;
			while (cur_item->next != NULL) {
				listSize++;
				cur_item = cur_item->next;
			}
			listSize += 1;
			return listSize;
		}
		else {
			return 0;
		}
	}

	/** Return contents of Linked List as a string */
	std::string toString() const {
		ostringstream out;
		Node<T>* cur_item = first_item;
		while (cur_item->next != NULL) {
			out << cur_item->data << " ";
			cur_item = cur_item->next;
		}
		out << cur_item->data;
		return out.str();
	}

	friend std::ostream& operator<< (ostream& os, const LinkedList<T>& linkedList)
	{
		os << linkedList.toString();
		return os;
	}
};

#endif


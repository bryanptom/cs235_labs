#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node {

	T data;
	Node* next;

	Node(const T imput_data, Node* next_item = NULL) {
		data = imput_data;
		next = next_item;
	}

	void setReference(Node* next_item) {
		next = next_item;
	}
};

#endif
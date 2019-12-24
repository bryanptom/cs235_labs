#ifndef NODE_H
#define NODE_H

using namespace std;

template<typename T>
struct Node {

	T data;
	Node* right;
	Node* left;

	Node(const T imput_data, Node* right_item = 0, Node * left_item = 0) {
		data = imput_data;
		right = right_item;
		left = left_item;
	}

	void setRight(Node* right_item) {
		right = right_item;
	}
	void setLeft(Node* left_item) {
		left = left_item;
	}
};

#endif
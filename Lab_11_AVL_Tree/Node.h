#ifndef NODE_H
#define NODE_H

using namespace std;

template<typename T>
struct Node {

	T data;
	Node* right;
	Node* left;
	Node* up;

	Node(const T imput_data, Node* right_item = 0, Node * left_item = 0) {
		data = imput_data;
		right = right_item;
		left = left_item;
		up = 0;
	}
	void setUp(Node* up_item) {
		up = up_item;
	}
	void setRight(Node* right_item) {
		right = right_item;
	}
	void setLeft(Node* left_item) {
		left = left_item;
	}
	int getHeight() {
		if (right == 0 && left == 0) {
			return 0;
		}
		else {
			int rightHeight = getHeight(right);
			int leftHeight = getHeight(left);

			if (rightHeight > leftHeight) {
				return rightHeight + 1;
			}
			else if (leftHeight <= rightHeight) {
				return leftHeight + 1;
			}
		}
	}

};

#endif
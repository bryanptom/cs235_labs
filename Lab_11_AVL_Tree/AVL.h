#ifndef BST_H
#define BST_H
#include "Node.h"
#include <string>
#include <sstream>
#include <iostream>
#include "AVLInterface.h"

using namespace std;

template <typename T>
class BST : public AVLInterface<T>
{
public:
	Node<T>* root;
	int num_items;

	BST(Node<T>* first = 0) {
		root = first;
		num_items = 0;
	}

	Node<T>* rotateLL(Node<T>* node) {
		Node<T>* left = node->left;
		node->left = left->right;
		left->right = node;
		cout << toString();
		if (getNodeAbove(root, node->data) == 0) {
			root = left;
			cout << toString();
		}
		else {

			if (left->data < getNodeAbove(root, node->data)->data) {
				getNodeAbove(root, node->data)->left = left;
			}
			else if (left->data > getNodeAbove(root, node->data)->data) {
				getNodeAbove(root, node->data)->right = left;
			}
		}
		cout << toString();
		return left;
	}

	Node<T>* rotateRR(Node<T>* node) {
		Node<T>* right = node->right;
		node->right = right->left;
		right->left = node;
		if (getNodeAbove(root, node->data) == 0) {
			root = right;
		}
		else {
			
			if (right->data < getNodeAbove(root, node->data)->data) {
				getNodeAbove(root, node->data)->left = right;
			}
			else if (right->data > getNodeAbove(root, node->data)->data) {
				getNodeAbove(root, node->data)->right = right;
			}
		}
		cout << toString();
		return right;
	}

	Node<T>* rotateRL(Node<T>* node) {
		Node<T>* right = node->right;
		node->right = rotateLL(right);
	//	right->left = node;
		cout << toString();
		return rotateRR(node);
	}

	Node<T>* rotateLR(Node<T>* node) {
		Node<T>* left = node->left;
		if (node->right == 0) {
			Node<T>* temp = node->left->right;
			node->left->right = node;
			if (getNodeAbove(root, node->data)->data > node->left->data) {
				getNodeAbove(root, node->data)->left = node->left;
			}
			node->left = temp;
			return node;
		}
		node->left = rotateRR(left);
		cout << toString();
//		left->right = node;
		//cout << toString();
		return rotateLL(node);
	}

	int heightDifference(Node<T>* node) {
		if (num_items == 1) {
			return 1;
		}
		if (node == 0) {
			return 0;
		}
		int left_height = getHeight(node->left);
		int right_height = getHeight(node->right);

		return left_height - right_height;
	}
	//bool adjustAll(Node<T>* node) {
	//	if (node->right != 0) {
	//		adjust(node->right);
	//	}
	//	if (node->left != 0) {
	//		adjust(node->left);
	//	}
	//	adjust(node);
	//	return true;
	//}

	void adjust(Node<T>* node) {
		if (node == 0) {
			return;
		}
		if (node->left != 0) { adjust(node->left); }
		if (node->right != 0) { adjust(node->right); }
		switch (heightDifference(node))
		{
		case 2:
		{
			//int leftLeftChild = node->left_->left_ ? node->left_->left_->height_ : 0;
			//int leftRightChild = node->left_->right_ ? node->left_->right_->height_ : 0;
			//cout << endl << (leftRightChild - leftLeftChild ? "Left-Right heavy" : "Left-Left heavy");
			if (heightDifference(node->left) < 0) rotateRR(node->left);
			rotateLL(node);
			return;
		}
		case -2:
		{
			//int rightLeftChild = node->right_->left_ ? node->right_->left_->height_ : 0;
			//int rightRightChild = node->right_->right_ ? node->right_->right_->height_ : 0;
			//cout << endl << (rightRightChild - rightLeftChild ? "Right-Left heavy" : "Right-Right heavy");
			if (heightDifference(node->right) > 0) rotateLL(node->right);
			rotateRR(node);
			return;
		}
		default:
			if (num_items == 1) {
				break;
			}
			else if (node->data == root->data) {
				break;
			}
			else {
				break;
			}
		}
	}
	bool addNode(const T& value) {
		if (num_items == 0) {
			Node<T>* newItem = new Node<T>(value);
			root = newItem;
			num_items++;
			return true;
		}
		
		else { return insert(root, value); }
	}

	bool insert(Node<T>* start, const T& value) {
		if (value > start->data) {
			if (start->right == 0) {
				start->setRight(new Node<T>(value));
				num_items++;
				adjust(root);
				return true;
			}
			else {
				return insert(start->right, value);
			}
		}
		else if (value < start->data) {
			if (start->left == 0) {
				start->setLeft(new Node<T>(value));
				num_items++;
				adjust(root);
				return true;
			}
			else {
				return insert(start->left, value);
			}
		}
		else {
			return false;
		}	
	}
	void deleteNodes(Node<T>* root) {
		if (root->right != 0) {
			deleteNodes(root->right);
		}
		if (root->left != 0) {
			deleteNodes(root->left);
		}
		delete root;
	}
	bool clearTree() {
		if (root != 0) {
			deleteNodes(root);
		}
		
		root = 0;
		num_items = 0;
		return true;
	}
	string getSize() const {
		return to_string(num_items);
	}
	Node<T>* getNodeAbove(Node<T>* root, const T& value) const {
		//cout << "left: " << root->left->data << " right: " << root->right->data << endl;
		if (root->data == value) {
			return 0;
		}
		if (root->right != 0) {
			//cout << root->right->data << " " << value << endl;
			if (root->right->data == value) {
				return root;
			}
		}
		if (root->left != 0) {
			if (root->left->data == value) {
				return root;
			}
		}
		if (root->right != 0 && getNodeAbove(root->right, value) != 0) {
			return getNodeAbove(root->right, value);
		}
		if (root->left != 0 && getNodeAbove(root->left, value) != 0) {
			return getNodeAbove(root->left, value);
		}
		else { 
			return 0; }
	}
	bool removeNode(const T& value) {
		Node<T>* toDelete;
		if (num_items == 0) {
			return false;
		}
		if (root->data == value) {
			if (root->left == 0 && root->right == 0) {
				delete root;
				root = 0;
			}
			else if (root->right == 0 && root->left != 0) {
				toDelete = root;
				root = root->left;
				delete toDelete;
			}
			else if (root->right != 0 && root->left == 0) {
				toDelete = root;
				root = root->right;
				delete toDelete;
			}
			else if (root->right != 0 && root->left != 0) {
				toDelete = root;
				if (root->left->right == 0) {
					root->left->right = root->right;
					root = root->left;
					delete toDelete;
				}
				else {
					Node<T>* toSwitch = root->left->right;
					Node<T>* aboveSwitch = root->left;
					while (toSwitch->right != 0) {
						aboveSwitch = toSwitch;
						toSwitch = toSwitch->right;
					}
					if (toSwitch->left != 0) {
						aboveSwitch->right = toSwitch->left;
					}
					else if (toSwitch->left == 0) {
						aboveSwitch->right = 0;
					}
					root->data = toSwitch->data;
					delete toSwitch;
				}
			}
			num_items--;
			if (num_items > 0) { 
				adjust(root->left); 
				adjust(root->right);
				
			}
			return true;
		}
		Node<T>* aboveNode = getNodeAbove(root, value);
		T saveValue;
		bool left = true;
		if (aboveNode == 0) {
			return false;
		}
		Node<T>* toRemove;
		if (aboveNode->left != 0 && aboveNode->left->data == value) {
			toRemove = aboveNode->left;
			left = true;
		}
		else {
			toRemove = aboveNode->right;
			left = false;
		}
		toDelete = toRemove;
		if (toRemove->left == 0 && toRemove->right == 0) {
			if (left) {
				aboveNode->left = 0;
			}
			else {
				aboveNode->right = 0;
			}
		}
		else if (toRemove->left == 0 && toRemove->right != 0) {
			if (left) {
				aboveNode->left = toRemove->right;
			}
			else {
				aboveNode->right = toRemove->right;
			}
		}
		else if (toRemove->left != 0 && toRemove->right == 0) {
			if (left) {
				aboveNode->left = toRemove->left;
			}
			else {
				aboveNode->right = toRemove->left;
			}
		}
		else if (toRemove->left != 0 && toRemove->right != 0) {
			if (toRemove->left->right == 0) {
				toRemove->left->right = toRemove->right;
				if (left) { aboveNode->left = toRemove->left; }
				else { aboveNode->right = toRemove->left; }
			}
			else if (toRemove->left->right != 0) {
				Node<T>* toSwitch = toRemove->left->right;
				Node<T>* aboveSwitch = toRemove->left;
				while (toSwitch->right != 0) {
					aboveSwitch = toSwitch;
					toSwitch = toSwitch->right;
				}
				if (toSwitch->left != 0) {
					aboveSwitch->right = toSwitch->left;
				}
				else if (toSwitch->left == 0) {
					aboveSwitch->right = 0;
				}
				toRemove->data = toSwitch->data;
				saveValue = toSwitch->data;

			}
		}
		delete toDelete;
		num_items--;
		if (aboveNode != 0) {
			if (aboveNode->right != 0) { adjust(aboveNode->right); }
			if (aboveNode->left != 0) { adjust(aboveNode->left); }
		}
		else {
			adjust(root);
		}
		return true;
	}
	string inOrder() {
		if (num_items == 0) {
			return "empty";
		}
		else {
			return outInOrder(root);
		}
	}
	string outInOrder(Node<T>* node)
	{
		ostringstream out;
		if (node == 0)
			return "";

		out << outInOrder(node->left);

		out << node->data << " ";

		out << outInOrder(node->right);

		return out.str();
	}
	
	int getHeight(Node<T>* node) const{
		if (node == 0) { return 0; }
		else {
			int leftHeight = getHeight(node->left);
			int rightHeight = getHeight(node->right);

			if (leftHeight > rightHeight) {
				return (leftHeight + 1);
			}
			else { return (rightHeight + 1); }
		}
	}
	string printLevel(Node<T>* root, int level) const {
		ostringstream out;
		if (root == 0) {
			return "";
		}
		else {
			if (level == 0) {
				out << root->data;
			}
			else if (level == 1) {
				if (root->left != 0) {
					out << root->left->data << " ";
				}
				else if (root->right != 0) {
					out << "_ ";
				}
				if (root->right != 0) {
					out << root->right->data << " ";
				}
				else if (root->left != 0){
					out << "_ ";
				}
			}
			else if (level > 1) {
				out << printLevel(root->left, level - 1) << printLevel(root->right, level - 1);
			}
		}
		return out.str();
	}

	string toString() const {
		ostringstream out;
		if (num_items == 0) { out << "empty" << endl; }
		else {
			out << endl;
			int height = getHeight(root);
			for (int i = 0; i < height; i++) {
				out << "  " << i+1 << ": ";
				out << printLevel(root, i) << endl;
			}

		}

		return out.str();
		
	}
};

#endif
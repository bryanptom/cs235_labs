#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "AVL.h"

using namespace std;



int main(int argc, char* argv[])
{
	//open input and output file streams
	if (argc < 3)
	{
		cerr << "Please provide name of input and output files";
		return 1;
	}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	AVL<int> intTree = AVL<int>();
	string mode = "";
	AVL<string> stringTree = AVL<string>();

	for (string line; getline(in, line);)
	{
		string item1, item2;
		if (line.size() == 0) continue;


		istringstream iss(line);

		iss >> item1;
		

		if (item1 == "INT") {
			out << item1 << " ";
			mode = "int";
			out << "true" << endl;
		}
		else if (item1 == "STRING") {
			out << item1 << " ";
			mode = "string";
			out << "true" << endl;
		}
		else if (item1 == "add") {
			iss >> item2;
			out << item1 << " " << item2 << " ";
			//add item 2 to the BST
			if (mode == "int") {
				if (intTree.addNode(stoi(item2))) {
					out << "true" << endl;
				}
				else {
					out << "false" << endl;
				}
			}
			else if (mode == "string") {
				if (stringTree.addNode(item2)) {
					out << "true" << endl;
				}
				else {
					out << "false" << endl;
				}
			}
		}
		else if (item1 == "remove") {
			iss >> item2;
			out << item1 << " " << item2 << " ";
			//remove item 2 from the BST
			if (mode == "int") {
				if (intTree.removeNode(stoi(item2))) {
					out << "true" << endl;
				}
				else {
					out << "false" << endl;
				}
			}
			else if (mode == "string") {
				if (stringTree.removeNode(item2)) {
					out << "true" << endl;
				}
				else {
					out << "false" << endl;
				}
			}
		}
		else if (item1 == "clear") {
			out << item1 << " ";
			if (mode == "int") {
				intTree.clearTree();
			}
			else if (mode == "string") {
				stringTree.clearTree();
			}
			out << "true" << endl;
		}
		else if (item1 == "size") {
			out << "size" << " ";
			//print the size of the BST
			if (mode == "int") {
				out << intTree.getSize() << endl;
			}
			else if (mode == "string") {
				out << stringTree.getSize() << endl;
			}
		}
		else if (item1 == "print") {
			out << "print: ";
			if (mode == "int") {
				out << intTree.toString();
			}
			else if (mode == "string") {
				out << stringTree.toString();
			}
		}
		else if (item1 == "find") {
			iss >> item2;
			out << item1 << " " << item2 << " ";
			if (mode == "int") {
				if (!intTree.addNode(stoi(item2))) {
					out << "found" << endl;
				}
				else {
					out << "not found" << endl;
					intTree.removeNode(stoi(item2));
				}
			}
			else if (mode == "string") {
				if (!stringTree.addNode(item2)) {
					out << "found" << endl;
				}
				else {
					out << "not found" << endl;
					stringTree.removeNode(item2);
				}
			}
		}
		else if (item1 == "tree") {
			if (mode == "int") {
				out << item1 << ": " << intTree.inOrder() << endl;
			}
			else if (mode == "string") {
				out << item1 << ": " << stringTree.inOrder() << endl;
			}
		}

	}
	intTree.clearTree();
	stringTree.clearTree();

	return 0;
} 
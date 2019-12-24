#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "LinkedList.h"

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

	//create LinkedList object to use throughout method
	LinkedList<string> linkedList = LinkedList<string>();
		
	
	// process input strings
	
	for (string line; getline(in, line);)
	{
		string item1, item2;
		if (line.size() == 0) continue;
		
		
		istringstream iss(line);
		
		iss >> item1;
		//out << "\n" << item1;
		try {

			//Call push_front to insert new items
			if (item1 == "Insert")
			{
				out << line << "\n";
				while (iss >> item2)
				{
					linkedList.push_front(item2);
				}
			}
			//output LinkedList
			else if (item1 == "PrintList") {
				try {
					out << item1 << " ";
					if (!linkedList.empty()) {
						out << linkedList << "\n";
					}
					else {
						throw 1;
					}
				}
				catch (...) {
					out << "Empty!" << "\n";
				}
			}
			//delete all items in linkedList
			else if (item1 == "Clear") {
				out << item1 << " ";
				linkedList.clear();
				out << "OK" << "\n";
			}

			//Pring True if the list is empty, false if it is not. 
			else if (item1 == "Empty") {
				out << item1 << " ";
				if (linkedList.empty()) {
					out << "true" << "\n";
				}
				else {
					out << "false" << "\n";
				}
			}

			//print the size of the list
			else if (item1 == "Size") {
				out << item1 << " ";
				if (!linkedList.empty()) {
					out << linkedList.size() << "\n";
				}
				else {
					out << "0" << "\n";
				}
			}

			//print the data from the first item in the list
			else if (item1 == "First") {
				try {
					out << item1 << " ";
					if (!linkedList.empty()) {
						out << linkedList.front() << "\n";
					}
					else {
						throw 1;
					}
				}
				catch (...) {
					out << "Empty!" << "\n";
				}
			}

			//delete the first item in the list
			else if (item1 == "Delete") {
				try {
					out << item1 << " ";
					if (!linkedList.empty()) {
						linkedList.pop_front();
						out << "OK" << "\n";
					}
					else {
						throw 1;
					}
				}
				catch (...) {
					out << "Empty!" << "\n";
				}
			}

			//remove all items matching the data provided
			else if (item1 == "Remove") {
				out << item1 << " ";
				iss >> item2;
				linkedList.remove(item2);
				out << item2 << "\n";
			}

			//reverse the order of nodes in the list
			else if (item1 == "Reverse") {
				try {
					out << item1 << " ";

					if (linkedList.size() < 1) {
						throw 1;
					}

					linkedList.reverse();
					out << "OK" << "\n";
				}
				catch (...) {
					out << "Empty!" << "\n";
				}
			}
		}
		catch (...) {
			cerr << "Input Processing Error";
		}
	}

	//clear the list to avoid memory links
	if (linkedList.size() != 0) {
		linkedList.clear();
	}
	return 0;
}
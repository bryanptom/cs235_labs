#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "quicksort.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

int main(int argc, char* argv[])
{
	//check for memory leaks
	VS_MEM_CHECK

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

	Quicksort<int> quicksort = Quicksort<int>();

	for (string line; getline(in, line);)
	{
		string item1, item2, item3, item4;
		istringstream iss(line);
		iss >> item1;
		out << item1;

		if (item1 == "QuickSort") {
			iss >> item2;
			quicksort.deleteTable();
			quicksort = Quicksort<int>(stoi(item2));
			out << " " << item2 << " OK" << endl;
		}
		else if (item1 == "Capacity") {
			out << " " << to_string(quicksort.capacity()) << endl;
		}
		else if (item1 == "Clear") {
			quicksort.clear();
			out << " OK" << endl;
		}
		else if (item1 == "AddToArray") {
			iss >> item2;
			quicksort.addElement(stoi(item2));
			out << item2;
			while (iss >> item3) {
				out << "," << item3;
				quicksort.addElement(stoi(item3));
			}
			out << " OK" << endl;
		}
		else if (item1 == "Size") {
			out << " " << to_string(quicksort.size()) << endl;
		}
		else if (item1 == "PrintArray") {
			out << " " << quicksort << endl;
		}
		else if (item1 == "MedianOfThree") {
			iss >> item2 >> item3;
			out << " " << item2 << "," << item3 << " = " << quicksort.medianOfThree(stoi(item2), stoi(item3)) << endl;
		}
		else if (item1 == "Partition") {
			iss >> item2 >> item3 >> item4;
			out << item2 << "," << item3 << "," << item4 << " = " << quicksort.partition(stoi(item2), stoi(item3), stoi(item4)) << endl;
		} 
		else if (item1 == "SortAll") {
			quicksort.resetStats();
			out << " ";
			if (quicksort.sortAll()) {
				out << "OK" << endl;
			}
			else {
				out << "ERROR" << endl;
			}
		}
		else if (item1 == "Sort") {
			quicksort.resetStats();
			iss >> item2 >> item3;
			if (quicksort.sort(stoi(item2), stoi(item3))) {
				out << " " << item2 << "," << item3 << " OK" << endl;
			}
			else {
				out << " " << item2 << "," << item3 << " ERROR" << endl;
			}
		}
		else if (item1 == "Stats") {
			out << " " << quicksort.getStats() << endl;
		}
	}
	quicksort.deleteTable();
	return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Station.h"

using namespace std;

int main(int argc, char* argv[])
{
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

	string line, command;
	string car_num;
	Station station = Station();

	while (getline(in, line)) {
		istringstream iss(line);
		if (line == "") {
			continue;
		}
		else {
			iss >> command;
			if (command == "Add:station") {
				iss >> car_num;
				out << "Add:station " << car_num << " " << station.addStation(stoi(car_num)) << endl;
			}
			else if (command == "Add:queue") {
				out << "Add:queue " << station.addQueue() << endl;
			}
			else if (command == "Add:stack") {
				out << "Add:stack " << station.addStack() << endl;
			}
			else if (command == "Remove:station") {
				out << "Remove:station " << station.removeStation() << endl;
			}
			else if (command == "Remove:stack") {
				out << "Remove:stack " << station.removeStack() << endl;
			}
			else if (command == "Remove:queue") {
				out << "Remove:queue " << station.removeQueue() << endl;
			}
			else if (command == "Train:") {
				out << "Train:   " << station.printTrain() << endl;
			}
			else if (command == "Top:station") {
				out << "Top:station " << station.stationTop() << endl;
			}
			else if (command == "Top:queue") {
				out << "Top:queue " << station.queueTop() << endl;
			}
			else if (command == "Top:stack") {
				out << "Top:stack " << station.stackTop() << endl;
			}
			else if (command == "Size:stack") {
				out << "Size:stack " << station.stackSize() << endl;
			}
			else if (command == "Size:queue") {
				out << "Size:queue " << station.queueSize() << endl;
			}
			else if (command.substr(0, 4) == "Find") {
				out << command << " " << station.find(stoi(command.substr(5, 1))) << endl;
			}
		}

	}
	station.deleteAll();

	return 0;
}
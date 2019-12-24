#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Maze.h"

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
	string line;
	getline(in, line);
	istringstream iss(line);
	string height;
	string width;
	string num_layers;

	iss >> height >> width >> num_layers;

	Maze maze = Maze(stoi(height), stoi(width), stoi(num_layers));

	//while (getline(in, line)) {
	//	
	//}
	for (int i = 0; i < stoi(num_layers); i++) {
		getline(in, line);
		for (int j = 0; j < stoi(height); j++) {
			getline(in, line);
			istringstream row(line);
			for (int k = 0; k < stoi(width); k++) {
				string value;
				row >> value;
				maze.setValue(j, k, i, stoi(value));
			}
		}
		
	}

	out << "Solve Maze:" << endl << maze.toString() << endl;
	
	if (maze.find_maze_path()) {
		out << "Solution:" << endl << maze.toString()<< endl;
	}
	else {
		out << "No Solution Exists! " << endl;
	}
	maze.deleteMaze();


	return 0;
}


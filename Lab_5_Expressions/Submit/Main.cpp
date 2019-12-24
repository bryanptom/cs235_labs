#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ExpressionManager.h"

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

	
	string line, command, expres;
	while (getline(in, line))
	{
		ExpressionManager* expression = new ExpressionManager();
		try
		{
			if (line.size() == 0) continue;
			istringstream iss(line);
			iss >> command;
			if (command == "Expression:")
			{
				string expres = line.substr(command.length() + 1);
				expression->setExpression(expres);
				out << "Expression: " << expres << endl;
			}

			else if (command == "Infix:") {
				out << "Infix: " << expression->infix() << endl;
			}

			else if (command == "Postfix:") {
				out << "Postfix: " << expression->postfix() << endl;
			}
		}
		catch (std::exception& e)
		{
			out << e.what() << endl;
		}
		expression->~ExpressionManager();
	}
	
	return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "Set.h"
#include "pair.h"
#include "HashMap.h"

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

	enum effect { non, normal, super };

	//Initiallize all needed sets and hashmaps
	Set<string> mainset = Set<string>(); //use for the Set command
	Set<string> set = Set<string>(); //used for creating entries in the effectives and ineffectives maps
	HashMap<string, string> pokemon = HashMap<string, string>(); //stores pokemon and their types
	HashMap<string, string> moves = HashMap<string, string>(); //stores moves and their types
	HashMap<string, Set<string>> effectives = HashMap<string, Set<string>>(); //stores types and sets of other types they are effective against
	HashMap<string, Set<string>> ineffectives = HashMap<string, Set<string>>(); //stores types and sets of other types they are ineffective against

	for (string line; getline(in, line);)
	{
		string item1, item2, item3;
		istringstream iss(line);
		iss >> item1;

		//set command-- inserts each object into a new version of Mainset 
		if (item1 == "Set:") {
			mainset.clear();
			mainset = Set<string>();
			while (iss >> item2) {
				mainset.insert(item2);
			}
			out << line << endl;
			out << "   [" << mainset.toString() << "]" << endl;
		}

		//Pokemon command -- creates a new entry or updates an existing entry in Pokemon
		else if (item1 == "Pokemon:") {
			iss >> item2;
			iss >> item3;
			pokemon[item2] = item3;
			out << line << endl;
			cout << pokemon.toString() << endl;
		}

		//Effective -- creates a new or updates an existing entry in Effective
		else if (item1 == "Effective:") {
			set = Set<string>();
			iss >> item2;
			while (iss >> item3) {
				set.insert(item3);
			}
			out << line << endl;
			Set<string> toclear = effectives[item2]; //Need this bit to avoid memory leaks when updating an entry
			toclear.clear();
			effectives[item2] = set;
		}

		//Ineffective -- creates a new or updates an existing entry in ineffective
		else if (item1 == "Ineffective:") {
			set = Set<string>();
			iss >> item2;
			while (iss >> item3) {
				set.insert(item3);
			}
			out << line << endl;
			Set<string> toclear = ineffectives[item2]; //Need this bit to avoid memory leaks when updating an entry
			toclear.clear();
			ineffectives[item2] = set;
		}

		//Move -- Creates or updates entry in Moves
		else if (item1 == "Move:") {
			iss >> item2;
			iss >> item3;
			moves[item2] = item3;
			out << line << endl;
			//cout << moves.toString() << endl;
		}

		//Prints the respective maps
		else if (item1 == "Pokemon") {
			out << "Pokemon: " << pokemon.size() << "/" << pokemon.max_size() << endl;
			out << pokemon.toString();
		}
		else if (item1 == "Moves") {
			out << "Moves: " << moves.size() << "/" << moves.max_size() << endl;
			out << moves.toString();
		}
		else if (item1 == "Effectivities") {
			out << "Effectivities: " << effectives.size() << "/" << effectives.max_size() << endl;
			out << effectives.toString();
		}
		else if (item1 == "Ineffectivities") {
			out << "Ineffectivities: " << ineffectives.size() << "/" << ineffectives.max_size() << endl;
			out << ineffectives.toString();
		}

		//Battle: Determines effectiveness of each pokemon's attack and compares the two to determine a winnner
		else if (item1 == "Battle:") {
			effect a, b;
			out << line << endl;
			string name1, move1, name2, move2;
			iss >> name1 >> move1 >> name2 >> move2;
			out << name1 << " (" << move1 << ") vs " << name2 << " (" << move2 << ")" << endl;
			out << name1 << " is a " << pokemon[name1] << " type Pokemon." << endl;
			out << name2 << " is a " << pokemon[name2] << " type Pokemon." << endl;
			out << move1 << " is a " << moves[name1] << " type move." << endl;
			out << move2 << "is a " << moves[name2] << " type move." << endl;
			
			//Testing if types are found in each map to determine a move's effectiveness
			if (!effectives[moves[move1]].insert(pokemon[name2])) {
				a = super;
			}
			else if (!ineffectives[moves[move1]].insert(pokemon[name2])) {
				a = non;
				effectives[moves[move1]].remove(pokemon[name2]);
			}
			else {
				effectives[moves[move1]].remove(pokemon[name2]);
				ineffectives[moves[move1]].remove(pokemon[name2]);
				a = normal;
			}
			if (!effectives[moves[move2]].insert(pokemon[name1])) {
				b = super;
			}
			else if (!ineffectives[moves[move2]].insert(pokemon[name1])) {
				b = non;
				effectives[moves[move2]].remove(pokemon[name1]);
			}
			else {
				effectives[moves[move2]].remove(pokemon[name1]);
				ineffectives[moves[move2]].remove(pokemon[name1]);
				b = normal;
			}

			out << move1 << " is super effective against " << effectives[moves[move1]] << endl;
			out << move1 << " is ineffective against " << ineffectives[moves[move1]] << endl;
			out << name1 << "'s " << move1 << " is ";
			if (a == super) { out << "super effective against "; }
			else if (a == normal) { out << "effective against "; }
			else { out << "ineffective against "; }
			out << name2 << endl;

			out << move2 << " is super effective against " << effectives[moves[move2]] << endl;
			out << move2 << " is ineffective against " << ineffectives[moves[move2]] << endl;
			out << name2 << "'s " << move2 << " is ";
			if (b == super) { out << "super effective against "; }
			else if (b == normal) { out << "effective against "; }
			else { out << "ineffective against "; }
			out << name1 << endl;

			if (a != b) {
				out << "In the battle between " << name1 << " and " << name2 << ", ";
				if (a > b) {
					out << name1 << " wins!" << endl;
				}
				else {
					out << name2 << " wins!" << endl;
				}
			}

			else {
				out << "The battle between " << name1 << " and " << name2 << " is a tie." << endl;
			}
			

		}


	}
	//Clears data to avoid memory leaks
	for (unsigned int i = 0; i < effectives.max_size(); i++) {
		effectives.table[i].value.clear();
	}
	for (unsigned int i = 0; i < ineffectives.max_size(); i++) {
		ineffectives.table[i].value.clear();

	}
	moves.clear();
	pokemon.clear();
	mainset.clear();
	ineffectives.clearSets();
	effectives.clearSets();
	ineffectives.clear();
	effectives.clear();
	return 0;
}
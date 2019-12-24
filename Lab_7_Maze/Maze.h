#ifndef MAZE_H
#define MAZE_H
#include "MazeInterface.h"

#include <sstream>
#include <string>
#include <iostream>

using namespace std;

class Maze :
	public MazeInterface
{
private:
	int maze_height;
	int maze_layers;
	int maze_width;
	int*** maze;

public:
	//Maze() {}
	enum CellValue { OPEN, BLOCKED, PATH, EXIT, TEMP, RIGHT, LEFT, UP, DOWN, OUT, IN };

	Maze(int height, int width, int layer) :
		maze_height(height), 
		maze_layers(layer),
		maze_width(width) {
			
		//allocate memory for maze
		maze = new int**[layer];
		for (int i = 0; i < layer; i++) {
			maze[i] = new int*[height];
			for (int j = 0; j < height; j++) {
				maze[i][j] = new int[width];
			}
		}
	}
	
	//~Maze(void) {}

	/** Set maze value
	   @parm height
	   @parm width
	   @parm layer
	   @parm value
	*/
	void setValue(int height, int width, int layer, int value) {
		maze[layer][height][width] = value;
	}

	/** Solve maze
	   @return true if solveable, else false
	*/
	bool solveMaze(int height, int width, int layers) {
		
		if (height < 0 || height > maze_height - 1 || width < 0 || width > maze_width - 1 || layers < 0 || layers > maze_layers - 1) {
			return false;
		}
		if (maze[layers][height][width] != OPEN) {
			return false;
		}
		if (height == maze_height - 1 && width == maze_width - 1 && layers == maze_layers - 1) {
			maze[layers][height][width] = EXIT;
			return true;
		}
		maze[layers][height][width] = PATH;
		// left
		if (solveMaze(height, width - 1, layers) == true) {
			maze[layers][height][width] = LEFT;
			return true;
		}
		// right
		if (solveMaze(height, width + 1, layers) == true) {
			maze[layers][height][width] = RIGHT;
			return true;
		}
		// up
		if (solveMaze(height - 1, width, layers) == true) {
			maze[layers][height][width] = UP;
			return true;
		}
		// down 
		if (solveMaze(height + 1, width, layers) == true) {
			maze[layers][height][width] = DOWN;
			return true;
		}
		// out 
		if (solveMaze(height, width, layers - 1) == true) {
			maze[layers][height][width] = OUT;
			return true;
		}
		// in
		if (solveMaze(height, width, layers + 1) == true) {
			maze[layers][height][width] = IN;
			return true;
		}
	
		maze[layers][height][width] = TEMP;
		return false;
	}

	bool find_maze_path() {
		if (this->solveMaze(0, 0, 0) == false) {
			return false;
		}

		for (int i = 0; i < maze_layers; i++) {
			for (int j = 0; j < maze_height; j++) {
				for (int k = 0; k < maze_width; k++) {
					if (maze[i][j][k] == TEMP) { this->setValue(j, k, i, OPEN); }
				}
			}
		}
		return true;
	}

	string charDict(int value) const {
		if (value == PATH) {return "2";}
		else if (value == EXIT) { return "E"; }
		else if (value == RIGHT) { return "R"; }  
		else if (value == LEFT) { return "L"; }
		else if (value == UP) { return "U"; }
		else if (value == DOWN) { return "D"; }
		else if (value == OUT) { return "O"; }
		else if (value == IN) { return "I"; }
		else { return "??????"; }
	}

	/** Output maze (same order as input maze)
	  @return string of 2D layers
	*/
	string toString(void) const {
		ostringstream output;
		for (int i = 0; i < maze_layers; i++) {
			output << "Layer " << to_string(i + 1) << endl;
			for (int j = 0; j < maze_height; j++) {
				for (int k = 0; k < maze_width; k++) {
					if (maze[i][j][k] == OPEN) {
						output << "_" << " ";
					}
					else if (maze[i][j][k] == BLOCKED) {
						output << "X" << " ";
					}
					else if (maze[i][j][k] > 1) {
						output << this->charDict(maze[i][j][k]) << " ";
					}
				}
				output << endl;
			}
		}
		return output.str();
	}

	void deleteMaze(void) {
		for (int i = 0; i < maze_layers; i++) {
			for (int j = 0; j < maze_height; j++) {
				delete [] maze[i][j];
			}
			delete [] maze[i];
		}
		delete [] maze;
	}
};

#endif
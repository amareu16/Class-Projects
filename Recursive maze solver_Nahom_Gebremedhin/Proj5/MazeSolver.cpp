//MazeSolver.cpp

#include "MazeSolver.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace std;

//default constructor
MazeSolver::MazeSolver() {
	setMaze("Not Found");
}


MazeSolver::MazeSolver(string maze_data) {
	setMaze(maze_data);
}


//Gets the data from the txt file.
void MazeSolver::setMaze(string maze_data) {

	if (maze_data == "Not Found") {
		cout << "Please input valid txt file" << endl;

		return;
	}

	//open the file
	ifstream inFile(maze_data);
	string line;
	
	if (!inFile) {
		cout << "Could not open file" << endl;
		return;
	}

	inFile >> col;
	inFile >> row;

	//initialize the vector with the row and col size that is included in the file and set all data to char a
	vect.resize(row, vector<char>(col, 'a'));

	inFile.ignore();

	//count_row is used to locate the row value of mario
	int count_row = 0;
	while (getline(inFile, line)) {

		//the loop is used to set each vector data to the character that is in the file
		//the string is placed in the variable line and then iterate through the string to get the character
		for (int i = 0; i < line.length(); i++) {

			vect[count_row][i] = line[i];

			//This is used to get the coordinates of mario and save it to his own variable
			if (line[i] == 'M') {
				mario_row = count_row;
				mario_col = i;
			}

			//This is used to get the coordinates of peach and save it to her own variable
			if (line[i] == 'P') {
				peach_row = count_row;
				peach_col = i;
			}
		}
		count_row++;
	}

	//print();
}

void MazeSolver::goNorth(int curr_row, int curr_col, bool& rescue) {

	//going up or down depends on the row value, to go up, you have to decrement row.
	//the conditional statement makes sures that the current position is not the border.
	if ((curr_row - 1) >= 0) {

		//the conditional statement checks if going up is peach, so we should set it to true
		if (vect[curr_row - 1][curr_col] == 'P' && rescue == false) {
			rescue = true;
		}

		//if it is not peach, we should move. 
		else if (vect[curr_row - 1][curr_col] == ' ' && rescue == false) {
			curr_row = curr_row - 1;
			vect[curr_row][curr_col] = '?';

			//going North is the initial movement, then east, then west.
			goNorth(curr_row, curr_col, rescue);
			if (rescue == false) {
				goEast(curr_row, curr_col, rescue);
			}
			if (rescue == false) {
				goWest(curr_row, curr_col, rescue);
			}
			if (rescue == false) {
				//Once North is done, we cannot move south without going back to the position that initiated this so set it to '*' before going south
				vect[curr_row][curr_col] = '*';
				goSouth(curr_row, curr_col, rescue);
			}
		}
	}
	else {
		rescue = false;
	}
}

void MazeSolver::goSouth(int curr_row, int curr_col, bool& rescue) {

	//going up or down depends on the row value, to go up, you have to increment row.
	//the conditional statement makes sures that the current position is not the border.
	if ((curr_row + 1) < row) {

		//the conditional statement checks if going down is peach, so we should set it to true
		if (vect[curr_row + 1][curr_col] == 'P' && rescue == false) {
			rescue = true;
		}

		//if it is not peach, we should move. 
		else if (vect[curr_row + 1][curr_col] == ' ' && rescue == false) {
			curr_row = curr_row + 1;
			vect[curr_row][curr_col] = '?';

			//going South is the initial movement, then east, then west.
			goSouth(curr_row, curr_col, rescue);
			if (rescue == false) {
				goEast(curr_row, curr_col, rescue);
			}
			if (rescue == false) {
				goWest(curr_row, curr_col, rescue);
			}
			if (rescue == false) {
				
				//Once South is done, we cannot move north without going back to the position that initiated this so set it to '*' before going north
				vect[curr_row][curr_col] = '*';
				goNorth(curr_row, curr_col, rescue);
			}
		}
	}
	else {
		rescue = false;
	}
}

void MazeSolver::goWest(int curr_row, int curr_col, bool& rescue) {
	
	//going left or right depends on the col value, to go left, you have to decrement col.
	//the conditional statement makes sures that the current position is not the border.
	if ((curr_col - 1) >= 0) {

		//the conditional statement checks if going left is peach, so we should set it to true
		if (vect[curr_row][curr_col - 1] == 'P' && rescue == false) {
			rescue = true;
		}

		//if it is not peach, we should move.
		else if (vect[curr_row][curr_col - 1] == ' ' && rescue == false) {
			curr_col = curr_col - 1;
			vect[curr_row][curr_col] = '?';

			//going West is the initial movement, then south, then north.
			goWest(curr_row, curr_col, rescue);
			if (rescue == false) {
				goSouth(curr_row, curr_col, rescue);
			}
			if (rescue == false) {
				goNorth(curr_row, curr_col, rescue);
			}
			if (rescue == false) {
				
				//Once West is done, we cannot move east without going back to the position that initiated this so set it to '*' before going east
				vect[curr_row][curr_col] = '*';
				goEast(curr_row, curr_col, rescue);
			}
		}
	}
	else {
		rescue = false;
	}
}

void MazeSolver::goEast(int curr_row, int curr_col, bool& rescue) {
	
	//going left or right depends on the col value, to go left, you have to increment col.
	//the conditional statement makes sures that the current position is not the border.
	if ((curr_col + 1) < col) {

		//the conditional statement checks if going right is peach, so we should set it to true
		if (vect[curr_row][curr_col + 1] == 'P' && rescue == false) {
			rescue = true;
		}

		//if it is not peach, we should move.
		else if (vect[curr_row][curr_col + 1] == ' ' && rescue == false) {
			curr_col = curr_col + 1;
			vect[curr_row][curr_col] = '?';

			//going East is the initial movement, then south, then north.
			goEast(curr_row, curr_col, rescue);
			if (rescue == false) {
				goSouth(curr_row, curr_col, rescue);
			}
			if (rescue == false) {
				goNorth(curr_row, curr_col, rescue);
			}
			if (rescue == false) {
				
				//Once East is done, we cannot move west without going back to the position that initiated this so set it to '*' before going west
				vect[curr_row][curr_col] = '*';
				goWest(curr_row, curr_col, rescue);
			}
		}
	}
	else {
		rescue = false;
	}
}

void MazeSolver::searchForPath() {
	bool rescued = false;
	int init_mario_row = mario_row, init_mario_col = mario_col;

	//Initialize a movement for mario for each scenario.
	goNorth(mario_row, mario_col, rescued);
	goSouth(mario_row, mario_col, rescued);
	goEast(mario_row, mario_col, rescued);
	goWest(mario_row, mario_col, rescued);
	
	print();

	if (rescued) {
		cout << "Yay! The Princess Has Been Rescued! \\(o^.^)/" << endl;
	}
	else {
		cout << "No Path Found To Rescue The Princess! (T^T)\\" << endl;
	}
}


void MazeSolver::print() {

	//prints the maze
	for (int i = 0; i < vect.size(); i++)
	{
		for (int j = 0; j < vect[i].size(); j++)
		{
			cout << vect[i][j];
		}
		cout << endl;

	}

}
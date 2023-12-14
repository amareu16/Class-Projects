//MazeSolver.h
#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class MazeSolver {
private:
	long long int row;
	long long int col;
	long long int mario_row;
	long long int mario_col;
	int peach_row;
	int peach_col;

	vector<vector<char>> vect;

public:
	MazeSolver();
	MazeSolver(string maze_data);

	void setMaze(string maze_data);

	void goNorth(int curr_row, int curr_col, bool& rescue);
	void goSouth(int curr_row, int curr_col, bool& rescue);
	void goEast(int curr_row, int curr_col, bool& rescue);
	void goWest(int curr_row, int curr_col, bool& rescue);
	void searchForPath();
	void print();
};

//main.cpp
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <string>
#include "MazeSolver.h"

using namespace std;

int main() {
	MazeSolver Maze("mazeMed.txt");

	Maze.searchForPath();

	return 0;
}
/*
Author: Jinu Jacob
Created: 9/23/2-15
gameState class for Sliding Brick Puzzle
*/

#include <fstream>
#include <stdio.h>
#include <iostream>
#include "gameState.h"
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

//gameState constructors

gameState::gameState(int width, int height){

	//Resize vector's height
	board.resize(height);

	//Resize width of each vector inside board
	for (int i = 0; i < height; i++)
		board[i].resize(width);
}

gameState gameState::createGame(string fileName){
	
	// Open file

	ifstream fin;
	fin.open(fileName.c_str());

	if (!fin){
		cout << "Error opening " << fileName << endl;
		exit (EXIT_FAILURE);
	}

	
	// Parse values from csv
	
	string line;
	vector<int> values;
	string value;

	getline(fin, line);
	stringstream lineStream(line);

	while(getline(lineStream, value, ','))
	{
		int int_value = stoi(value);
		values.push_back(int_value);
	}

	int i;

	for(i = 0; i < values.size(); i++){
		cout << values[i];
	}



	// Check that grid is larger than 1x1

	// Check that there are enought values for a W x H grid

	// Create a gameState with a W x H board

	// Parse the values for each row and add to a row vector

	// add row vector to board

	// return gameState object

}

// gameState Mutators

void gameState::addRow(vector<int> row){

	//add row to board
	board.push_back(row);

}


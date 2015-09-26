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
#include <cstring>
#include <stdlib.h>
#include <sstream>

using namespace std;

//gameState constructors

gameState::gameState(vector< vector<int> > _matrix){

	board = _matrix;
	height = _matrix.size();
	width = _matrix[0].size();
}

gameState::gameState(const gameState& obj){
	board = obj.board;
	height = obj.height;
	width = obj.width;
}


//Inspectors
void gameState::printState(){

	int i,j;

	cout << width << ',' << height << ',' << endl;

	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
		  	cout << board[i][j] << ',' ;
		}	  
		cout << endl ;
	}
}

bool gameState::checkSolved(){
// Iterate through matrix and look for -1(not solved)
	int i,j;

	for(i = 0;i < height; i++){
		for(j = 0;j < width; j++){
			if(board[i][j] == -1)
				return false;
		}
	}
	return true;
}

//Mutators
void gameState::changeValue(int row, int column, int newValue){
	board[row][column] = newValue;

}

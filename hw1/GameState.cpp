/*
Author: Jinu Jacob
Created: 9/23/2-15
GameState class for Sliding Brick Puzzle
*/

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sstream>
#include "GameState.h"
#include "Move.h"

using namespace std;

//GameState constructors

GameState::GameState(vector< vector<int> > _matrix){

	board = _matrix;
	height = _matrix.size();
	width = _matrix[0].size();
}

GameState::GameState(const GameState& obj){
	board = obj.board;
	height = obj.height;
	width = obj.width;
}


//Inspectors
void GameState::printState(){

	int i,j;

	cout << width << ',' << height << ',' << endl;

	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
		  	cout << board[i][j] << ',' ;
		}	  
		cout << endl ;
	}
}

bool GameState::checkSolved(){
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

vector<Move> GameState::getMoves(int piece){
	
	// Directions and vector to return possible moves

	char u = 'u';
	Move moveUp(piece, u);
	Move moveDown(piece, 'd');
	Move moveLeft(piece, 'l');
	Move moveRight(piece, 'r');

	vector<Move> moves;

	// Make sure piece is not -1, 0, or 1
	if(piece < 2)
		return moves;

	// Booleans to keep track of which sides are open
	bool up = true;
	bool down = true;
	bool left = true;
	bool right = true;


	// Check if any positions above, below, left, or right of piece are blocked
	int i,j;
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
		
			if (board[i][j] == piece){  // Find piece
				// If the piece above, below, left, or right of our piece is not 0
				// or the same then that direction is completely blocked
				if ((board[i-1][j] != 0) and (board[i-1][j] != piece)){
					up = false;
				}
				if ((board[i+1][j] != 0) and (board[i+1][j] != piece)){
					down = false;
				}
				if ((board[i][j-1] != 0) and (board[i][j-1] != piece)){
					left = false;
				}
				if ((board[i][j+1] != 0) and (board[i][j+1] != piece)){
					right = false;
				}
			}
			// Stop searching if all sides are blocked; check after each cell
			if ((!up) and (!down) and (!left) and (!right))
				break;
		}
		// Stop searching if all sides are blocked; check after each row
		if ((!up) and (!down) and (!left) and (!right))
			break;
	} // End of search loop
	
	// Add open directions to moves vector
	if (up)
		moves.push_back(moveUp);
	if (down)
		moves.push_back(moveDown);
	if (left)
		moves.push_back(moveLeft);
	if (right)
		moves.push_back(moveRight);

	return moves;

}


//Mutators
void GameState::changeValue(int row, int column, int newValue){
	board[row][column] = newValue;

}

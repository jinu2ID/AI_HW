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
#include <time.h>
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

// Checks if game has been solved
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

// Returns possible moves for a piece
vector<Move> GameState::getMoves(int piece){
	
	// Check if piece is master piece
	bool masterPiece = false;
	if (piece == 2)
		masterPiece = true;

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
	bool pieceFound = false;


	// Check if any positions above, below, left, or right of piece are blocked
	int i,j;
	for (i = 0; i < height; i++){
		// Stop searching if all sides are blocked; check after each row
		if ((!up) and (!down) and (!left) and (!right))
			break;
	
		for (j = 0; j < width; j++){
	 		// Stop searching if all sides are blocked; check after each cell
			if ((!up) and (!down) and (!left) and (!right))
				break;

			if (board[i][j] == piece){  // Find piece
				pieceFound = true;
				// If the piece above, below, left, or right of our piece is not 0
				// or the same then that direction is completely blocked
				if ((board[i-1][j] != 0) and (board[i-1][j] != piece)){
					if (masterPiece){ // If dealing with the masterpiece
						if (board[i-1][j] != -1) // Check for goal
							up = false;
					}
					else {
						up = false;
					}
				}
				if ((board[i+1][j] != 0) and (board[i+1][j] != piece)){
					if (masterPiece){
						if (board[i+1][j] != -1)
							down = false;
					}
					else {
						down = false;
					}
				}
				if ((board[i][j-1] != 0) and (board[i][j-1] != piece)){
					if (masterPiece){
						if (board[i][j-1] != -1)
							left = false;
					}
					else{
						left = false;
					}
				}
				if ((board[i][j+1] != 0) and (board[i][j+1] != piece)){
					if (masterPiece){
						if (board[i][j+1] != -1)
							right = false;
					}
					else {
						right = false;
					}
				}
			}
			
		}
		
	} // End of search loop
	
	// If the piece is not on the board return no moves
	if(!pieceFound){
		up = false;
		down = false;
		left = false;
		right = false;
	}

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

// Returns all possible moves for all pieces in a game state
vector <vector<Move> > GameState::getAllMoves(){
	
	vector <vector<Move> > allMoves;
	// Iterate through every piece on the board
	int i,j;

	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			// Get the piece's moveas
			int x = board[i][j];
			vector<Move> moves = this->getMoves(x);
			// If the piece has moves add it to our collection of all moves
			if(moves.size() != 0)
				allMoves.push_back(moves);
		}
	}

	return allMoves;

}

// Compares two gameStates and checks if they are the same
bool GameState::compareState(GameState otherState){

	int i,j;
	
	// First check that they are the same size
	if ((height != otherState.height) or (width != otherState.width))
	  return false;	

	// Iterate through each position and compare
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			if (board[i][j] != otherState.board[i][j])
				return false;
		}
	}
	// All positions are same; return true
	return true;

}


//Mutators
void GameState::changeValue(int row, int column, int newValue){
	board[row][column] = newValue;
}

// Applies a move to a gameState
void GameState::applyMove(Move move){
	
	int piece = move.getPiece();
	char direction = move.getDirection();
	vector <vector<int> > destinations; // This vector will store positions
	// our piece is moving to (only for right and down)
	vector <vector<int> > toZeroes; // This vector will store positions that
	// need to be changed to 0

	// If the piece is moving up
	if (direction == 'u'){
		int i,j;
		// Find the piece on the board
		for (i = 0; i < height; i++){
			for (j = 0; j < width; j++){
				if (board[i][j] == piece){
					board[i-1][j] = piece;
					// If the position below piece is not the same,
				   //	then that piece needs to be changed to zero
					if (board[i+1][j] != piece){
						vector<int> curPosition; // Temp storage for position
						curPosition.push_back(i);
						curPosition.push_back(j);
						toZeroes.push_back(curPosition);
					}

				}
			}
		}
		// Change old positions to zero
		int k;
		for (k = 0; k < toZeroes.size(); k++){
			board[toZeroes[k][0]][toZeroes[k][1]] = 0; // This is same as
			//board[x][y] = 0  where x and y are the row and column of the
		   //	postition we stored earlier
		}
	}
	// If the piece is moving down
	// This is a special case. We can only update the positions at the end
	// when we are done checking otherwise we will run into an infinite loop
  	else if (direction == 'd'){
		int i,j;
		// Find the piece on the board
		for (i = 0; i < height; i++){
			for (j = 0; j < width; j++){
				if (board[i][j] == piece){
					vector <int> newPosition;
					newPosition.push_back(i+1);
					newPosition.push_back(j);
					destinations.push_back(newPosition);
					// If the position above piece is not the same,
				   //	then that piece needs to be changed to zero
					if (board[i-1][j] != piece){
						vector<int> curPosition; // Temp storage for position
						curPosition.push_back(i);
						curPosition.push_back(j);
						toZeroes.push_back(curPosition);
					}
				}
			}
		}
		// Move piece to new position
		int m;
		for (m = 0; m < destinations.size(); m++){
			board[destinations[m][0]][destinations[m][1]] = piece; // We stored
			// the positions as <x,y> vectors with the destinations vector.
		}
		// Change old positions to zero
		int k;
		for (k = 0; k < toZeroes.size(); k++){
			board[toZeroes[k][0]][toZeroes[k][1]] = 0;
		}
	}
	// If the piece is moving left
  	else if (direction == 'l'){
		int i,j;
		// Find the piece on the board
		for (i = 0; i < height; i++){
			for (j = 0; j < width; j++){
				if (board[i][j] == piece){
					board[i][j-1] = piece;
					// If the position right of  piece is not the same,
				   //	then that piece needs to be changed to zero
					if (board[i][j+1] != piece){
						vector<int> curPosition; // Temp storage for position
						curPosition.push_back(i);
						curPosition.push_back(j);
						toZeroes.push_back(curPosition);
					}
				}
			}
		}
		// Change old positions to zero
		int k;
		for (k = 0; k < toZeroes.size(); k++){
			board[toZeroes[k][0]][toZeroes[k][1]] = 0;
		}
	}
	// If the piece is moving right. This is a special case similar to down
  	else if (direction == 'r'){
		int i,j;
		// Find the piece on the board
		for (i = 0; i < height; i++){
			for (j = 0; j < width; j++){
				if (board[i][j] == piece){
					vector<int> newPosition;
					newPosition.push_back(i);
					newPosition.push_back(j+1);
					destinations.push_back(newPosition);
					// If the position left of piece is not the same,
				   //	then that piece needs to be changed to zero
					if (board[i][j-1] != piece){
						vector<int> curPosition; // Temp storage for position
						curPosition.push_back(i);
						curPosition.push_back(j);
						toZeroes.push_back(curPosition);
					}
				}
			}
		}
		// Move piece to new position
		int m;
		for (m = 0; m < destinations.size(); m++){
			board[destinations[m][0]][destinations[m][1]] = piece;
		}
		// Change old positions to zero
		int k;
		for (k = 0; k < toZeroes.size(); k++){
			board[toZeroes[k][0]][toZeroes[k][1]] = 0;
		}
	}
}

// Applies move to a clone of a gameState and returns clone
GameState GameState::applyMoveCloning(Move move){
	
	vector<vector<int> > cloneVector = board;
	GameState cloneState(cloneVector);
	cloneState.applyMove(move);
	return cloneState;
}

// Normalizes a gameState
void GameState::normalizeState(){
	int i,j;
	int nextIdx = 3;
	for(i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			if (board[i][j] == nextIdx){
				nextIdx++;
			}
			else if (board[i][j] > nextIdx){
			this->swapIdx(nextIdx, board[i][j]);
				nextIdx++;
			}
		}

	}
}

void GameState::swapIdx(int idx1, int idx2){
	int i,j;
	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			if (board[i][j] == idx1){
				board[i][j] = idx2;
			}
			else if(board[i][j] == idx2){
				board[i][j] = idx1;
			}
		}

	}
}

void GameState::randomWalk(int n){
	
	if (n < 1)
		return;

	this->printState();
	cout << endl;

	srand (time(NULL));

	int i;
	for (i = 0; i < n; i++){
		// Generate all possible moves on game board
		vector<vector<Move> > allMoves = this->getAllMoves();

		// Randomly select a move
		int randNo = rand() % allMoves.size();
		int randNoTwo = rand() % allMoves[randNo].size();
		// Execute move
		this->applyMove(allMoves[randNo][randNoTwo]);
		// Normalize game state
		this->normalizeState();
		// Print move to screen
		allMoves[randNo][randNoTwo].printMove();
		cout << endl;
		this->printState();
		cout << endl;
		// Check if solved
		if (this->checkSolved()){
			cout << "Puzzle Solved!" << endl;
			return;
		}
	}
}

/*
Created: 9/23/15
Author: Jinu Jacob
game state class for Sliding Brick Puzzle
*/

#ifndef _GAME_STATE_
#define _GAME_STATE_

#include <fstream>
#include <vector>
#include <string>
#include "Move.h"

using namespace std;

class GameState {


public:
	//Constructors
	GameState(vector< vector<int> > _matrix);
	GameState(const GameState& obj);           //Copy constructor
	
	//Inspectors
	void printState();
	bool checkSolved();
	vector<Move> getMoves(int piece);
	vector <vector<Move> > getAllMoves();
	bool compareState(GameState otherState);

	//Mutators
	void changeValue(int row, int column, int newValue);
	void applyMove(Move move);
	GameState applyMoveCloning(Move move);

private:
	int width;
	int height;
	vector<vector<int> > board;         // 2D vector to hold game state

};

#endif

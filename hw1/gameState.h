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

using namespace std;

class gameState {


public:
	//Constructors
	gameState(vector< vector<int> > _matrix);


private:
	vector<vector<int> > board;         // 2D vector to hold game state

};

#endif

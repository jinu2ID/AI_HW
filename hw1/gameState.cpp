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
}



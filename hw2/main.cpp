/*
Created: 10/14/15
Author: Jinu Jacob
Driver for Marbles in Baskets game
*/
#include <stdio.h>
#include "BasketGame.h"
#include "BasketGame.cpp"
#include "Move.h"
#include "Move.cpp"
#include <algorithm>
#include <vector>

using namespace std;

// Function prototypes
vector<Move> backTrack(vector<BasketGame> stateList, int depthBound, int
		&counter, int &failCount);

int main(){
	BasketGame myGame(6,5,1);
	myGame.printBaskets();	

	vector<Move> myGameMoves = myGame.getAllMoves();
	
	// Print all moves for (6,5,1)
/*	int i;
	for (i = 0; i < myGameMoves.size(); i++)
		myGameMoves[i].printMove();
*/	
	vector<BasketGame> stateList;
	stateList.push_back(myGame);
	int callCount = 0;
	int failCount = 0;
	vector<Move> solution = backTrack(stateList, 3, callCount, failCount);

	int j;
	for (j = 0; j < solution.size(); j++)
		solution[j].printMove();
	cout << callCount << endl << failCount << endl;

}

vector<Move> backTrack(vector<BasketGame> stateList, int depthBound, int
		&counter, int &failCount){
	counter ++;
	BasketGame state = stateList[0];
	if (find(stateList.begin()+1, stateList.end(), state) != stateList.end()){
		vector<Move> path;
		failCount++;
		return path;
	}
	if (state.isSolved()){
		Move emptyMove(0,0,0);
 		vector<Move> path; 
		path.push_back(emptyMove);	
		return path;
	}
	if (stateList.size() > depthBound){
		vector<Move> path;
		failCount++;
		return path;
	}

	vector<Move> moves = state.getAllMoves();
	int i;
	for (i = 0; i < moves.size(); i++){
		BasketGame newState = state.applyMoveClone(moves[i]);
		vector<BasketGame> newStateList = stateList;
		newStateList.insert(newStateList.begin(), newState);

		vector<Move> path = backTrack(newStateList, depthBound, counter,
				failCount);
		if (!path.empty()){
			path.insert(path.begin(), moves[i]);
			return path;
		}
	}
	vector<Move> noSolution;
	return noSolution;
}

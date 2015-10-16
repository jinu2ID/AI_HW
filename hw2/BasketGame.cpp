/*
Created: 10/14/15
Basket implementation for Marbles in Basket problem
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "Move.h"

using namespace std;

// Constructor
BasketGame::BasketGame(int b1, int b2, int b3){
	baskets[0] = b1;
	baskets[1] = b2;
	baskets[2] = b3;
}

// Prints number of marbles in each basket
void BasketGame::printBaskets(){
	int i;
	for (i = 0; i < 3; i++)
		cout << baskets[i] << " ";
	cout << endl;

}

// Checks if game is solved
bool BasketGame::isSolved(){
	if ((baskets[0] == baskets[1]) and (baskets[1] == baskets[2]))
		return true;
	else
		return false;
}
// Returns all moves for a basket
vector<Move> BasketGame::getMoves(int basketNo){
	int basket0 = baskets[0];
	int basket1 = baskets[1];
	int basket2 = baskets[2];

	vector<Move> moves;

	// Check possible moves for each bucket
	if (basketNo == 0){
		if (basket1 <= basket0){ // value can be taken from basket0 that will double basket1
			Move m1(basket1*-1, basket1, 0); // (-basket1, basket1, 0)
			moves.push_back(m1);
		}
		if (basket2 <= basket0){
			Move m2(basket2*-1, 0, basket2); // (-basket2, 0, basket2)
			moves.push_back(m2);
		}

		return moves;
	}
	else if (basketNo == 1){
		if (basket0 <= basket1){ // value can be taken from basket1 that will double basket0
			Move m1(basket0, basket0*-1, 0); // (basket0, -basket0, 0)
			moves.push_back(m1);
		}
		if (basket2 <= basket1){ // value can be taken from basket1 that will double basket 3
			Move m2(0, basket2*-1, basket2); // (0, -basket2, basket2)
			moves.push_back(m2);
		}

		return moves;
	}
	else if (basketNo == 2){
		if (basket0 <= basket2) { // value can be take from basket 3 that will double basket0
			Move m1(basket0, 0, basket0*-1); // (basket0, 0, -basket0)
			moves.push_back(m1);
		}
		if (basket1 <= basket2) { // value can be taken from basket2 that willdouble basket1
			Move m2(0, basket1, basket1*-1); // (0, basket1, -basket1)
			moves.push_back(m2);
		}

		return moves;
	}
	else
		exit (EXIT_FAILURE);
}

// Return all possible moves for a BasketGame
vector<Move> BasketGame::getAllMoves(){
	vector<Move> allMoves;
	
	int i;
	for (i = 0; i < 3; i++){
		vector<Move> moves = this->getMoves(i);
		int j;
		for (j = 0; j < moves.size(); j++){
			allMoves.push_back(moves[j]);
		}
	}

	// Sort moves lexicographically
	moveQSort(allMoves);

	return allMoves;
}

// Applies move to BasketGame
void BasketGame::applyMove(Move m){
	baskets[0] += m.getValue(0);
	baskets[1] += m.getValue(1);
	baskets[2] += m.getValue(2);
}

BasketGame BasketGame::applyMoveClone(Move m){
	
	BasketGame cloneGame(baskets[0], baskets[1], baskets[2]);
	cloneGame.applyMove(m);
	return cloneGame;
}

void moveQSort(vector<Move> &moves){
	int i = 0;
	int j = (int)moves.size()-1;
	Move tmp;
	Move pivot = moves[(i + j)/2];

	while (i <= j) {
		while (moves[i] < pivot)
			i++;
		while (moves[j] > pivot)
			j--;
		if (i <= j) {
			tmp = moves[i];
		  	moves[i] = moves[j];
			moves[j] = tmp;	  
			i++;
			j--;
		}	
	}
}
// 

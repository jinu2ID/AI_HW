/*
Created: 10/14/15
Author: Jinu Jacob
Basket class for Marbles in Basket problem
*/

#include <vector>
#include "Move.h"

#ifndef _BASKET_
#define _BASKET_

using namespace std;

class BasketGame{

	public:
		// Constructor
		BasketGame(int b1, int b2, int b3);

		// Inspectors
		void printBaskets();
		bool isSolved();
		vector<Move> getMoves(int basketNo);
		vector<Move> getAllMoves();
		
		friend bool operator== (const BasketGame &g1, const BasketGame &g2);
		// Mutators
		void applyMove(Move m);
		BasketGame applyMoveClone(Move m);

	private:
		int baskets[3];


};

void moveQSort(vector<Move> &moves);

bool operator== (const BasketGame &b1, const BasketGame &b2){
	return ((b1.baskets[0] == b2.baskets[0]) and
			  (b1.baskets[1] == b2.baskets[1]) and
			  (b1.baskets[2] == b2.baskets[2]));
}


#endif

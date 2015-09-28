/*
Author: Jinu Jacob
Created: 9/27/15
Move class for Sliding Brick Puzzle
*/

#include <stdio.h>
#include "Move.h"

using namespace std;

//Constructors
Move::Move(int value, char _direction){

	piece = value;
	direction = _direction;
}

//Inspectors
void Move::printMove(){
	if(direction == 'u')
	  cout << piece << " up" << endl;	
	else if (direction == 'd')
		cout << piece << " down" << endl;
	else if (direction == 'l')
		cout << piece << " left" << endl;
	else if (direction == 'r')
		cout << piece << " right" << endl;
	else
		cout << "direction " << direction << " unrecognized" << endl;
}

int Move::getPiece(){
	return piece;
}

char Move::getDirection(){
	return direction;
}

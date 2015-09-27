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
	  cout << "up" << endl;	
	else if (direction == 'd')
		cout << "down" << endl;
	else if (direction == 'l')
		cout << "left" << endl;
	else if (direction == 'r')
		cout << "right" << endl;
	else
		cout << "direction " << direction << " unrecognized" << endl;
}

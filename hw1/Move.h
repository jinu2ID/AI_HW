/* 
Created: 9/26/15
Author: Jinu Jacob
A move class for the Sliding Brick Puzzle
*/

#ifndef _MOVE_
#define _MOVE_

using namespace std;
 

class Move{

	public:
		//Constructors
		Move(int value, char _direction);
		
		//Inspectors
		void printMove();

	private:
		int piece;
		char direction;


};

#endif

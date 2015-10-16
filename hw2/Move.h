/*
Created: 10/14/15
Author: Jinu Jacob
Move class for Marbles in Basket problem
*/

#ifndef _MOVE_
#define _MOVE_

class Move{
	public:
		// Constructors
		Move();
		Move(int m1, int m2, int m3);
		Move (const Move &m1);		
		// Inspectors	
		void printMove();
		int getValue(int position);
		
		// Overload assignment operator
		Move& operator= (const Move &mSource);

		// Overload boolean comparison operators
		friend bool operator== (Move &m1, Move &m2);
		friend bool operator!= (Move &m1, Move &m2);
		friend bool operator< (Move &m1, Move &m2);
		friend bool operator<= (Move &m1, Move &m2);
		friend bool operator> (Move &m1, Move &m2);
		friend bool operator>= (Move &m1, Move &m2);
		int move[3];

	private:
};

bool operator== (Move &m1, Move &m2){
	return( m1.move[0] == m2.move[0] and
			  m1.move[1] == m2.move[1] and
			  m1.move[2] == m2.move[2]);
}

bool operator!= (Move &m1, Move &m2){
	return !( m1.move[0] == m2.move[0] and
			  m1.move[1] == m2.move[1] and
			  m1.move[2] == m2.move[2]);
}

bool operator< (Move &m1, Move &m2){

	if (m1.move[0] < m2.move[0]) // If the first value of m1 is less than m2's
		return true;
	else if (m1.move[0] == m2.move[0]){ // If the first values are the same
		if (m1.move[1] < m2.move[1]) // Check the second values
			return true;
		else
			return false;
	}
	else
		return false;
	
}

bool operator<= (Move &m1, Move &m2){
	return ((m1 == m2) or (m1 < m2)); 
}

bool operator> (Move &m1, Move &m2){
	return !(m1 <= m2);
}

bool operator>= (Move &m1, Move &m2){
	return !(m1 < m2);
}
#endif

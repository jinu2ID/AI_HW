/*
Created: 10/14/15
Author: Jinu Jacob
Move class implementation for Basket problem
*/

// Constructors

Move::Move(){
	move[0] = 0;
	move[1] = 0;
	move[2] = 0;
}
Move::Move(int m1, int m2, int m3){
	move[0] = m1;
	move[1] = m2;
	move[2] = m3;
}

Move::Move(const Move &m1){ // Copy constructor
	move[0] = m1.move[0];
	move[1] = m1.move[1];
	move[2] = m1.move[2];
}

// Overload assignment operator
Move& Move::operator= (const Move &mSource){
	move[0] = mSource.move[0];
	move[1] = mSource.move[1];
	move[2] = mSource.move[2];

	return *this;
}
// Returns move value in position
int Move::getValue(int position){
	return move[position];
}

// Prints Move
void Move::printMove(){
	cout << "(" << move[0] << "," << move[1] << "," << move[2] << ")" <<
		endl;
}

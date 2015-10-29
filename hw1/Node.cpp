/* 
Created: 10/18/15
Author: Jinu Jacob
jj559@drexel.edi
node class implementation for Sliding Brick Puzzle
*/

#include <vector>
#include <string>
#include <iostream>
#include "Node.h"
#include "GameState.h"

using namespace std;

// Constructors
Node::Node(){

	state = GameState();
	parent = NULL;
	parentMove = Move();
}

Node::Node(GameState _state){

	state = _state;
	parent = NULL;
	parentMove = Move();
}

Node::Node(GameState _state, Node *_parent){

	state = _state;
	parent = _parent;
	parentMove = Move();
}

Node::Node(GameState _state, Node *_parent, Move _parentMove){
	
	state = _state;
	parent = _parent;
	parentMove = _parentMove;
}

// Copy Constructor
Node::Node(const Node &nSource){
	state = nSource.state;
	parent = nSource.parent;
	parentMove = nSource.parentMove;
}

// Inspectors
bool Node::checkSolved(){

	return state.checkSolved();
}
bool Node::compareNode(const Node otherNode){
	if (state == otherNode.state)
		return true;
	else
		return false;
}

void Node::printNode(){
	
	parentMove.printMove();
	state.printState();
}

// Accessors
GameState Node::getState(){
	return state;
}

Node* Node::getParent(){
	return parent;
}

// Creates a hash from a gameState by converting the 2D vector to a single
// string
string Node::hashNode(){

	string hash;   // Stores hash
	vector< vector<int> > state = this->getState().getBoard();

	int i,j;
	for ( i = 0; i < state.size(); i++){									// [#1]
		for (j = 0; j < state[i].size(); j++){
			// Convert number to string and append to hash string
			int number = state[i][j];
			string numberStr = static_cast<ostringstream*>( &(ostringstream()
						<< number) )->str();
			hash.append(numberStr);
		}
	}
	return hash;
}

// [#1] To create a unique hash this function takes the values in a matrix
// and turns them into a one line string. So for the following matrix:
//
//			1 2 3 
//       4 5 6     ----[ nodeHash()]------>  "123456789012" 
//       7 8 9
//       0 1 2
//       
// Of course a 3 X 4 matrix with the same values in the same order would 
// return the same hash, but for our sliding brick puzzles the dimensions 
// of the board stay the same (even if we did have have to deal with changing 
// dimensions we could tag the height and width to the hash to ensure 
// that it was unique). Therefore any two game states will return the same
// hash. 

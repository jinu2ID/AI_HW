/* 
Created: 10/18/15
Author: Jinu Jacob
jj559@drexel.edi
node class implementation for Sliding Brick Puzzle
*/

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

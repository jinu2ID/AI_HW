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
}

Node::Node(GameState _state){

	state = _state;
	parent = NULL;
}

Node::Node(GameState _state, Node *_parent){

	state = _state;
	parent = _parent;
}

// Inspectors
GameState Node::getState(){
	return state;
}

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

	state.printState();
}

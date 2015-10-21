/*
Created: 10/18/15
Author: Jinu Jacob
jj559@drexel.edu
node class for Sliding Brick Puzzle
This class will be used to perform searches such as BFS amd DFS
*/

#ifndef _NODE_
#define _NODE_

#include <string> 
#include "GameState.h"

using namespace std;

class Node{

	public:
		// Constructor
		Node();
		Node(GameState _state);
		Node(GameState _state, Node *_parent);
		Node(GameState _state, Node *_parent, Move _parentMove);
		Node(const Node & nSource);

		// Inspectors
		bool compareNode(const Node otherNode);
		bool checkSolved();
		void printNode();

		// Access
		GameState getState();
		Node* getParent();

		// Overload operators
		friend bool operator== (const Node &n1, const Node &n2);
		Node& operator= (const Node &nSource);
		

		string hashNode();

	private:
		GameState state;
		Node *parent;
		Move parentMove;


};

bool operator== (const Node &n1, const Node &n2){
	return (n1.state == n2.state);
}

Node& Node::operator= (const Node &nSource){
	state = nSource.state;
	parent = nSource.parent;
	parentMove = nSource.parentMove;
}

#endif

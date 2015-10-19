/*
Created: 10/18/15
Author: Jinu Jacob
jj559@drexel.edu
node class for Sliding Brick Puzzle
This class will be used to perform searches such as BFS amd DFS
*/

#ifndef _NODE_
#define _NODE_

#include "GameState.h"

using namespace std;

class Node{

	public:
		// Constructor
		Node();
		Node(GameState _state);
		Node(GameState _state, Node *_parent);

		// Inspectors
		GameState getState();
		bool compareNode(const Node otherNode);
		bool checkSolved();
		void printNode();

		// Overload operators
		friend bool operator== (const Node &n1, const Node &n2);

	private:
		GameState state;
		Node *parent;


};

bool operator== (const Node &n1, const Node &n2){
	return (n1.state == n2.state);
}

#endif

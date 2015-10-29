/*
Author: Jinu Jacob
Created: 9/23/15
Main program to test GameState class
*/

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include "GameState.h"
#include "GameState.cpp"
#include "Move.h"
#include "Move.cpp"
#include "Node.h"
#include "Node.cpp"

using namespace std;

/* _____________________________________________________	
[]                   FUNCTION PROTOTYPES               /
[] ____________________________________________________\
[]
*/
vector< vector<int> > getValues(string fileName);
vector<Node> bfs(GameState startState);
vector<Node> dfs(GameState startState);
vector<Node> depthLS(GameState startState, int depth);
void deleteNodes(vector<Node*> nodePtrs);
   
/* ______________________________________________________
  /_____________________________________________________/\
  |                                                     //
  |               MAIN METHOD                           \\
  |_____________________________________________________//                 
*/

int main(int argc, char *argv[]) {

	// Test creating GameState from file
	// Get file name
	string file;

	if(argc < 2 ){
		while(file.empty()){
			cout << "Enter a filename" << endl;
			cin >> file;
		}
	} else {
		file = argv[1];
	}

	vector< vector<int> > startState = getValues(file);
 
	GameState myGame(startState);
	myGame.printState();

	map<int, vector<int> > test;

	test[0].push_back(0);
//	test[0].push_back(3);
	test[1].push_back(2);

	std::vector<int>::iterator it;
	it = find(test[0].begin(), test[0].end(), 0);
	test[0].erase(it);
/*	std::vector<int>::iterator it2 = find(test[0].begin(), test[0].end(), 3);
	if (test[0].size() == 1)
		test.erase(0);
	else
		test[0].erase(it2);
*/
	cout << test.begin()->second[0] << endl;

	vector<int> test2;
	test2.push_back(1);
	std::vector<int>::iterator it3 = find(test2.begin(), test2.end(), 1);
	test2.erase(it3);
	cout << test2.size() << endl;

/*	vector<Node> solution = bfs(myGame);

	if (!solution.empty()){
		int i;
		for ( i = 0; i < solution.size(); i++)
			solution[i].printNode();
	
	}*/
}

/* ______________________________________________________________________________
  /_____________________________________________________________________________/|
  |/////////////////////////////////////////////////////////////////////////////||
  |/////////////////				FUNCTION DEFINITIONS           ///////////////////||
  |_____________________________________________________________________________|/


   _____________________________________________________________________________
  [__________________________ HELPER FUNCTIONS__________________________________]
   
 */

// Reads values from a file and converts them to a 2D vector
vector< vector<int> > getValues(string fileName){
 
        // Open file

        ifstream fin;
        fin.open(fileName.c_str());

        if (!fin){
                cout << "Error opening " << fileName << endl;
                exit (EXIT_FAILURE);
        }

		  // Read in line from file

		  // First two values are width and height
        string line;       
        getline(fin, line);
			
		  // Check that strlen is 4
		  if(line.length() != 4){
			  cout << "Incorrect format for height and width" << endl;
			  exit (EXIT_FAILURE);
		  }

		  // Convert height to int
		  char number = line[2];
		  char* convert = new char[2];
		  strcpy(convert, &number);
		  char *endptr;
		  
		  int height = (int)strtol(convert, &endptr, 10);

		  // Extract rows from file
		  int i;
		  string value;
		  vector<int> values;
		  vector< vector<int> > matrix;

		  // Iterate through rows		  
		  for(i = 0;i < height;i++){
			  getline(fin, line);
			  stringstream lineStream(line);
			  
			  // Extract numbers from rows
			  while(getline(lineStream, value, ','))
			  {
				  convert = new char[value.length() + 1];
				  strcpy(convert, value.c_str());
				  int int_value = (int)strtol(convert, &endptr, 10);
				  values.push_back(int_value);
			  }
			  
			  // Add row to matrix
			  matrix.push_back(values);
			  values.clear();

		  }

		  fin.close();
		  return matrix;

}

// Deletes dynamically allocated Nodes to free memory
// Used in Search alogorithms
void deleteNodes(vector<Node*> nodePtrs){
	int i;
	for ( i = 0; i < nodePtrs.size(); i++)
		delete nodePtrs[i];
}

/* _______________________________________________________________________
  [_____________________ UNINFORMED SEARCH ALGORITHMS ____________________]
*/

//-----------------------BREADTH FIRST SEARCH-----------------------------//
vector<Node> bfs(GameState startState){

	Node graphNode(startState);
	vector<Node> path; // will store path to solution if it exists

	// Check if initial state is goal state
	if (startState.checkSolved())
		return path;

	// FIFO queue that stores keys to nodes in breadth first order 
	vector<string> openListKeys;

	// Hash maps storing nodes to visit(openList) and nodes that have been visited(closedList)
	map<string, Node> openList;
	map<string, Node> closedList;

	vector<Node*> nodePtrs;    // Keeps track of dynamically allocated Nodes
	
	// Put first node in openList
	string parentKey = graphNode.hashNode();
	openList[parentKey] = graphNode;
	openListKeys.push_back(parentKey); // Add key to open list queue

	// Iterate through all nodes until solution is found or reeach all leaves
	while(!openListKeys.empty()){

		// Get shallowest node in open list
		Node* parent = new Node;
		parentKey = openListKeys.front();
		*parent = openList[parentKey];
		nodePtrs.push_back(parent);
		
		// Remove node from open lists
		openList.erase(parentKey);
		openListKeys.erase(openListKeys.begin());
		
		// Add Node to closed list
		closedList[parentKey] = *parent;

		// Get all moves for state
		vector<Move> moves = parent->getState().getAllMovesV2();

		// For each move create applyMoveCloning and create node
		int i;
		for ( i = 0; i < moves.size(); i++){

			// Create child state by applying move to parent
			GameState childState = parent->getState().applyMoveCloning(moves[i]);
			childState.normalizeState();

			// Create child node and key for hash map
			Node child(childState, parent, moves[i]);

			string childKey = child.hashNode();
				
			// Check if Node is in open or closed lists
			if ((openList.count(childKey) == 0) and (closedList.count(childKey) == 0)){
					
				// Check if Node has goal state
				if (child.checkSolved()){
					Node* parentPtr;
					parentPtr = &child;
					// Walk backwards and add nodes to path
					while(true){
						path.insert(path.begin(), *parentPtr);
						if (parentPtr->getParent() == NULL){ // At root node
							break;
						}
						parentPtr = parentPtr->getParent();
					}
					deleteNodes(nodePtrs); // Free memory
					return path;           // Return solution path
				}
				// Node is not goal; add it to the back of the open list
				openListKeys.push_back(childKey);
				openList[childKey] = child;
			}
		}
	}
	// No solution found
	deleteNodes(nodePtrs);   // Free memory
	return path;				 // Return empty path

}

//-------------------------------DEPTH FIRST SEARCH------------------------//
vector<Node> dfs(GameState startState){

	Node graphNode(startState);
	vector<Node> path; // Will store path to solution if it exists

	// Check if initial state is goal
	if (startState.checkSolved())
		return path;

	// LIFO stack that stores keys to nodes in a depth first order
	vector<string> openListKeys;

	// Hash maps storing nodes to visit(openList) and nodes that have been
	// visited(closedList)
	map<string, Node> openList;
	map<string, Node> closedList;

	vector<Node*> nodePtrs;		// Keeps track of dynamically allocated nodes
	
	// Put first node in open list
	string parentKey = graphNode.hashNode();
	openList[parentKey] = graphNode;
	openListKeys.push_back(parentKey);

	while(!openList.empty()){
		
		// Get node on top of stack
		Node* parent = new Node;
		parentKey = openListKeys.front();
		*parent = openList[parentKey];
		nodePtrs.push_back(parent);

		// Remove node from open lists
		openList.erase(parentKey);
		openListKeys.erase(openListKeys.begin());

		// Add node to closed list
		closedList[parentKey] = *parent;
		
		// Get all moves for state
		vector<Move> moves = parent->getState().getAllMovesV2();

		// For each move applyMoveCloning and create node
		int i;
		for ( i = 0; i < moves.size(); i++){
			
			// Create child state by applyihn move to parent
			GameState childState = parent->getState().applyMoveCloning(moves[i]);
			childState.normalizeState();

			// Create child node and key for hash map
			Node child(childState, parent, moves[i]);
			string childKey = child.hashNode();

			// Check if node is in open or closed lists
			if ((openList.count(childKey) == 0) and (closedList.count(childKey) == 0 )){

				// Check if Node is goal state
				if (child.checkSolved()){
					Node* parentPtr;
					parentPtr = &child;

					// Wallk backwards and add nodes to solution path
					while(true){
						path.insert(path.begin(), *parentPtr);
						if (parentPtr->getParent() == NULL){ // At root node
							break;
						}
						parentPtr = parentPtr->getParent();
					}
					deleteNodes(nodePtrs);		// Free memory
					return path;				   // Return solution path
				}
				// Node is not goal; add it to the top of the open list
				openListKeys.insert(openListKeys.begin(), childKey);
				openList[childKey] = child;
			}
		}
	}
	// No solution found
	deleteNodes(nodePtrs); 			// Free memory      
	return path;						// Return empty path
}


//-------------------------DEPTH LIMMITED SEARCH-----------------------//
vector<Node> depthLS(GameState startState, int depth){

	Node graphNode(startState);
	vector<Node> path; // Will store path to solution if it exists
	int depthCounter = 0;

	// Check if initial state is goal
	if (startState.checkSolved())
		return path;

	// Vectors used as LIFO stack
	vector<Node> openList;
	vector <Node> closedList;

	vector<Node*> nodePtrs;		// Keeps track of dynamically allocated nodes

	openList.push_back(graphNode);

	while(!openList.empty()){
		
		// Get node on top of stack
		Node* parent = new Node;
		*parent = openList.front();
		nodePtrs.push_back(parent);
		openList.erase(openList.begin());

		// Add node to closed list
		closedList.push_back(*parent);
		
		// Get all moves for state
		vector<Move> moves = parent->getState().getAllMovesV2();

		// For each move applyMoveCloning and create node
		int i;
		for ( i = 0; i < moves.size(); i++){
			
			// Create child state by applyihn move to parent
			GameState childState = parent->getState().applyMoveCloning(moves[i]);
			childState.normalizeState();

			Node child(childState, parent, moves[i]);

			// Check if node is in open or closed lists
			if ((find(openList.begin(), openList.end(), child) == openList.end()) and
				 (find(closedList.begin(), closedList.end(), child) == closedList.end())){
				// Check if Node is goal state
				if (child.checkSolved()){
					Node* parentPtr;
					parentPtr = &child;

					// Wallk backwards and add nodes to solution path
					while(true){
						path.insert(path.begin(), *parentPtr);
						if (parentPtr->getParent() == NULL){ // At root node
							break;
						}
						parentPtr = parentPtr->getParent();
					}
					deleteNodes(nodePtrs);
					return path;
				}
				openList.insert(openList.begin(), child);
			}
		}
		if (depthCounter == depth){
			path.clear();
			return path;
		}
		depthCounter++;
	}
	deleteNodes(nodePtrs);
	return path;


}

//-----------------------ITERATIVE DEEPENING SEARCH----------------//
vector<Node> iterativeDS(GameState startState){

}


/*	 _________________________________________________________________
	[____________________ INFORMED SEARCH ALGORITHMS)_________________]
*/

//------------------------ A* SEARCH--------------------------------//
vector<Node> aStar(GameState startState){
	
	Node graphNode(startState);
	vector<Node> path; // Will store solution if it exists

	// Chcck if initial state is goal state
	if (startState.checkSolved())
		return path;

	// Stores keys to nodes in increasing F score order
	map<int, vector<string> > openListKeys;

	// Hash maps storing nodes to visit(openList) and nodes that have been
	// visited(closedList)
	map<string, Node> openList;
	map<string, Node> closedList;

	vector<Node* > nodePtrs; // Keep track of dynamically allocated nodes

	// Put node on open list
	string parentKey = graphNode.hashNode();
	openList[parentKey] = graphNode;
	graphNode.setScores();
	int fScore = graphNode.getFScore();
	openListKeys[fScore].push_back(parentKey);

	// Iterate through all nodes until solution is found or leaves reached
	while(!openListKeys.empty()){
	
		// Get node with lowest f score
		Node *parent = new Node;
		parentKey = openListKeys.begin()->second[0];
		*parent = openList[parentKey];
		nodePtrs.push_back(parent);

		// Remove node from openListKeys and openList
		if (openListKeys.begin()->second.size() == 1)
			openListKeys.erase(openListKeys.begin()->first);
		else
			openListKeys.begin()->second.erase(openListKeys.begin()->second.begin());

		// Add node to closed list
		closedList[parentKey] = *parent;

		// Check if current_node is solution
		if (parent->checkSolved()){
			Node* parentPtr;
			parentPtr = parent;
			// Walk backwards and add nodes to path
			while(true){
				path.insert(path.begin(), *parentPtr);
				if (parentPtr->getParent() == NULL){
					break;
				}
			}
		}

		vector<Move> moves = parent->getState().getAllMovesV2();

		// for each successor_node
		int i;
		for (i = 0; i < moves.size(); i++)
		{
			// Set cost of each node to be cost of current + 1
			// Generate each succesor_node from current_node
			GameState childState = parent->getState().applyMoveCloning(moves[i]);
			childState.normalizeState();

			Node child(childState, parent, moves[i]);
			child.setScores();
			string childKey = child.hashNode();
			child.setScores();
			int childFScore = child.getFScore();
			
			// Child is in closed list discard and continue
			if (closedList.count(childKey) > 0)
					continue;

			// Child is in open list
			if (openList.count(childKey) > 0){
				// Child in open list has f score better than current child
				if (openList[childKey].getFScore() <= childFScore)
					continue;
				// Current old child has better f score than child in open list
				else {
					// Remove child in openListKeys and openList
					int oldFScore = openList[childKey].getFScore();
					std::vector<string>::iterator it = find(openListKeys[oldFScore].begin(),openListKeys[oldFScore].end(),childKey);
					
					if (openListKeys[oldFScore].size() == 1)            //[1]
						openListKeys.erase(oldFScore);
					else
						openListKeys[oldFScore].erase(it);

					openList.erase(childKey);

					// Add new child to openListKeys and openList
					openListKeys[childFScore].push_back(childKey);
					openList[childKey] = child;
				}
			} // Child is not in open or closed list
			else {
				openListKeys[childFScore].push_back(childKey);
				openList[childKey] = child;
			}
			// Add node_successor to open list
		}
		// Add node_current to closed list
	}
}


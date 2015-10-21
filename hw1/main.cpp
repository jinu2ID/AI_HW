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
#include <list>
#include "GameState.h"
#include "GameState.cpp"
#include "Move.h"
#include "Move.cpp"
#include "Node.h"
#include "Node.cpp"

using namespace std;

//FUNCTION PROTOTYPES
vector< vector<int> > getValues(string fileName);
vector<Node> bfs(GameState startState);
vector<Node> dfs(GameState startState);
vector<Node> depthLS(GameState startState, int depth);
void deleteNodes(vector<Node*> nodePtrs);

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

	Node n1(myGame);
	string hash = n1.hashNode();
	cout << hash << endl;
/*	vector<Node> solution = bfs(myGame);

	if (!solution.empty()){
		int i;
		for ( i = 0; i < solution.size(); i++)
			solution[i].printNode();
	}
	// Test print function
	cout << "Print Function Test" << endl;
	myGame.printState();
	cout << endl; 

	// Test copy function
	cout << "Copy Function Test" << endl;
	GameState yourGame(myGame);

	yourGame.changeValue(0,0,100);

	cout << "Changed Copy" << endl;
	yourGame.printState();
	cout << "Original Unchanged" << endl;
	myGame.printState();
	cout << endl;

	// Test puzzle solved function
	cout << "Puzzle Solved Function Test" << endl;
	if (myGame.checkSolved())
		cout << "Solved!" << endl;
	else
		cout << "Not solved!" << endl;
	cout << endl;

	// Test showing piece's moves
	cout << "Get Piece's Moves Function Test" << endl << "Enter piece" <<
		endl;
	int piece;
	cin >> piece;
	vector<Move> moves = myGame.getMoves(piece);

	if (moves.size() == 0)
		cout << "No moves" << endl;
	else {
		int i;
		for (i = 0; i < moves.size(); i++){
			moves[i].printMove();
		}
	}
	cout << endl;

	// Test get all moves
	cout << "Get All Moves for State Function Test" << endl;
	vector <vector<Move> > allMoves = myGame.getAllMoves();
	int i, j;
	for (i = 0; i < allMoves.size(); i++){
		for (j = 0; j < allMoves[i].size(); j ++){
			allMoves[i][j].printMove();

		}
	}
	cout << endl;

	// Test applyMove function
	cout << "Apply Move Function Test" << endl << "Enter piece" << endl;
	cin >> piece;
	cout << "Enter direction: u d l r" << endl;
	char dir;
	cin >> dir;
	Move newMove(piece, dir);
	myGame.applyMove(newMove);
	myGame.printState();
	cout << endl;

	// Test applyMoveCloning function
	cout << "Apply Move Cloning Test" << endl << "Enter piece" << endl;
	cin >> piece;
	cout << "Enter direction: u d l r" << endl;
	cin >> dir;
	Move newerMove(piece, dir);
	GameState cloneState = myGame.applyMoveCloning(newerMove);
	cloneState.printState();
	cout << endl;

	// Test compareState function
	cout << "Compare States Function Test" << endl;
	bool same = myGame.compareState(cloneState);
	cout << "Comparing to previously changed clone state" << endl;
	cout << ( same ? "Same" : "Not Same") << endl;
	GameState copyState(myGame);
	same = myGame.compareState(copyState);
	cout << "Comparing to a copy of original game state" << endl;
	cout << ( same ? "Same" : "Not Same") << endl;
	cout << endl;

	// Test normalizeState function
	cout << "Normalize State Function Test" << endl;
	myGame.normalizeState();
	myGame.printState();
	cout << endl;

	// Test randWalk function
	cout << "Random Walk Function Test" << endl << "Enter a number" << endl;
	int n;
	cin >> n;
	myGame.randomWalk(n);
*/
}


//FUNCTION DEFINITIONS
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

	// Vectors used a FIFO queues
	vector<Node> openList;		// For nodes that need to be visited
	vector<Node> closedList;	// For nodes that have already been visited
	
	vector<Node*> nodePtrs;    // Keeps track of dynamically allocated Nodes

	openList.push_back(graphNode);

	while(!openList.empty()){

		// Get shallowest node in open list
		Node* parent = new Node;
		*parent = openList.front();
		nodePtrs.push_back(parent);
		openList.erase(openList.begin());
		
		// Add Node to closed list
		closedList.push_back(*parent);

		// Get all moves for state
		vector<Move> moves = parent->getState().getAllMovesV2();

		// For each move create applyMoveCloning and create node
		int i;
		for ( i = 0; i < moves.size(); i++){

			// Create child state by applying move to parent
			GameState childState = parent->getState().applyMoveCloning(moves[i]);
			childState.normalizeState();

			Node child(childState, parent, moves[i]);

			// Check if Node is in open or closed lists
			if ((find(openList.begin(), openList.end(), child) == openList.end()) and
				 (find(closedList.begin(), closedList.end(), child) == closedList.end())){
					
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
					deleteNodes(nodePtrs);
					return path;
				}
				// Add Node to open list
				openList.push_back(child);
			}
		}
	}
	deleteNodes(nodePtrs);
	return path;

}

//-------------------------------DEPTH FIRST SEARCH------------------------//
vector<Node> dfs(GameState startState){

	Node graphNode(startState);
	vector<Node> path; // Will store path to solution if it exists

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
	}
	deleteNodes(nodePtrs);
	return path;
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

// Deletes dynamically allocate Nodes to free memory
void deleteNodes(vector<Node*> nodePtrs){
	int i;
	for ( i = 0; i < nodePtrs.size(); i++)
		delete nodePtrs[i];
}

/*	 _________________________________________________________________
	[____________________ INFORMED SEARCH ALGORITHMS)_________________]
*/

//------------------------ A* SEARCH--------------------------------//
/*vector<Node> aStar(GameState startState, pointerToFunction){

	// Open list
	// Closed list

	// Create node from first state

}*/


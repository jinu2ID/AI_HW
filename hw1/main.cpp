/*
Author: Jinu Jacob
Created: 9/23/15
Main program to test GameState class
*/

#include <fstream>
#include <stdio.h>
#include <iostream>
#include "GameState.h"
#include "GameState.cpp"
#include "Move.h"
#include "Move.cpp"
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

//FUNCTION PROTOTYPES
vector< vector<int> > getValues(string fileName);
bool backTrack(vector<GameState> stateList, int depthBound, vector<Move> path, vector<vector<Move> > &pathList);
bool bfs(GameState state);
bool checkDuplicate(GameState child, vector<GameState> list);

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
	// Test breadth-first-search
	if( bfs(myGame))
		cout << "Solved" << endl;
	else
		cout << "Not solved" << endl;

/*	// Test print function
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
*/	int piece;
/*	cin >> piece;
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

		  return matrix;

}

// BackTrack algorithm searches for solution 
bool backTrack(vector<GameState> stateList, int depthBound, vector<Move> path, vector<vector<Move> > &pathList){
	
	GameState state = stateList[0];
	// Check that state is not already in stateList i.e. it is a leaf
	if (find(stateList.begin()+1, stateList.end(), state) != stateList.end()){
		return false;
	}		
	// Check if goal state
	if (state.checkSolved()){
		return true;
	}
	if(stateList.size() > depthBound){
		return false;
	}
	
	int i,j;
	vector<Move> moves = state.getAllMovesV2();
	for (i = 0; i < moves.size(); i++){
		// New node 
		GameState newState = state.applyMoveCloning(moves[i]);
		// Add node to tree
		vector<GameState> newStateList = stateList;
		newStateList.insert(newStateList.begin(), newState);
		// Add move to path
		vector<Move> newPath = path;
		newPath.push_back(moves[i]);
		
		// If move solves puzzle add path to pathList
		bool solved = false; 
		solved = backTrack(newStateList, depthBound, newPath, pathList);
		if (solved){
			if (find(pathList.begin(), pathList.end(), newPath) == pathList.end()){
				pathList.push_back(newPath);
			}
		}
	}
	return false;
}

// Breadth First Search
bool bfs(GameState state){

	GameState node = state;

	// Check if initial state is goal
	if (node.checkSolved()){
		return true;
	}

	vector<GameState> frontier;
	frontier.push_back(node);
	vector<GameState> explored;
	
	while(!frontier.empty()){
	
		node = frontier[0];   // choose shallowest frontier in node
	//	cout << "Node " << counter << endl;
	//	node.printState();
		frontier.erase(frontier.begin()); // Remove that node from frontier
		explored.push_back(node); // add node to explored
		vector<Move> moves = node.getAllMovesV2(); // Get all moves for that node

		int i;
		for (i = 0; i < moves.size(); i++){
			
			// Apply move to node
			GameState child = node.applyMoveCloning(moves[i]);
			
			// Check if child is already in frontier or explored
			if (checkDuplicate(child, frontier))
				continue;
			if (checkDuplicate(child, explored))
				continue;

			if (child.checkSolved()){ // Found solution
				child.printState();
				return true;
			}
			frontier.push_back(child); // Add child to frontier to check its children
		}
	}

	return false;

}

bool checkDuplicate(GameState child, vector<GameState> list){
	GameState childCopy = child;
	childCopy.normalizeState();

	int k;
	for (k = 0; k < list.size(); k++){
		GameState inList = list[k];
		inList.normalizeState();
		if (child == inList)
			return true;
	}
	return false;

}

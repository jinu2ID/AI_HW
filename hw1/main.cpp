/*
Author: Jinu Jacob
Created: 9/23/15
Main program to test gameState class
*/

#include <fstream>
#include <stdio.h>
#include <iostream>
#include "gameState.h"
#include "gameState.cpp"
#include <string>

using namespace std;

//FUNCTION PROTOTYPES
vector< vector<int> > getValues(string fileName);

main() {

vector< vector<int> > startState = getValues("SBP-level0.txt");

int i, j;

for(i = 0; i < startState.size(); i++){

	for(j = 0; j < startState[i].size(); j++){
		cout << startState[i][j] ;
	
	}
	cout << endl;
}

}


//FUNCTION DEFINITIONS

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

		  // Convert width and height to int
		  char number = line[0];
		  char* convert = new char[2];
		  strcpy(convert, &number);
		  char *endptr;
		  
		  int width = (int)strtol(convert, &endptr, 10);
		  
		  number = line[2];
		  strcpy(convert, &number);
		  
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



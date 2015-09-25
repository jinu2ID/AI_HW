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
gameState createGame(string fileName);

main() {

gameState game1 = createGame("SBP-level0.txt");

}


//FUNCTION DEFINITIONS

gameState creatGame(string fileName){

 
        // Open file

        ifstream fin;
        fin.open(fileName.c_str());

        if (!fin){
                cout << "Error opening " << fileName << endl;
                exit (EXIT_FAILURE);
        }

        
        /* Parse values from csv
         This was tricky as I couldn't use atoi(no error handling).
         I had to convert the number string to a char *. Then pass
         it to strtol and convert it to an int. Seems like some C++
         voodoo.
        */

        string line;
        vector<int> values;
        string value;
        char *endptr;

        getline(fin, line);
        stringstream lineStream(line);

        while(getline(lineStream, value, ','))
        {
                char* convert = new char[value.length() + 1];
                strcpy(convert, value.c_str());
                long int_value = strtol(convert, &endptr, 10);
                values.push_back(int_value);
        }

        int i;

        for(i = 0; i < values.size(); i++){
                cout << values[i];
        }



        // Check that grid is larger than 1x1

        // Check that there are enought values for a W x H grid

        // Create a gameState with a W x H board

        // Parse the values for each row and add to a row vector

        // add row vector to board

        // return gameState object
        gameState game1(2, 2);
        return game1;

}



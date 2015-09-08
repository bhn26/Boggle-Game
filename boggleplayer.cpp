#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <algorithm>
#include <iostream>

#include "iboggleplayer.h"
#include "boggleplayer.h"

/*
 * Builds the lexicon by inserting the words into a ternary tree data 
 * structure. Calls a recursive add that inserts the words from the vector
 * starting from the center, then the center of the sides.
 */
void BogglePlayer::buildLexicon(const vector<string>& word_list) {
  //Inserts the words recursively into the tree in optimized manner
  BoggleUtil::insertWords(word_list, 0, word_list.size() - 1, lexTree);
  hasBuilt = true;    //Sets the built to true;
}

/**
 * Sets up the boggle board using the provided number of rows,
 * and letters.
 */
void BogglePlayer::setBoard(unsigned int rows,
                       unsigned int cols, string** diceArray){
  bogRows = rows;       // Record desired number of rows/cols
  bogCols = cols;

  // Creates a vector representing the board
  for(int i = 0; i < (int) rows; i++)
  {
    for(int j = 0; j < (int) cols; j++)
      board.push_back(diceArray[i][j]);
  }
  hasSet = true;        // Record that the bord has been set
}

/**
 * Gets all the valid words on the board for the computer player to 
 * search through and annihilate the human player
 */
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length,
                                   set<string>* words) {
  // Checks if board and lexicon has been built
  if(hasBuilt && hasSet) {
    for(int i = 0; i < bogRows; i++) {       // Go through cells and branch
      for(int j = 0; j < bogCols; j++) {
        std::vector<bool> visited ((bogRows*bogCols), false);
        int position = (bogRows*i)+ j;

	// After calculating start position, start branching out
        BoggleUtil::wordOnBoard(position, board, lexTree, words, "", visited,
	                       minimum_word_length, bogRows, bogCols);
      }
    }
    return true;
  }
  return false;
}

/**
 * Goes through lexicon tree to find if word is valid
 * Returns true if the word is valid
 * false if invalid word or if lexicon tree hasn't been built.
 */
bool BogglePlayer::isInLexicon(const string& word_to_check){
  //Checks if the lexicon was built or not yet.
  if(!hasBuilt)
    return false;
  //Searches the tree and returns if there was a successful find
  else {
    return lexTree.find(word_to_check).first;   
  }
}
  
/*
 * Checks if the user inputted word is on the board or not. If so, it will
 * highlight the words that are on the board and add a point to the player's
 * score.
 */
vector<int> BogglePlayer::isOnBoard(const string& word_to_check){
  std::vector<int> onBoard;          //Creates the board object to be returned
  std::vector<bool> visited ((bogRows*bogCols), false); //Use for acyclic find
  bool found = false;                //Defaults bool flag to false

  //For loop that takes in case to determine which letter to start at on board
  for(int i = 0; i < bogRows; i++) {
    for(int j = 0; j < bogCols; j++) {
      int position = (bogRows*i)+ j; //Gets initial position to check board
      std::string tmp = board.at(position);   //Gets the lowercase string
      std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
      std::string checker = word_to_check.substr(0, tmp.length());//Get substr
      int counter = tmp.length();    //Used to keep track of how to get substr
      //If strings match, then it'll go into a recursive call to find the word
      if(!checker.compare(tmp)) {
        //The recursive method call that traverses the board
        BoggleUtil::findWOB(onBoard, board, word_to_check, position, 
	                    bogRows, bogCols, counter, visited);
        
	std::string test; //Turns the vector into a string to compare sizes
	for(int i = 0; i < (int) onBoard.size(); i++){
	  test.append(board.at(onBoard.at(i)));
	}

        //If they are different, the path went down the incorrect way
        if(test.size() != word_to_check.length()) {
          std::vector<int> clear;
          onBoard = clear;
          continue;
        }

        found = true;      //Sets bool flag to true
        i = 0;             //Sets initial search again
	j = 0;
        break;             //Breaks from the inner loop
      }
    }
    if(found)              //Used to break from outer loop if true
      break;
  }
  return onBoard;          //Returns vector of ints for positions
}

/*
 * Used to make a custom board used for testing purposes
 */
void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, 
                                  unsigned int *cols)
{
  *rows = 4;
  *cols = 4;
  new_board[0][0] = "B";
  new_board[0][1] = "G";
  new_board[0][2] = "L";
  new_board[0][3] = "G";
  new_board[1][0] = "I";
  new_board[1][1] = "I";
  new_board[1][2] = "W";
  new_board[1][3] = "U";
  new_board[2][0] = "T";
  new_board[2][1] = "S";
  new_board[2][2] = "D";
  new_board[2][3] = "E";
  new_board[3][0] = "E";
  new_board[3][1] = "F";
  new_board[3][2] = "O";
  new_board[3][3] = "W";
}
  
/*
 * Destructod method that deletes the boggle player.
 */
BogglePlayer::~BogglePlayer() {}

#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H

#include "iboggleplayer.h"
#include "boggleutil.h"

class BogglePlayer: public IBogglePlayer{
private:
  bool hasBuilt;         //Checks if the lex was built yet
  bool hasSet;           //Checks if the board was set yet
  int bogRows;           //Number of rows passed in
  int bogCols;           //Number of cols passed in
  TST lexTree;           //Lexicon tree that lex is stored in
  vector<string> board;  //Stores the board into a vector of strings

public:
 /**
  * Builds the lexicon out of a list of words
  */
  void buildLexicon(const vector<string>& word_list);

 /**
  * Sets up the boggle board
  */
  void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
  
 /**
  * Gets every valid word on the board
  */
  bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);

  /**
   * Checks whether given word is in lexicon
   */
  bool isInLexicon(const string& word_to_check);

  /**
   * Checks whether given word is on the board
   */
  vector<int> isOnBoard(const string& word_to_check);

  /**
   * Builds a custom board, mainly for testing
   */
  void getCustomBoard(string** &new_board, 
                unsigned int *rows, unsigned int *cols);

  /**
   * Destroys the boggleplayer
   */
  ~BogglePlayer();

};

#endif //BOGGLEPLAYER_H

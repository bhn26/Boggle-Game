#include "boggleutil.h"
#include <iostream>
#include <algorithm>

/*
 * Inserts the word from the vector into a ternary tree
 * Does so recursively
 */
void BoggleUtil::insertWords(const std::vector<std::string>& word_list,
                             int start, int end, TST& t) {
  //Used to check for overflows in the recursion call
  if (start > end) {
    return;
  }

  int mid = start + (end-start)/2;   //Gets the midpoint of the current
  t.insert(word_list.at(mid));       //Inserts the word at the midpoint
  BoggleUtil::insertWords(word_list, start, mid - 1, t); //Recursion cals
  BoggleUtil::insertWords(word_list, mid + 1, end, t); 
}

/**
 * Traverses the board, putting every valid word it finds into the 
 * given set.
 */
void BoggleUtil::wordOnBoard(int position,
                       const std::vector<std::string> board, TST& t,
		       std::set<std::string>* words, std::string currStr,
		       std::vector<bool> visited, int min, int rows, int cols)
{
  std::vector<int> dx ({0,1,1,1,0,-1,-1,-1});   // Offset board traversal
  std::vector<int> dy ({cols,cols,0,-1*cols,-1*cols,-1*cols,0,cols});

  visited.at(position) = true;                  // Mark current tile as used

  std::string tmp = board.at(position);  // Convert tile to lower case
  std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
  currStr.append(tmp);                   // Add tile to current string

  // Get information on the current string
  std::pair<bool, bool> check = t.find(currStr);

  if(check.first) {             // If it's a valid word
    const bool is_in = words->find(currStr) != words->end(); // Check copies
    if((int) currStr.length() >= min && !is_in) {   // meets min length
      words->insert(currStr);   // insert
    }
    if(check.second)            // If word is a dead end
      return;
  }
  else                          // Invalid word
    if(check.second)            // If word is a dead end
      return;

  int top = cols; // boundary for top of the board
  int bot = (rows*cols - 1) - cols;  // bottom board boundary
  int right = cols - 1;   // right boundary, index%cols == right
  int left = 0;           // left boundary, index%cols == left;


  // Branch out more and add more letters    
  for(int delta = 0; delta < 8; delta++) {
    int x = dx.at(delta);             // Get the offset
    int y = dy.at(delta);

    int newPos = position+x+y;        // Position of next tile

    // Checks boundaries of board
    if(position < top && y == (-1*cols)) {
      continue;
    }
    if(bot < position && y == cols) {
      continue;
    }
    if(position%cols == right && x == 1) {
      continue;
    }
    if(position%cols == left && x == -1) {
      continue;
    }

    if(visited.at(newPos)) {           // Checks if node has been visited
      continue;
    }

    // Recursively start from new position
    wordOnBoard(newPos, board, t, words, currStr, visited, min, rows, cols);
  }
}

/**
 * Finds if the user's inputed word is a valid word on the board
 * Returns true if the word is found
 */
bool BoggleUtil::findWOB(std::vector<int> &onBoard,
                         const std::vector<std::string> board,
			 const std::string& word_to_check,
			 int position, int rows, int cols, int counter, 
		         std::vector<bool> visited)
{
  std::vector<int> dx ({0,1,1,1,0,-1,-1,-1});     // Offsets for traversal
  std::vector<int> dy ({cols,cols,0,-1*cols,-1*cols,-1*cols,0,cols});

  // If the position in the string exceeds the length, just get out
  if(counter > (int) word_to_check.length())
    return false;

  visited.at(position) = true;               // Mark current tile as true
  onBoard.push_back(position);               // Record tile's position

  // If the position matches the length of the word
  if(counter == (int) word_to_check.length()) {
    std::string test;
    for(int i = 0; i < (int) onBoard.size(); i++){  // Build word from pos
      test.append(board.at(onBoard.at(i)));
    }

    // Turn to lower case
    std::transform(test.begin(), test.end(), test.begin(), ::tolower);
    if(!word_to_check.compare(test))    // Check if built word is right
      return true;
    else 
      return false;
  }

  int tmpSize = 0;                   // Size of string in tile
  int top = cols;                    // boundary for top of the board
  int bot = (rows*cols - 1) - cols;  // bottom board boundary
  int right = cols - 1;   // right boundary, index%cols == right
  int left = 0;           // left boundary, index%cols == left;

  // 
  for(int delta = 0; delta < 8; delta++) { 
    int x = dx.at(delta);             // Get the offset
    int y = dy.at(delta);

    int newPos = position+x+y;        // position of next tile

    // Checks boundaries of the board
    if(position < top && y == (-1*cols)) {
      continue;
    }
    if(bot < position && y == cols) {
      continue;
    }
    if(position%cols == right && x == 1) {
      continue;
    }
    if(position%cols == left && x == -1) {
      continue;
    }

    // Checks if tile has already been visited
    if(visited.at(newPos)) {
      continue;
    }
    // Lower case the string
    std::string tmp = board.at(newPos);
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

    // Get substring from word to check
    std::string tmpStr = word_to_check.substr(counter, tmp.length());
    tmpSize = tmp.size();       // Get size of the tile
    if(!tmpStr.compare(tmp)) {  // Checks if the substring == tile
      counter += tmp.length();  // Increment position in string
      if(findWOB(onBoard, board, word_to_check, newPos, 
                  rows, cols, counter, visited))  // Next one is user's word
        return true;                              // Then end
      counter -= tmpSize;       // Not found, move string back
    }
  }
  onBoard.pop_back();           // Not found, remove added position
  return false;                 // Not found
}


/**
 * Recursively deconstructs the TST
 */
void TST::destruct(bogNode* node){
  if(node->left)                 // Traverse down tree
    destruct(node->left);
  else if(node->center)
    destruct(node->center);
  else if(node->right)
    destruct(node->right);

  delete node;                   // Destroy the node
  node = nullptr;
}

/**
 * Compares two characters for ternary tree traversal
 */
int TST::charCmp(char b, char c){
    return ((int) b - c);
}

/**
 * Inserts word into Ternary Tree, for lexicon
 */
void TST::insert(const std::string word) {
      
  bogNode *node = new bogNode(word.at(0));   //first letter of the word
  bogNode *start = node;                     //Pointer to start of word chain
      
  if(word.length() == 1)
  {
    start->end = true;
  }

  //Creates the word chain and sets the last node's end to true
  for(unsigned int i = 1; i < word.length(); i++) {
    bogNode *tmp = new bogNode(word.at(i));
    node->center = tmp;
    node = node->center;
    if(i+1 == word.length()) {
      node->end = true;
    }
  }
        
  //Sets the root node if there isn't any yet
  if(root == nullptr) {
    root = start;
    tSize++;
    return;
  }
      
  // two node pointers, one to the root, and one to keep track of position
  bogNode *curr = root;
  bogNode *track = nullptr;
      
  //While loop that traverses the ternary tree to insert
  while(1) {      
    //Compares the current two characters
    int cmp = charCmp(curr->data, start->data);
        
    //If the compare was negative and has no right pointer, it inserts it
    if(cmp < 0 && !curr->right) {
      curr->right = start;
      tSize++;
      break;
    }
    //If the compare was positive and has no left pointer, it inserts it
    else if(0 < cmp && !curr->left) {
      curr->left = start;
      tSize++;
      break;
    }
    // less and has a right pointer, moves the current right for next compare
    else if(cmp < 0 && curr->right) {
      curr = curr->right;
      continue;
    }
    //If the compare was greater and has a left pointer, moves the current 
    //left for next compare
    else if(0 < cmp && curr->left) {
      curr = curr->left;
      continue;
    }
    //If the compare was the same, and we can't move down anymore, it
    //increments down the chain.
    else if(cmp == 0 && !curr->center && start->center) {
      track = start;
      curr->center = start->center;
      track->center = nullptr;
      delete track;
      tSize++;
      break;
    }
    //If the compare was the same, it moves down the word chain in both to 
    //compare the next letters
    else if(cmp == 0 && curr->center) {
      track = start;
          
      //Checks if the word is already in the chain and changes the 
      //node's end to true
      if(!start->center) {
        curr->end = true;
        track->center = nullptr;
        delete track;
	tSize++;
        break;
      }
     
      curr = curr->center;
      start = start->center;
      track->center = nullptr;    //Sets the previous letter's pointer to null
      delete track;
      continue;
    }
    curr->end = true;             //Otherwise, sets the node's end to true
    tSize++;
  }
  return;
}

/**
 * Finds information on the word in the tree
 * The pair contains this information
 * The first of the pair is true if the word is in the tree
 * The second is true if the word is a dead-end, meaning that
 * there are no other words that follow from it
 */
std::pair<bool,bool> TST::find(const std::string word) {

  //First is a word, second is a prefix
  std::pair<bool, bool> result (false,false);

  if(root == nullptr) {   // If tree doesn't exist, can't find anything
    return result;
  }

  bogNode *curr = this->root;    // Start at root

  int index = 0;                 // Loop through given word and tree
  while(index < (int) word.length()) {
    char c = word.at(index);     // Get character from word

    int check = charCmp(curr->data, c);   // Locate its position in tree
    if(!curr->right && !curr->left)       // Check if dead end
      result.second = true;

    // Checks where to go in the tree
    if(check < 0) {
      if(curr->right) {
        curr = curr->right;
        continue;
      }
      else {                              // Found dead end
        result.second = true;
        return result;
      }
    }
    else if(0 < check) {
      if(curr->left) {
        curr = curr->left;
        continue;
      }
      else {                              // Found dead end
        result.second = true;
        return result;
      }
    }
    else if(check == 0 && curr->center) {   // Found matching char
      
      // Check if end node and end of word
      if(curr->end != 0 && (index+1) == (int) word.length()){
        result.first = true;              // Mark word as found

	if(curr->right || curr->left || curr->center)  // Check for children
	  result.second = false;          // If children, no prefix
        return result;
      }
      curr = curr->center; // Go to next word
      index++;             // Go to next char
      continue;
    }
    else if(!curr->center && check == 0)  // matching char, but no center
    {
      // Check end node and end of word
      if(curr->end != 0 && (index+1) == (int) word.length()){
        result.first = true;      // Found word, record
        return result;
      }
      else
        return result;            // End, no center child, can't keep going
    }
    else if(curr->end != 0 && (index+1) == (int) word.length()) {
      result.first = true;
      return result;
    }
    else                          // Just return, no cases met
      return result;
  }
  result.second = false;
  return result;                  // End of search, just return result
}

/**
 * Destructs ternary tree
 */
TST::~TST(){
  if(root)                 // Delete tree if it exists
    destruct(root);
}

#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

#include <string>
#include <vector>
#include <utility>
#include <set>

class TST;
class bogNode;
class BoggleUtil{
  public:
  /**
   * Inserts the words from a given vector of strings starting at the center
   * of the vector, then adds it at the centers of the other sides, and so
   * on recursively.
   */
  static void insertWords(const std::vector<std::string> &word_list,int start,
                          int end, TST& t);

  /**
   * This method is a recursive method that will find all the possible words
   * on the board and stores them in a set of strings.
   */
  static void wordOnBoard(int position, const std::vector<std::string> board,
                          TST& t, std::set<std::string>* words, 
                          std::string currStr, std::vector<bool> visited, 
                          int min, int rows, int cols);

  /**
   * This method is a recursive method call that finds if the word inputted
   * by the user is on the board and is not in an acyclic path.
   */
  static bool findWOB(std::vector<int> &onBoard, 
                      const std::vector<std::string> board, 
                      const std::string& word_to_check, int position, 
                      int rows, int cols, int counter, 
                      std::vector<bool> visited);
};

/**
 * Class for the ternary tree object used to store the strings in.
 */
class TST {
  private:
    /**
     * Returns negative if b < c
     * 0 if b == c, positive if b > c 
     */
    int charCmp(char b, char c);

    /**
     * Destructor of the ternary tree
     */
    void destruct(bogNode* node);

  protected:
    bogNode* root = nullptr;    //Defaults root to nullptr
    int tSize = 0;              //Amounts of words in the tree
    
  public:
    /**
     * Inserts a string into the ternary tree.
     */
    void insert(const std::string word);

    /**
     * Method that returns a pair to determine if the word was in the
     * lexTree or not and whether it was a prefix or not
     */
    std::pair<bool,bool> find(const std::string word);


    ~TST();        //Deconstructor for TST
};

/**
 * Creates a node object to be used to insert into a ternary tree
 */
class bogNode{
  friend class TST;
  public:
    // Constructor goes here
    bogNode(const char &c): data(c) {
      data = c;                          //Initializes the data
      left = right = center = nullptr;   //Sets everything to nullptr
      end = false;                       //Defaults to false
    }
    
  private:
    bogNode* left;    // Children nodes
    bogNode* right;
    bogNode* center;
    char data;        // Data contained in node
    bool end;         // True if node is an end node
};

#endif // BOGGLEUTIL_H

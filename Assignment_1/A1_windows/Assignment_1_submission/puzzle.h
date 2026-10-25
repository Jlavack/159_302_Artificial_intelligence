/*159.302 Artificial Intelligence
John Lavack 20001249
*/

#ifndef PUZZLE_H
#define PUZZLE_H

#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

enum heuristicFunction{misplacedTiles, manhattanDistance};

class Puzzle{
        
private:

    string path;
    int pathLength;
    int hCost;
    int fCost;
    int depth; 
        
    int goalBoard[3][3];
    
    int x0, y0; //coordinates of the blank or 0-tile
    
    int board[3][3];
    
public:
    
    string strBoard;
    int puzzleKey;
    int publicfcost;
    int publiclength;

    Puzzle(const Puzzle &p); //Constructor
    Puzzle(string const elements, string const goal);
     
    void printBoard();
    
    int h(heuristicFunction hFunction);   
    void updateFCost(); 
    void updateHCost(heuristicFunction hFunction);
    void updateDepth(){
         depth++;
    }        
          
    bool goalMatch();
    string toString();
    string getString();
    
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveUp();
    bool canMoveDown();  
//----------------------------------------
//these functions will be useful for Progressive Deepening Search    
     bool canMoveLeft(int maxDepth);
     bool canMoveDown(int maxDepth);
     bool canMoveRight(int maxDepth);
     bool canMoveUp(int maxDepth);   
//----------------------------------------
      
    Puzzle * moveUp();
    Puzzle * moveRight();
    Puzzle * moveDown();
    Puzzle * moveLeft();  
     
    const string getPath();
    
    void setDepth(int d);
    int getDepth();
    
    int getPathLength();
    int getFCost();
    int getHCost();
    int getGCost(); 
    
};

#endif
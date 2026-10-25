/*159.302 Artifical Intelligence
John Lavack 20001249*/

#include "puzzle.h"
#include <cmath>
#include <assert.h>
#include <string>
#include <queue>
#include <vector>
#include <algorithm> 
#include <unordered_map>

using namespace std;

// int MaxQueueLength = 0;
// int NoStateExpansions = 0;
// int numOfDeletionsFromMiddleOfHeap =0;
// vector<Puzzle*> ExpandedList;	
// clock_t startTime;
// float actualRunningTime=0.0;	

//////////////////////////////////////////////////////////////
//constructor
//////////////////////////////////////////////////////////////
Puzzle::Puzzle(const Puzzle &p) : path(p.path){
	
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		    board[i][j] = p.board[i][j];
		    goalBoard[i][j] = p.goalBoard[i][j];
		}
	}	
	
	x0 = p.x0;
	y0 = p.y0;
	//path = p.path;
	pathLength = p.pathLength;
	hCost = p.hCost;
	fCost = p.fCost;	
	strBoard = toString(); //uses the board contents to generate the string equivalent
	puzzleKey=stoi(strBoard);
	depth = p.depth;

}

//////////////////////////////////////////////////////////////
//constructor
//inputs:  initial state, goal state
//////////////////////////////////////////////////////////////
Puzzle::Puzzle(string const elements, string const goal){
	int n;
	n = 0;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		    board[i][j] = elements[n] - '0';
			
		    if(board[i][j] == 0){
			    x0 = j;
			    y0 = i;
			 }
		    n++;
		} 
	}
		
	///////////////////////
	n = 0;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		    goalBoard[i][j] = goal[n] - '0';
		    n++;
		} 
	}		
	///////////////////////	
	path = "";
	pathLength=0;
	hCost = 0;
	fCost = 0;
	depth = 0;
	strBoard = toString();
	puzzleKey=stoi(strBoard);
}

void Puzzle::setDepth(int d){
	depth = d;
}

int Puzzle::getDepth(){
	return depth;
}

void Puzzle::updateHCost(heuristicFunction hFunction){
	hCost = h(hFunction);
}

void Puzzle::updateFCost(){
	fCost = hCost;																		//will only be GCost for Uniform Cost search
}

int Puzzle::getFCost(){
	return fCost;
}

int Puzzle::getHCost(){
	return hCost;
}

int Puzzle::getGCost(){
	return depth;
}

//Heuristic function implementation
int Puzzle::h(heuristicFunction hFunction){
	
	int sum=0;
	int h=0;
	int numOfMisplacedTiles=0;
	
	switch(hFunction){

		case misplacedTiles:
			for(int i=0; i<3; i++) {
				for(int j=0; j<3; j++) {
					if(board[i][j] != goalBoard[i][j]) {
						if(board[i][j] == 0) {
							numOfMisplacedTiles = numOfMisplacedTiles;					//not ot include blank tile
						}
						else {numOfMisplacedTiles++;}
					}
				}
			}	
                h = numOfMisplacedTiles; 
		        break;
				updateHCost(misplacedTiles);											//update the hcost with misplaced tile value
		         
		case manhattanDistance:
			for(int i=0; i < 3; i++){
				for(int j=0; j < 3; j++){	
					sum += (abs(board[i][j] - goalBoard[i][j]));   
				}
			}
				h = sum; 
		        break; 
				updateHCost(manhattanDistance);       									//update hcost with manhattan value
	};
	
	return h;
	
}

//converts board state into its string representation
string Puzzle::toString(){
  int n;
  string stringPath;
  n=0;
  for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){			    
		    stringPath.insert(stringPath.end(), board[i][j] + '0');
		    n++;
		} 
  }  
  return stringPath;
}

bool Puzzle::goalMatch(){																//My implementation
	bool result=false;
    
	int MatchingTiles = 0;
 
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			if(board[i][j] == goalBoard[i][j]) {
				MatchingTiles ++;
			}
		}
	}

	if(MatchingTiles == 9) { result = true;}
	else {result = false;}
	return result;
}

string Puzzle::getString(){
	return strBoard;
}

const string Puzzle::getPath(){
	return path;
}

bool Puzzle::canMoveLeft(){
  return (x0 > 0);
	
}

bool Puzzle::canMoveRight(){

   return (x0 < 2);
	
}

bool Puzzle::canMoveUp(){

   return (y0 > 0);
	
}

bool Puzzle::canMoveDown(){

   return (y0 < 2);
	
}

///////////////////////////////////////////////
//these functions will be useful for Progressive Deepening Search 

bool Puzzle::canMoveLeft(int maxDepth){													//My code
  	
  	bool m=false;
	
	if (x0 != 0) {
		m = true;
	}

  	return m; 
}

bool Puzzle::canMoveRight(int maxDepth){												//My code
   
  	bool m=false;

	if (x0 != 2) {
		m = true;
	}

  	return m; 
}

bool Puzzle::canMoveUp(int maxDepth){													//My code
   
  	bool m=false;

	if (y0 != 0) {
		m = true;
	}

  	return m; 
}

bool Puzzle::canMoveDown(int maxDepth){													//My code
   
  	bool m=false;
  	
	if (y0 != 2) {
		m = true;
	}

  	return m; 
}

///////////////////////////////////////////////

Puzzle *Puzzle::moveLeft(){
	
	Puzzle *p = new Puzzle(*this);
	
	
   if(x0 > 0){
		
		p->board[y0][x0] = p->board[y0][x0-1];
		p->board[y0][x0-1] = 0;
		
		p->x0--;
		
		p->path = path + "L";
		p->pathLength = pathLength + 1;  
		p->depth = depth + 1; 
		
		
	}
	p->strBoard = p->toString();

	return p;
	
}

Puzzle *Puzzle::moveRight(){
	
   Puzzle *p = new Puzzle(*this);
	
	
   if(x0 < 2){
		
		p->board[y0][x0] = p->board[y0][x0+1];
		p->board[y0][x0+1] = 0;
		
		p->x0++;
		
		p->path = path + "R";
		p->pathLength = pathLength + 1; 
     	
		p->depth = depth + 1;
		
	}
	
	p->strBoard = p->toString();
	
	return p;
	
}

Puzzle *Puzzle::moveUp(){
	
   Puzzle *p = new Puzzle(*this);
	
	
   if(y0 > 0){
		
		p->board[y0][x0] = p->board[y0-1][x0];
		p->board[y0-1][x0] = 0;
		
		p->y0--;
		
		p->path = path + "U";
		p->pathLength = pathLength + 1;  
	
		p->depth = depth + 1;
		
	}
	p->strBoard = p->toString();
	
	return p;
	
}

Puzzle *Puzzle::moveDown(){
	
   Puzzle *p = new Puzzle(*this);
	
	
   if(y0 < 2){
		
		p->board[y0][x0] = p->board[y0+1][x0];
		p->board[y0+1][x0] = 0;
		
		p->y0++;
		
		p->path = path + "D";
		p->pathLength = pathLength + 1;  
		
		p->depth = depth + 1;
		
	}
	p->strBoard = p->toString();	
	
	return p;
	
}

/////////////////////////////////////////////////////

void Puzzle::printBoard(){
	cout << "board: "<< endl;
	for(int i=0; i < 3; i++){
		for(int j=0; j < 3; j++){	
		  cout << endl << "board[" << i << "][" << j << "] = " << board[i][j];
		}
	}
	cout << endl;
	
}

int Puzzle::getPathLength(){
	return pathLength;
}

// bool operator==(const Puzzle &p) const {
// 	if(strBoard ==p.strBoard) {
// 	return true;}
// 	else {return false;}
// }

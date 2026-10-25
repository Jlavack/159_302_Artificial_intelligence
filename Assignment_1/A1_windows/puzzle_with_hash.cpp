/*159.302 Artifical Intelligence

John Lavack 20001249*/

#include "puzzle.h"
#include <cmath>
#include <assert.h>
#include <string>
#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T_S 1000000000

using namespace std;

int maxQLength = 0;
int numOfStateExpansions = 0;
int numOfDeletionsFromMiddleOfHeap =0;
vector<Puzzle*> ExpandedList;	
clock_t startTime;
float actualRunningTime=0.0;	


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
	puzzleKey = stoi(strBoard);
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
	puzzleKey = stoi(strBoard);
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
	fCost = hCost;																
}

int Puzzle::getFCost(){
	return fCost;
}

int Puzzle::getHCost(){
	return hCost;
}

int Puzzle::getGCost(){
	return pathLength;
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
	p->puzzleKey = stoi(strBoard);

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
	p->puzzleKey = stoi(strBoard);
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
	p->puzzleKey = stoi(strBoard);
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
	p->puzzleKey = stoi(strBoard);
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
// //-------------------------------HASH_Functions--------------------------//
class HashTableEntry {
   public:
      int k;								//use integer of boardstate
	  int v;								//value to store. FCost for heuristics, depth for uniform cost
      HashTableEntry(int k, int v) {
         this->k= k;
		 this->v = v; 
		}
};

class HashMapTable {
   private:
      HashTableEntry **t;
   public:
      HashMapTable() {
         t = new HashTableEntry * [T_S];
         for (int i = 0; i< T_S; i++) {
            t[i] = 0;
         }
      }
      int HashFunc(int k) {
        //  float intpart, c = (sqrt(5)-1)/2;
		// 	float frac;
		// 	int x1 =  k % 1000;
		// 	int x2 = (k % 1000000)/1000;
		// 	int x3 = (k % 1000000000)/1000000;
		// 	//int hash = ((x1+x2+x3)*1.61803398);// % T_S;
		// 	int hash = floor(T_S *modf(((x1+x2+x3)*1.61803398), &frac));
		// 	cout << hash << endl;
		//  return hash;
		 return k % T_S;
      }
      void Insert(int k, int v) {
         int h = HashFunc(k);
         while (t[h] != NULL && t[h]->k != k) {
			cout << "reshash: " ;
            h = HashFunc(h + 1);
         }
         if (t[h] != NULL)
            delete t[h];
         t[h] = new HashTableEntry(k, v);
      }
      bool SearchKey(int k) {
         int h = HashFunc(k);
         while (t[h] != NULL && t[h]->k != k) {
            h = HashFunc(h + 1);
         }
         if (t[h] == NULL)
            return false; //in the hastable
         else
            return true;
      }

      bool IsNewValueLessThanExisting(int k, int x) {
         int h = HashFunc(k);
        //  while (t[h] != NULL && t[h]->k != k) {
        //     h = HashFunc(h + 1);
        //  }
         if (t[h]->v > x)
            return true; //existing value is less than new one
         else
            return false;
      }

      void Remove(int k) {
         int h = HashFunc(k);
         while (t[h] != NULL) {
            if (t[h]->k == k)
               break;
            h = HashFunc(h + 1);
         }
         if (t[h] == 0) {
            // cout<<"No Element found at key "<<k<<endl;
            return;
         } else {
            delete t[h];
         }
        //  cout<<"Element Deleted"<<endl;
      }
    //   ~HashMapTable() {
    //      for (int i = 0; i < T_S; i++) {
    //            delete t[i];
    //            delete[] t;
    //      }
    //   }
};

// //-------------------------------Helper_functions--------------------------//
struct compare{																							//Orders the heap via the minimum condition for a* implementation
	bool operator()(Puzzle* lhs,   Puzzle* rhs) {
		return (lhs->getFCost() > rhs->getFCost());
	}
};

struct compare_UC{																						//Orders the heap via the minimum condition for UC implementation
	bool operator()(Puzzle* lhs,   Puzzle* rhs) {
		return (lhs->getDepth() > rhs->getDepth());
	}
};

void GoalDiagnostics(Puzzle* state) {																	//prints diagnostics of puzzle
	cout << "GOAL REACHED: " << endl;                               							
	cout<< state->toString() << endl;
	cout << "Maximum Queue Length: " << maxQLength << endl;       	
	cout << "Path length: " << state->getPathLength() << endl;
	cout << "Number of state expansions: " << numOfStateExpansions << endl;
	cout << "NUmber of deletions from middle of heap: " << numOfDeletionsFromMiddleOfHeap << endl;
	cout << "Step sequence: " << state->getPath() << endl;
	actualRunningTime = ((float)(clock() - startTime)/*/CLOCKS_PER_SEC*/);
	cout << "RUNTIME: " << actualRunningTime << endl;
	return; 
	}	

void GenerateSuccessors_aStar(Puzzle* &min, vector<Puzzle*> *successorstate, heuristicFunction hFunction) {
	if(min->canMoveUp(3) == true) {																		//Check if can move up							
		Puzzle* nextstate = min->moveUp();																//if yes, make up node. Move previous state blank tile up one
		nextstate->updateHCost(hFunction);																//recalculate the h(cost)
		nextstate->updateFCost(); 			
		successorstate->push_back(nextstate);															//recalculate the g(cost) = h(cost)
	}

	if(min->canMoveRight(3) == true) {	
		Puzzle* nextstate = min->moveRight();
		nextstate->updateHCost(hFunction);
		nextstate->updateFCost();
		successorstate->push_back(nextstate); 
	}

	if(min->canMoveDown(3) == true) {	
		Puzzle* nextstate = min->moveDown();
		nextstate->updateHCost(hFunction);
		nextstate->updateFCost(); 
		successorstate->push_back(nextstate);
	}

	if(min->canMoveLeft(3) == true) {	
		Puzzle* nextstate = min->moveLeft();
		nextstate->updateHCost(hFunction);
		nextstate->updateFCost(); 
		successorstate->push_back(nextstate);
	}
}

void GenerateSuccessors_UC(Puzzle* &min, vector<Puzzle*> *successorstate) {
	if(min->canMoveUp(3) == true) {																//Check if can move up							
		Puzzle* nextstate = min->moveUp();														//if yes, make up node. Move previous state blank tile up one	
		successorstate->push_back(nextstate);													//UC uses depth, no need to update hcost
	}

	if(min->canMoveRight(3) == true) {	
		Puzzle* nextstate = min->moveRight();
		successorstate->push_back(nextstate); 
	}

	if(min->canMoveDown(3) == true) {	
		Puzzle* nextstate = min->moveDown();
		successorstate->push_back(nextstate);
	}

	if(min->canMoveLeft(3) == true) {	
		Puzzle* nextstate = min->moveLeft();
		successorstate->push_back(nextstate);
	}
}


// //-------------------------------DEBUGGING_Function-----------------------//
void DEBUGHEAP(vector<Puzzle*> minheap) {
	cout << "DEBUG HEAP" << endl;
	for(int i=0; i<minheap.size(); i++) {
		cout << minheap[i]->toString() << " : " << minheap[i]->getFCost() << " : " << minheap[i]->getPathLength() << endl;
	} cout << endl;
}

//-------------------------------Solver_functions--------------------------//

//hFunctions
void Solver(string start, string goal, heuristicFunction hFunction) {
	vector<Puzzle*> minheap;																			//create minheap
	HashMapTable *puzzleMap = new HashMapTable;
	HashMapTable *OpenList = new HashMapTable;
	Puzzle *root = new Puzzle(start, goal);             			  									//create root node
	root->updateHCost(hFunction);                                										//initialise its cost						                                                    //initialise the steps
	minheap.push_back(root);
	make_heap(minheap.begin(), minheap.end(), compare());												//make vector a heap
	                                                      						
	while(!minheap.empty()) {																			//until the queue is empty
		startTime = clock();																			     
        pop_heap(minheap.begin(), minheap.end());														//take the top element and examine it (line 592 is examination)
		Puzzle* min = minheap.back();
		minheap.pop_back();
		
        if(min->goalMatch()==true) {																	//If this is the goal state, print diagnostics and end process
			GoalDiagnostics(min);
			delete puzzleMap;
			delete OpenList;
			return;																
			}	
		if (puzzleMap->SearchKey(stoi(min->strBoard)) == true) {																	//check if state in hand is in expanded list. If yes, don't add it to heap
			continue;
		} else { 																						//if no, add to expanded list and generate successors
			puzzleMap->Insert(stoi(min->strBoard), min->getFCost());
			numOfStateExpansions ++;
			// cout << endl << "MAKING KIDS of " << min->strBoard << endl;
			vector<Puzzle*> Successors;
			GenerateSuccessors_aStar(min, &Successors, hFunction); 

			for (int i =0; i<Successors.size(); i++ ){
				// cout << "Checking if: " << Successors[i]->strBoard << " in explist" << endl;
				if(puzzleMap->SearchKey(stoi(Successors[i]->strBoard)==true )) { 
					delete Successors[i];
					continue;
				} else if (OpenList->SearchKey(stoi(Successors[i]->strBoard))==true) {
					if(OpenList->IsNewValueLessThanExisting(stoi(Successors[i]->strBoard), Successors[i]->getFCost())==true) {  //yes, new value is less
						OpenList->Remove(stoi(Successors[i]->strBoard)); //remove old value
						OpenList->Insert(stoi(Successors[i]->strBoard), Successors[i]->getFCost()); //add new value
						numOfDeletionsFromMiddleOfHeap++;
						delete Successors[i];
					}
				} else {
					minheap.push_back(Successors[i]);
					OpenList->Insert(stoi(Successors[i]->strBoard), Successors[i]->getFCost());
					make_heap(minheap.begin(), minheap.end(), compare());
					maxQLength++;
				} 
			}
			Successors.clear();
		}
		delete min;
	}																															
	delete puzzleMap;
	delete OpenList;
}

//Uniform Cost Solver
void UniformCostSolver(string start, string goal) {
	vector<Puzzle*> minheap;																			//create minheap
	HashMapTable *puzzleMap = new HashMapTable;
	HashMapTable *OpenList = new HashMapTable;
	Puzzle *root = new Puzzle(start, goal);             			  									//create root node
	root->updateFCost();                                												//initialise its cost						                                                    //initialise the steps
	minheap.push_back(root);
	make_heap(minheap.begin(), minheap.end(), compare_UC());												//make vector a heap
	                                                      						
	while(!minheap.empty()) {																			//until the queue is empty
		startTime = clock();																			     
        pop_heap(minheap.begin(), minheap.end());														//take the top element and examine it (line 592 is examination)
		Puzzle* min = minheap.back();
		minheap.pop_back();
		
		// cout << "Now expanding " << stoi(min->strBoard) << endl;

        if(min->goalMatch()==true) {																	//If this is the goal state, print diagnostics and end process
			GoalDiagnostics(min);
			delete OpenList;
			delete puzzleMap;	
			return;																
			}	
		if (puzzleMap->SearchKey(stoi(min->strBoard)) == true) {											//check if state in hand is in expanded list. If yes, don't add it to heap
			continue;
		} else { 																						//if no, add to expanded list and generate successors
			puzzleMap->Insert(stoi(min->strBoard), min->getDepth());
			numOfStateExpansions ++;
			vector<Puzzle*> Successors;
			GenerateSuccessors_UC(min, &Successors); 

			for (int i =0; i<Successors.size(); i++ ){
				if(puzzleMap->SearchKey(stoi(Successors[i]->strBoard)) == true) { 
					// cout << stoi(min->strBoard) << " is IN EXPANDED LIST" << endl;
					delete Successors[i];
					continue;
				} else if (OpenList->SearchKey(stoi(Successors[i]->strBoard))==true) {
					if(OpenList->IsNewValueLessThanExisting(stoi(Successors[i]->strBoard), Successors[i]->getDepth())==true) {  //yes, new value is less
						OpenList->Remove(stoi(Successors[i]->strBoard)); //remove old value
						OpenList->Insert(stoi(Successors[i]->strBoard), Successors[i]->getDepth()); //add new value
						numOfDeletionsFromMiddleOfHeap++;
					}
					delete&Successors[i];
					continue;
				} else {
					minheap.push_back(Successors[i]);
					cout << "making a hash of: " << stoi(Successors[i]->strBoard) << ": ";
					OpenList->Insert(stoi(Successors[i]->strBoard), Successors[i]->getDepth());
					make_heap(minheap.begin(), minheap.end(), compare_UC());
					maxQLength++;
					exit(100);
				} 
			}
			Successors.clear();
		}
		delete min;
	}																															
	 delete puzzleMap;
	 delete OpenList;
}


int main() {
///////////////////////////////////////////////////////////////////////////////////////////////////////////
	const string start = "120483765";
	// const string start = "208135467";
	// const string start = "704851632";
	// const string start = "536407182";
	// const string start = "638541720";

	const string goal = "123456780";

	cout << "//-----------------------------------START-----------------------------------//" << endl;
	// cout << "Uniform Cost: " << endl;
	// cout << "Misplaced tiles: " << endl;
	// cout << "Manhattan Distance: " << endl;
	
	cout << "Start state: " << start << endl;
	
	// UniformCostSolver(start, goal);
	// Solver(start, goal, misplacedTiles);
	Solver(start, goal, manhattanDistance);
	
}


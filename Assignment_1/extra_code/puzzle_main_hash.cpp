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
#include <unordered_set>

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

bool IsSameState (Puzzle* s1, Puzzle* s2) {																//Checks if two states have same board state
	if(s1->strBoard != s2->strBoard) { return false;}
	return true;
}

bool IsSmallerCost (Puzzle* s1, Puzzle* s2) {															//Check which board has smaller fCost
	if(s1->getFCost() < s2->getFCost()) { return false;}
	return true;
}

bool IsShallower (Puzzle* s1, Puzzle* s2) {																//Check which board has smaller fCost
	if(s1->getDepth() < s2->getDepth()) { return false;}
	return true;
}

bool IsInExpandedList(Puzzle *currentstate) {															//Checks if boardstate is in expanded list
	bool flag = false;
	for(int i=0; i < ExpandedList.size(); i++) {
		if(IsSameState(currentstate, ExpandedList[i])) {
			return true;
		}
	} return false;
}

bool check_key(unordered_map<string, Puzzle> puzzleMap, string key) {
	if (puzzleMap.count(key) == 0) {
		return false ;
	} else { return true;}
}

bool IsInQueue(Puzzle* currentstate, vector<Puzzle*> q) {												//checks if board state is in Queue. Keeps only the smaller fCost state
	bool flag = false;
	for(int i=0; i < q.size(); i++) {
		if(IsSameState(currentstate, q[i])) {															//if same board state, check size of f(cost) next
			if(IsSmallerCost(currentstate, q[i])) {														//if new state is cheaper, pass back true
				swap(*q[i], *currentstate);
				return true;
			} else {
				return false;
			}
		} 	
	} 
	return false;
}

bool IsInQueue_UC(Puzzle* currentstate, vector<Puzzle*> q) {											//checks if board state is in Queue. Keeps only the smaller fCost state
	bool flag = false;
	for(int i=0; i < q.size(); i++) {
		if(IsSameState(currentstate, q[i])) {															//if same board state, check size of f(cost) next
			if(IsShallower(currentstate, q[i])) {														//if new state is cheaper, pass back true
				q[i]->setDepth(currentstate->getDepth());
				return true;
			} else {
				return false;
			}
		} 	
	} 
	return false;
}

void GoalDiagnostics(Puzzle* state) {																	//prints diagnostics of puzzle
	cout << "GOAL REACHED: " << endl;                               							
	cout<< state->toString() << endl;
	cout << "Maximum Queue Length: " << maxQLength << endl;       	
	cout << "Path length: " << state->getPathLength() << endl;
	cout << "Number of state expansions: " << numOfStateExpansions << endl;
	cout << "NUmber of deletions from middle of heap: " << numOfDeletionsFromMiddleOfHeap << endl;
	cout << "Step sequence: " << state->getPath() << endl;
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
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
	unordered_map<string, Puzzle> puzzleMap;
	Puzzle *root = new Puzzle(start, goal);             			  									//create root node
	root->updateHCost(hFunction);                                										//initialise its cost						                                                    //initialise the steps
	minheap.push_back(root);
	make_heap(minheap.begin(), minheap.end(), compare());												//make vector a heap
	                                                      						
	while(!minheap.empty()) {																			//until the queue is empty
		startTime = clock();																			     
        pop_heap(minheap.begin(), minheap.end());														//take the top element and examine it (line 592 is examination)
		Puzzle* min = minheap.back();
		minheap.pop_back();
		// cout << "Now trying to expand " << min->strBoard << endl;
		
        if(min->goalMatch()==true) {																	//If this is the goal state, print diagnostics and end process
			GoalDiagnostics(min);	
			return;																
			}	

		// cout << endl << "prefligth explist check: " << endl;
		// for(auto p : puzzleMap) {
		// 	cout << p.first << " depth: " << p.second.getDepth() <<  endl;
		// }
		// cout << endl << "CHECKING PUZZLEMAP" << endl;
		if (check_key(puzzleMap, min->strBoard)==true /*IsInExpandedList(min)*/) {																	//check if state in hand is in expanded list. If yes, don't add it to heap
			// cout << min->strBoard << " Is in explist" << endl;
			continue;
		} else { 																						//if no, add to expanded list and generate successors
			// cout << min->strBoard << " Is not in explist, adding it" << endl;
			puzzleMap.insert({min->strBoard, *min});
			// cout << endl << "POST EXPLIST CHECK EXPLIST" << endl;
			// for(auto p : puzzleMap) {
			// 	cout << p.first << " depth: " << p.second.getDepth() <<  endl;
			// }
			//ExpandedList.push_back(min);
			numOfStateExpansions ++;
			// cout << endl << "MAKING KIDS of " << min->strBoard << endl;
			vector<Puzzle*> Successors;
			GenerateSuccessors_aStar(min, &Successors, hFunction); 

			// cout << "printing successor states" << endl;
			// for (int i =0; i<Successors.size(); i++ ){
			// 	cout << Successors[i]->strBoard << endl;
			// } cout << endl;
			// cout << endl << "CHECKING SUCCESSORS IN EXPLIST: " << endl;
			for (int i =0; i<Successors.size(); i++ ){
				// cout << "Checking if: " << Successors[i]->strBoard << " in explist" << endl;
				if(check_key(puzzleMap, Successors[i]->strBoard)==true     /*IsInExpandedList(Successors[i])*/) { 
					// cout << "yes: " << Successors[i]->strBoard << " is in explist" << endl;
					// for(auto p : puzzleMap) {
					// cout << p.first << " depth: " << p.second.getDepth() <<  endl;
					// } cout << endl;

					delete Successors[i];
				} else if (IsInQueue(Successors[i],minheap)) {
					// cout << " and in the queue. " << endl;
					numOfDeletionsFromMiddleOfHeap ++;
					delete Successors[i];
				} else {
					// cout << "Not in explist, Adding " << Successors[i]->strBoard << " to the queue" << endl;
					minheap.push_back(Successors[i]);
					make_heap(minheap.begin(), minheap.end(), compare());
					maxQLength++;
					//cout << "ADDING " << Successors[i]->toString() << " TO HEAP " << endl;
				} 
			}

			// cout << endl << "SUCCESSOR STATES CHECKED " << endl;

			// DEBUGHEAP(minheap);

			// cout << endl << "Starting again" << endl;
			//exit(100);
			Successors.clear();
		}
	}																															
     cout << "QUEUE is empty, no solution found" << endl;												//if no solution is found
}

//Uniform Cost Solver
void UniformCostSolver(string start, string goal) {
	vector<Puzzle*> minheap;																			//create minheap
	Puzzle *root = new Puzzle(start, goal);             			  									//create root node
	root->updateFCost();                                												//initialise its cost						                                                    //initialise the steps
	minheap.push_back(root);
	make_heap(minheap.begin(), minheap.end(), compare_UC());												//make vector a heap
	                                                      						
	while(!minheap.empty()) {																			//until the queue is empty
		startTime = clock();																			     
        pop_heap(minheap.begin(), minheap.end());														//take the top element and examine it (line 592 is examination)
		Puzzle* min = minheap.back();
		minheap.pop_back();
		
        if(min->goalMatch()==true) {																	//If this is the goal state, print diagnostics and end process
			GoalDiagnostics(min);	
			return;																
			}	

		if (IsInExpandedList(min)) {																	//check if state in hand is in expanded list. If yes, don't add it to heap
			continue;
		} else { 																						//if no, add to expanded list and generate successors
			ExpandedList.push_back(min);
			numOfStateExpansions ++;
																										//now generate each successor node in the order U, R, D, L
			vector<Puzzle*> Successors;
			GenerateSuccessors_UC(min, &Successors); 

			// cout << "printing successor states" << endl;
			// for (int i =0; i<Successors.size(); i++ ){
			// 	cout << Successors[i]->toString() << endl;
			// }

			for (int i =0; i<Successors.size(); i++ ){
				if(IsInExpandedList(Successors[i])) { 
					delete Successors[i];
				} else if (IsInQueue_UC(Successors[i],minheap)) {
					numOfDeletionsFromMiddleOfHeap ++;
					delete Successors[i];
				} else {
					minheap.push_back(Successors[i]);
					make_heap(minheap.begin(), minheap.end(), compare_UC());
					maxQLength++;
					//cout << "ADDING " << Successors[i]->toString() << " TO HEAP " << endl;
				} 
			}
		}
	}																															
     cout << "QUEUE is empty, no solution found" << endl;	
}


int main() {

	// unordered_map<int, Puzzle> puzzleMap;

	// // // unordered_set<Puzzle, puzzleHasher, puzzleComparator> puzzleMap;

 	// Puzzle *state1 = new Puzzle("120345678", "123456780");
	// state1->setDepth(4);
	// cout << state1->strBoard << " " << state1->getDepth() << endl;

    // Puzzle *state2 = new Puzzle("123456078", "123456780");
	// cout << state2->strBoard << " " << state2->getDepth() << endl;

    // Puzzle *state3 = new Puzzle("120345678", "123456780");
	// state3->setDepth(1);
	// cout << state3->strBoard << " " << state3->getDepth() << endl;

	// cout << "loading puzzleMap" << endl;
	// //int key = state1->puzzleKey;
	// // cout << key << endl;
	// puzzleMap.insert({state1->puzzleKey, *state1});
	// puzzleMap.insert({state2->puzzleKey, *state2});
	// puzzleMap.insert({state3->puzzleKey, *state3});

	// // puzzleMap[state2->puzzleKey] = *state3;
	// cout << "FIRST PUZZLEMPA CHECK: " << endl;
	// for(auto p : puzzleMap) {
	// 	cout << p.first << " depth: " << p.second.getDepth() <<  endl;
	// }

	// Puzzle *state4 = new Puzzle("187654320", "123456780");

	// cout << endl << "check1: " << endl;
	// if(check_key(puzzleMap, state4->puzzleKey)) {
	// 	cout << "not Present" << endl;		
	// } else {cout << "present" << endl;}

	// // if(check_key(puzzleMap, state3)) 
	
	// // cout << "printing puzzleMap" << endl;

	// for(auto p : puzzleMap) {
	// 	cout << p.first << " depth: " << p.second.getDepth() <<  endl;
	// }





///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// const string start = "120483765";
	const string start = "208135467";
	// const string start = "704851632";
	// const string start = "536407182";
	// const string start = "638541720";

	const string goal = "123456780";

	cout << "//-----------------------------------START-----------------------------------//" << endl;
	cout << "Start state: " << start << endl;
	Solver(start, goal, misplacedTiles);
	// Solver(start, goal, manhattanDistance);
	// UniformCostSolver(start, goal);
}


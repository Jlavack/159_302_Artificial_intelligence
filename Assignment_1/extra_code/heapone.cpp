#include "puzzle.h"
#include <cmath>
#include <assert.h>
#include <string>
#include <queue>
#include <vector>
#include <algorithm> 

using namespace std;

int MaxQueueLength = 0;
int NoStateExpansions = 0;
int numOfDeletionsFromMiddleOfHeap =0;

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
	depth = p.depth;
	publicfcost = p.fCost;
    publiclength = p.pathLength;
	
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
	publicfcost=fCost;
    publiclength = getPathLength();
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
	int gCost = getGCost();
	fCost = hCost + gCost;																		//will only be GCost for Uniform Cost search
	publicfcost = fCost;
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

	//display boards for debugging
	/*
	cout << "DEBUG TEST board: " << endl;
	for(int i=0;i<3;i++) {
		cout << endl;
		for(int j=0;j<3;j++) {
			cout << board[i][j] << " " ;
		}
	}
	cout << endl;
	/*
	cout << endl;
	cout << "DEBUG TEST goalDoard: " << endl;
	for(int i=0; i < 3; i++){
		cout << endl;
		for(int j=0; j < 3; j++){	
			cout << goalBoard[i][j] << " ";
		}
	}    
	cout << endl;*/
	
	switch(hFunction){

		case misplacedTiles:
		//cout << "Calcualting Misplaced Tiles value:" << endl;							//DEBUG uncomment to test
				//place your implementation here
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
				//cout << "DEBUG TEST MISPLACED TILES RESULT: " << h << endl;			//DEBUG uncomment to test				
		        break;
				updateHCost(misplacedTiles);											//update the hcost with misplaced tile value
		         
		case manhattanDistance:
		//cout << "Calculating Manhattan Distance..." << endl;							//DEBUG uncomment to test
		        //place your implementation here	
			for(int i=0; i < 3; i++){
				for(int j=0; j < 3; j++){	
					sum += (abs(board[i][j] - goalBoard[i][j]));   
				}
			}
				h = sum; 
				//cout << "DEBUG TEST MANHATTAN RESULT : " << h << endl;				//DEBUG uncomment to test				
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
  
//  cout << "toString = " << stringPath << endl;
  
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

struct compare{																							//Orders the heap via the minimum condition
	bool operator()(Puzzle* lhs,   Puzzle* rhs) {
		return (lhs->getFCost() < rhs->getFCost());
	}
};

int contains(vector<Puzzle*> &minheap, Puzzle* nextstate) {
    int checker;

    for(int i=0; i < minheap.size(); i++) {
         if((nextstate->toString() == minheap[i]->toString())&&(nextstate->getFCost() < minheap[i]->getFCost())) {
             checker = 1;
             break;
        } else if((nextstate->toString() == minheap[i]->toString())&&(nextstate->getFCost() > minheap[i]->getFCost())){ //next state is larger and should not be added
            checker = 2;
            break;
         } else if((nextstate->toString() == minheap[i]->toString())&&(nextstate->getFCost() == minheap[i]->getFCost())) { //same as existing state, so don't add it
            checker = 2;
            break;
        } else if ((nextstate->toString() != minheap[i]->toString())) {
            checker = 3;}
            break;
    } return checker;
}
    
void checkQueue(Puzzle* nextstate, vector<Puzzle*> &minheap, vector<Puzzle*> &garbageheap) {
     int checker;
     int i=0;
     while(i < minheap.size()) {
        checker = contains(minheap, nextstate);
        cout << "DEBUG UP CHECKER: " << checker << endl;
        switch(checker) {
            case 0 : //case where new state is in Q exactly; discard
            cout << "case 0: discard existing state" << endl;
            garbageheap.push_back(nextstate);
            numOfDeletionsFromMiddleOfHeap++;
            //i++;
            continue;

            case 1 : //case where new state is in Q and has smaller FCost; add to queue
            cout << "case 1: replaceing with smaller element" << endl;
            swap(minheap[i], nextstate);
            make_heap(minheap.begin(), minheap.end(), compare());
            numOfDeletionsFromMiddleOfHeap++;
           // i++;
            continue;

            case 2 : //case where new state is in Q and has larger FCost; do not add to Q
            cout << "case 2: not pushing to heap" << endl;
            garbageheap.push_back(nextstate);
            //i++;
            continue;

            case 3 : //case where new state is not in Q, add to queue
            cout << "case 3: Pushing to heap next state" << endl;
            minheap.push_back(nextstate);
            MaxQueueLength ++;
            make_heap(minheap.begin(), minheap.end(), compare());
            ///i++;
            continue;

            default : 
            cout << "case default: Pushing to heap next state" << endl;
            minheap.push_back(nextstate);
            MaxQueueLength ++;
            make_heap(minheap.begin(), minheap.end(), compare());
            //i++;
            continue;
        }
     }
}


//-------------------------------Solver functions--------------------------//
//Misplaced Tiles
void MisplacedTilesSolver(string start, string goal) {
	vector<Puzzle*> ExpandedList;																		//holds expanded list
	priority_queue<Puzzle*, vector<Puzzle*>, compare> pq;                								//create priority queue to store nodes of search tree
    Puzzle *root = new Puzzle(start, goal);             			  									//create root node
    root->updateHCost(misplacedTiles);                                									//initialise its cost						                                                    //initialise the steps
    pq.push(root);                                                           							//push onto heap

	while(!pq.empty()) {																				//until the queue is empty
        Puzzle* min = pq.top();                                                							//find node with least cost
        pq.pop();                                                            							//remove node from heap
        NoStateExpansions ++; 																			//increase state expansions
		ExpandedList.push_back(min);																	//push visitied node to expanded list
		                                               													//increase number of state expansions
        if(min->goalMatch()==true) {																	//If this is hte goal state
			cout << "GOAL REACHED: " << endl;                               							//print diagnostics
            cout<< min->toString() << endl;
            cout << "Maximum Queue Length: " << MaxQueueLength << endl;       	
            cout << "Path length: " << min->getPathLength() << endl;
            cout << "Number of state expansions: " << NoStateExpansions << endl;
            cout << "Step sequence: " << min->getPath() << endl;
            return;
        } else if(min->goalMatch()==false) {															//else expand the node
		
			if(min->canMoveUp(3) == true) {																//check up movement potential. 
			//	cout << "DEBUG I CAN MOVE UP!!";
				Puzzle* nextstate;
				nextstate = min->moveUp();
																				//otherwise, add to queue
				nextstate->updateHCost(misplacedTiles);													//get hueristic
				nextstate->updateFCost();																//update the state
		//		cout << endl << "DEBUG UP: " <<nextstate->toString() << " fcost = " << nextstate->getFCost();
				if(find(ExpandedList.begin(), ExpandedList.end(), nextstate) != ExpandedList.end()) {	//do not add if in expanded list
			//		cout << "DEBUG: I AM IN THE EXPANDED LIST" << endl;
					delete nextstate;																	//delete nextstate
				} else {				
					pq.push(nextstate);																	//push onto queue
					MaxQueueLength++;																	//increase max queue size
			//		cout << endl << "TESTING QUEUE: " << pq.size() << endl;
				}
			}

			if(min->canMoveRight(3) == true) {															//check right movement potential. 
			//	cout << "DEBUG I CAN MOVE RIGHT!!";
				Puzzle* nextstate;
				nextstate = min->moveRight();
				if(find(ExpandedList.begin(), ExpandedList.end(), nextstate) != ExpandedList.end()) {	//do not add if in expanded list
			//		cout << "DEBUG: I AM IN THE EXPANDED LIST" << endl;
					delete nextstate;																	//delete nextstate
				} else {																				//otherwise, add to queue
					nextstate->updateHCost(misplacedTiles);												//get hueristic
					nextstate->updateFCost();															//update the state
			//		cout << endl << "DEBUG RIGHT: " <<nextstate->toString() << " fcost = " << nextstate->getFCost();
					pq.push(nextstate);																	//push onto queue
					MaxQueueLength++;																	//increase max queue size
			//		cout << endl << "TESTING QUEUE: " << pq.size() << endl;
				}
			}

			if(min->canMoveDown(3) == true) {															//check down movement potential. 
			//	cout << "DEBUG I CAN MOVE DOWN!!";
				Puzzle* nextstate;
				nextstate = min->moveDown();
				if(find(ExpandedList.begin(), ExpandedList.end(), nextstate) != ExpandedList.end()) {	//do not add if in expanded list
			//		cout << "DEBUG: I AM IN THE EXPANDED LIST" << endl;
					delete nextstate;																	//delete nextstate
				} else {																				//otherwise, add to queue
					nextstate->updateHCost(misplacedTiles);												//get hueristic
					nextstate->updateFCost();															//update the state
			//		cout << endl << "DEBUG DOWN: " <<nextstate->toString() << " fcost = " << nextstate->getFCost();
					pq.push(nextstate);																	//push onto queue
					MaxQueueLength++;																	//increase max queue size
			//		cout << endl << "TESTING QUEUE: " << pq.size() << endl;
				}
			}

			if(min->canMoveLeft(3) == true) {																//check up movement potential. 
			//	cout << "DEBUG I CAN MOVE LEFT!!";
				Puzzle* nextstate;
				nextstate = min->moveLeft();
				if(find(ExpandedList.begin(), ExpandedList.end(), nextstate) != ExpandedList.end()) {	//do not add if in expanded list
			//		cout << "DEBUG: I AM IN THE EXPANDED LIST" << endl;
					delete nextstate;																	//delete nextstate
				} else {																				//otherwise, add to queue
					nextstate->updateHCost(misplacedTiles);												//get hueristic
					nextstate->updateFCost();															//update the state
			//		cout << endl << "DEBUG Left: " <<nextstate->toString() << " fcost = " << nextstate->getFCost();
					pq.push(nextstate);																	//push onto queue
					MaxQueueLength++;																	//increase max queue size
			//		cout << endl << "TESTING QUEUE: " << pq.size() << endl;
				}
			}
		}

			//Puzzle* Top = pq.top();
			//cout << endl << "TOP OF QUEUE: " << Top->toString() << " fcost = " << Top->getFCost();
			
			//cout << endl << "DEBUG EXPANDED LIST: " << endl;
			//for(auto & element : ExpandedList) { cout << element->toString() << endl;}
	}
}

//Manhattan Distance
void ManhattanDistanceSolver(string start, string goal) {
	vector<Puzzle*> ExpandedList;																		//holds expanded list
	priority_queue<Puzzle*, vector<Puzzle*>, compare> pq;                								//create priority queue to store nodes of search tree
	vector<Puzzle*> minheap;
    vector<Puzzle*> garbageheap;
	
	Puzzle *root = new Puzzle(start, goal);             			  									//create root node
    root->updateHCost(manhattanDistance);                                									//initialise its cost						                                                    //initialise the steps
    //pq.push(root); 
	minheap.push_back(root);
	make_heap(minheap.begin(), minheap.end(), compare());                                                        							//push onto heap

	while(!minheap.empty()) {																				//until the queue is empty     
        pop_heap(minheap.begin(), minheap.end());
		Puzzle* min = minheap.back();
		//cout <<"DEBUG " << min->toString() << endl; 
		minheap.pop_back();
        
        if(min->goalMatch()==true) {																	//If this is hte goal state
			cout << "GOAL REACHED: " << endl;                               							//print diagnostics
            cout<< min->toString() << endl;
            cout << "Maximum Queue Length: " << MaxQueueLength << endl;       	
            cout << "Path length: " << min->getPathLength() << endl;
            cout << "Number of state expansions: " << NoStateExpansions << endl;
			cout << "NUmber of deletions from middle of heap: " << numOfDeletionsFromMiddleOfHeap << endl;
			cout << "Step sequence: " << min->getPath() << endl;
            return;

        } else if(min->goalMatch()==false) {															//else expand the node
			ExpandedList.push_back(min);
			NoStateExpansions ++; 																			//increase state expansions															
		
			if(min->canMoveUp(3) == true) {																//check up movement potential. 
			//	cout << "DEBUG I CAN MOVE UP!!";
				Puzzle* nextstate;
				nextstate = min->moveUp();
				nextstate->updateHCost(manhattanDistance);												//get hueristic
				nextstate->updateFCost();

                checkQueue(nextstate, minheap, garbageheap);
            }																
			//		cout << endl << "TESTING QUEUE: " << pq.size() << endl;
				//}
			//}

			if(min->canMoveRight(3) == true) {															//check right movement potential. 
			//	cout << "DEBUG I CAN MOVE RIGHT!!";
				Puzzle* nextstate;
				nextstate = min->moveRight();
				nextstate->updateHCost(manhattanDistance);												//get hueristic
				nextstate->updateFCost();

                int checker = contains(minheap, nextstate);
                //cout << "DEBUG RIGHT CHECKER: " << checker << endl;
                checkQueue(nextstate, minheap, garbageheap);
				}

			if(min->canMoveDown(3) == true) {															//check down movement potential. 
			//	cout << "DEBUG I CAN MOVE DOWN!!";
				Puzzle* nextstate;
				nextstate = min->moveDown();
				nextstate->updateHCost(manhattanDistance);												//get hueristic
				nextstate->updateFCost();
				
				int checker = contains(minheap, nextstate);
                //cout << "DEBUG DOWN CHECKER: " << checker << endl;
                checkQueue(nextstate, minheap, garbageheap);
				}

			if(min->canMoveLeft(3) == true) {																//check up movement potential. 
			//	cout << "DEBUG I CAN MOVE LEFT!!";
				Puzzle* nextstate;
				nextstate = min->moveLeft();
				nextstate->updateHCost(manhattanDistance);												//get hueristic
				nextstate->updateFCost();
				
				int checker = contains(minheap, nextstate);
                //cout << "DEBUG RIGHT CHECKER: " << checker << endl;
                checkQueue(nextstate, minheap, garbageheap);
			}
            
				cout << "DEBUG HEAP" << endl;
				for(int i=0; i<minheap.size(); i++) {
					cout << minheap[i]->toString() << " : " << minheap[i]->getFCost() << " : " << minheap[i]->getPathLength() <<" : " << minheap[i]->getPathLength() << endl;
				} cout << endl;
		}
	}
    cout << "QUEUE is empty, no solution found" << endl;
}

//Uniform Cost Solver
void UniformCostSolver(string start, string goal) {
	vector<Puzzle*> ExpandedList;																		//holds expanded list
	priority_queue<Puzzle*, vector<Puzzle*>, compare> pq;                								//create priority queue to store nodes of search tree
    Puzzle *root = new Puzzle(start, goal);             			  									//create root node
    root->updateFCost();                                												//initialise its cost						                                                    //initialise the steps
    pq.push(root);                                                           							//push onto heap

	while(!pq.empty()) {																				//until the queue is empty
        Puzzle* min = pq.top();                                                							//find node with least cost
        pq.pop();                                                            							//remove node from heap
        NoStateExpansions ++; 																			//increase state expansions
		ExpandedList.push_back(min);																	//push visitied node to expanded list
		                                               													//increase number of state expansions
        if(min->goalMatch()==true) {																	//If this is hte goal state
			cout << "GOAL REACHED: " << endl;                               							//print diagnostics
            cout<< min->toString() << endl;
            cout << "Maximum Queue Length: " << MaxQueueLength << endl;       	
            cout << "Path length: " << min->getPathLength() << endl;
            cout << "Number of state expansions: " << NoStateExpansions << endl;
            cout << "Step sequence: " << min->getPath() << endl;
            return;
        } else if(min->goalMatch()==false) {															//else expand the node
		
			if(min->canMoveUp(3) == true) {																//check up movement potential. 
			//	cout << "DEBUG I CAN MOVE UP!!";
				Puzzle* nextstate;
				nextstate = min->moveUp();
				if(find(ExpandedList.begin(), ExpandedList.end(), nextstate) != ExpandedList.end()) {	//do not add if in expanded list
			//		cout << "DEBUG: I AM IN THE EXPANDED LIST" << endl;
					delete nextstate;																	//delete nextstate
				} else {																				//otherwise, add to queue
					nextstate->updateFCost();															//get hueristic
			//		cout << endl << "DEBUG UP: " <<nextstate->toString() << " fcost = " << nextstate->getFCost();
					pq.push(nextstate);																	//push onto queue
					MaxQueueLength++;																	//increase max queue size
			//		cout << endl << "TESTING QUEUE: " << pq.size() << endl;
				}
			}

			if(min->canMoveRight(3) == true) {															//check right movement potential. 
			//	cout << "DEBUG I CAN MOVE RIGHT!!";
				Puzzle* nextstate;
				nextstate = min->moveRight();
				if(find(ExpandedList.begin(), ExpandedList.end(), nextstate) != ExpandedList.end()) {	//do not add if in expanded list
			//		cout << "DEBUG: I AM IN THE EXPANDED LIST" << endl;
					delete nextstate;																	//delete nextstate
				} else {																				//otherwise, add to queue
					nextstate->updateFCost();															//get hueristic
			//		cout << endl << "DEBUG RIGHT: " <<nextstate->toString() << " fcost = " << nextstate->getFCost();
					pq.push(nextstate);																	//push onto queue
					MaxQueueLength++;																	//increase max queue size
			//		cout << endl << "TESTING QUEUE: " << pq.size() << endl;
				}
			}

			if(min->canMoveDown(3) == true) {															//check down movement potential. 
			//	cout << "DEBUG I CAN MOVE DOWN!!";
				Puzzle* nextstate;
				nextstate = min->moveDown();
				if(find(ExpandedList.begin(), ExpandedList.end(), nextstate) != ExpandedList.end()) {	//do not add if in expanded list
			//		cout << "DEBUG: I AM IN THE EXPANDED LIST" << endl;
					delete nextstate;																	//delete nextstate
				} else {																				//otherwise, add to queue
					nextstate->updateFCost();															//get hueristic
			//		cout << endl << "DEBUG DOWN: " <<nextstate->toString() << " fcost = " << nextstate->getFCost();
					pq.push(nextstate);																	//push onto queue
					MaxQueueLength++;																	//increase max queue size
			//		cout << endl << "TESTING QUEUE: " << pq.size() << endl;
				}
			}

			if(min->canMoveLeft(3) == true) {																//check up movement potential. 
			//	cout << "DEBUG I CAN MOVE LEFT!!";
				Puzzle* nextstate;
				nextstate = min->moveLeft();
				if(find(ExpandedList.begin(), ExpandedList.end(), nextstate) != ExpandedList.end()) {	//do not add if in expanded list
			//		cout << "DEBUG: I AM IN THE EXPANDED LIST" << endl;
					delete nextstate;																	//delete nextstate
				} else {																				//otherwise, add to queue
					nextstate->updateFCost();															//get cost														//update the state
			//		cout << endl << "DEBUG Left: " <<nextstate->toString() << " fcost = " << nextstate->getFCost();
					pq.push(nextstate);																	//push onto queue
					MaxQueueLength++;																	//increase max queue size
			//		cout << endl << "TESTING QUEUE: " << pq.size() << endl;
				}
			}
		}

			//Puzzle* Top = pq.top();
			//cout << endl << "TOP OF QUEUE: " << Top->toString() << " fcost = " << Top->getFCost();
			
			//cout << endl << "DEBUG EXPANDED LIST: " << endl;
			//for(auto & element : ExpandedList) { cout << element->toString() << endl;}
	}
}

int main() {
	const string start = "124803765";
	const string goal = "123456780";

	//MisplacedTilesSolver(start, goal);
	ManhattanDistanceSolver(start, goal);
	//UniformCostSolver(start, goal);
}

	




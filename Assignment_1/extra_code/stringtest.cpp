#include "puzzle.h"
#include <cmath>
#include <assert.h>
#include <string>
#include <queue>
#include <vector>
#include <algorithm> 

using namespace std;

struct compare{																			//Order the heap
	bool operator()(Puzzle* lhs,   Puzzle* rhs) {
		return (lhs->publicfcost + lhs->publiclength) > (rhs->publicfcost + rhs->publiclength);
	}
};

//Misplaced tiles solver

int MaxQueueLength = 0;
int NoStateExpansions = 0;

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
				if(find(ExpandedList.begin(), ExpandedList.end(), nextstate) != ExpandedList.end()) {	//do not add if in expanded list
			//		cout << "DEBUG: I AM IN THE EXPANDED LIST" << endl;
					delete nextstate;																	//delete nextstate
				} else {																				//otherwise, add to queue
					nextstate->updateHCost(misplacedTiles);												//get hueristic
					nextstate->updateFCost();															//update the state
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
    Puzzle *root = new Puzzle(start, goal);             			  									//create root node
    root->updateHCost(manhattanDistance);                                									//initialise its cost						                                                    //initialise the steps
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
					nextstate->updateHCost(manhattanDistance);												//get hueristic
					nextstate->updateFCost();															//update the state
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
					nextstate->updateHCost(manhattanDistance);												//get hueristic
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
					nextstate->updateHCost(manhattanDistance);												//get hueristic
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
					nextstate->updateHCost(manhattanDistance);												//get hueristic
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
	const string start = "120483765";
	const string goal = "123456780";

	//MisplacedTilesSolver(start, goal);
	ManhattanDistanceSolver(start, goal);
	//UniformCostSolver(start, goal);
}

	




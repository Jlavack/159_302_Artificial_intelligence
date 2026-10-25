/*159.302 Artificial Intelligence
John Lavack 20001249
*/

#include <cmath>
#include <assert.h>
#include <string>
#include <queue>
#include <vector>
#include <algorithm> 
#include "algorithm.h"
#include "puzzle.h"

using namespace std;
//-------------------------------Global_Variables--------------------------//

vector<Puzzle*> ExpandedList;	

//-------------------------------Helper_functions--------------------------//
struct compare{																							//Orders the heap via the minimum condition
	bool operator()(Puzzle* lhs,   Puzzle* rhs) {
		return (lhs->getFCost() > rhs->getFCost());
	}
};

bool IsSameState (Puzzle* s1, Puzzle* s2) {																//Checks if two states have same board state
	if(s1->toString() != s2->toString()) { return false;}
	return true;
}

bool IsSmallerCost (Puzzle* s1, Puzzle* s2) {															//Check which board has smaller fCost
	if(s1->getFCost() < s2->getFCost()) { return false;}
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

void GoalDiagnostics(Puzzle* state, int maxQLength, int numOfStateExpansions, int pathLength, int numOfDeletionsFromMiddleOfHeap) {																	//prints diagnostics of puzzle
	cout << "GOAL REACHED: " << endl;                               							
	cout<< state->toString() << endl;
	cout << "Maximum Queue Length: " << maxQLength << endl;       	
	cout << "Path length: " << state->getPathLength() << endl;
	cout << "Number of state expansions: " << numOfStateExpansions << endl;
	cout << "NUmber of deletions from middle of heap: " << numOfDeletionsFromMiddleOfHeap << endl;
	cout << "Step sequence: " << state->getPath() << endl;
	// actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	// cout << "RUNTIME: " << actualRunningTime << endl;
	return; 
	}	




//-------------------------------DEBUGGING_Function-----------------------//
void DEBUGHEAP(vector<Puzzle*> minheap) {
	cout << "DEBUG HEAP" << endl;
	for(int i=0; i<minheap.size(); i++) {
		cout << minheap[i]->toString() << " : " << minheap[i]->getFCost() << " : " << minheap[i]->getPathLength() << endl;
	} cout << endl;
}


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  UC with Strict Expanded List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string uc_explist(string const initialState, string const goalState, int& pathLength, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions){
											 
   string path;
   clock_t startTime;
   
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;


    // cout << "------------------------------" << endl;
    // cout << "<<uc_explist>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;	
	startTime = clock();

    	vector<Puzzle*> minheap;																			//create minheap
	Puzzle *root = new Puzzle(initialState, goalState);             			  									//create root node
	root->updateFCost();                                												//initialise its cost						                                                    //initialise the steps
	minheap.push_back(root);
	make_heap(minheap.begin(), minheap.end(), compare());												//make vector a heap
	                                                      						
	while(!minheap.empty()) {																			//until the queue is empty
        pop_heap(minheap.begin(), minheap.end());														//take the top element and examine it (line 592 is examination)
		Puzzle* min = minheap.back();
		minheap.pop_back();
		
        if(min->goalMatch()==true) {																	//If this is the goal state, print diagnostics and end process
			// GoalDiagnostics(min, maxQLength, numOfStateExpansions, min->getPathLength(), numOfDeletionsFromMiddleOfHeap);	
            path = min->getPath();
            // return path;	
            break;															
			}		

		if (IsInExpandedList(min)) {																	//check if state in hand is in expanded list. If yes, don't add it to heap
			continue;
		} else { 																						//if no, add to expanded list and generate successors
			ExpandedList.push_back(min);
			numOfStateExpansions ++;
																										//now generate each successor node in the order U, R, D, L
			if(min->canMoveUp(3) == true) {																//Check if can move up							
			 	Puzzle* nextstate = min->moveUp();														//if yes, make up node. Move previous state blank tile up one
				nextstate->updateFCost(); 																//recalculate the g(cost) = h(cost) + Pathlength
				if(!IsInExpandedList(nextstate) && !IsInQueue(nextstate, minheap)) {					//If next state is not in the expanded list nor in the queue
					minheap.push_back(nextstate);														//push the better state onto the queue
					maxQLength++;																    	//iterate queue length
					make_heap(minheap.begin(), minheap.end(), compare());								//heapify
				} else if(!IsInExpandedList(nextstate) && IsInQueue(nextstate, minheap)) { numOfDeletionsFromMiddleOfHeap ++;}
			}

			if(min->canMoveRight(3) == true) {															//repeat for moving right
				Puzzle* nextstate = min->moveRight();
				nextstate->updateFCost(); 
				if(!IsInExpandedList(nextstate) && !IsInQueue(nextstate, minheap)) {
					minheap.push_back(nextstate);
					maxQLength++;
					make_heap(minheap.begin(), minheap.end(), compare());
				} else if(!IsInExpandedList(nextstate) && IsInQueue(nextstate, minheap)) { numOfDeletionsFromMiddleOfHeap ++;}
			}

			if(min->canMoveDown(3) == true) {															//repeat for moving down
				Puzzle* nextstate = min->moveDown();
				nextstate->updateFCost(); 
				if(!IsInExpandedList(nextstate) && !IsInQueue(nextstate, minheap)) {
					minheap.push_back(nextstate);
					maxQLength++;
					make_heap(minheap.begin(), minheap.end(), compare());
				} else if(!IsInExpandedList(nextstate) && IsInQueue(nextstate, minheap)) { numOfDeletionsFromMiddleOfHeap ++;}
			}

			if(min->canMoveLeft(3) == true) {															//repret for moving left
				Puzzle* nextstate = min->moveLeft();
				nextstate->updateFCost(); 
				if(!IsInExpandedList(nextstate) && !IsInQueue(nextstate, minheap)) {
					minheap.push_back(nextstate);
					maxQLength++;
					make_heap(minheap.begin(), minheap.end(), compare());
				} else if(!IsInExpandedList(nextstate) && IsInQueue(nextstate, minheap)) { numOfDeletionsFromMiddleOfHeap ++;}
			}
		}
	}																															
     //cout << "QUEUE is empty, no solution found" << endl;	
	
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	pathLength = path.size();
	return path;		
		
}




///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  A* with the Strict Expanded List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string aStar_ExpandedList(string const initialState, string const goalState, int& pathLength, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){
											 
   string path;
   clock_t startTime;
   
   //initialise performance variables
   maxQLength=0;
   numOfStateExpansions=0;
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;

    // cout << "------------------------------" << endl;
    // cout << "<<aStar_ExpandedList>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;	
	startTime = clock();

	vector<Puzzle*> minheap;																			//create minheap
	Puzzle *root = new Puzzle(initialState, goalState);             			  						//create root node
	root->updateHCost(heuristic);                                										//initialise its cost						                                                    //initialise the steps
	minheap.push_back(root);
	make_heap(minheap.begin(), minheap.end(), compare());												//make vector a heap
	                                                      						
	while(!minheap.empty()) {																			//until the queue is empty
        pop_heap(minheap.begin(), minheap.end());														//take the top element and examine it (line 592 is examination)
		Puzzle* min = minheap.back();
		minheap.pop_back();
		
        if(min->goalMatch()==true) {																	//If this is the goal state, print diagnostics and end process
			// GoalDiagnostics(min, maxQLength, numOfStateExpansions, min->getPathLength(), numOfDeletionsFromMiddleOfHeap);	
            path = min->getPath();
            // return path;
            break;																
			}	

		if (IsInExpandedList(min)) {																	//check if state in hand is in expanded list. If yes, don't add it to heap
			continue;
		} else { 																						//if no, add to expanded list and generate successors
			ExpandedList.push_back(min);
			numOfStateExpansions ++;
																										//now generate each successor node in the order U, R, D, L
			if(min->canMoveUp(3) == true) {																//Check if can move up							
			 	Puzzle* nextstate = min->moveUp();														//if yes, make up node. Move previous state blank tile up one
				nextstate->updateHCost(heuristic);														//recalculate the h(cost)
				nextstate->updateFCost(); 																//recalculate the g(cost) = h(cost) + Pathlength
				if(!IsInExpandedList(nextstate) && !IsInQueue(nextstate, minheap)) {					//If next state is not in the expanded list nor in the queue
					minheap.push_back(nextstate);														//push the better state onto the queue
					maxQLength++;																	    //iterate queue length
					make_heap(minheap.begin(), minheap.end(), compare());								//heapify
				} else if(!IsInExpandedList(nextstate) && IsInQueue(nextstate, minheap)) { numOfDeletionsFromMiddleOfHeap ++;}
			}

			if(min->canMoveRight(3) == true) {															//repeat for moving right
				Puzzle* nextstate = min->moveRight();
				nextstate->updateHCost(heuristic);
				nextstate->updateFCost(); 
				if(!IsInExpandedList(nextstate) && !IsInQueue(nextstate, minheap)) {
					minheap.push_back(nextstate);
					maxQLength++;
					make_heap(minheap.begin(), minheap.end(), compare());
				} else if(!IsInExpandedList(nextstate) && IsInQueue(nextstate, minheap)) { numOfDeletionsFromMiddleOfHeap ++;}
			}

			if(min->canMoveDown(3) == true) {															//repeat for moving down
				Puzzle* nextstate = min->moveDown();
				nextstate->updateHCost(heuristic);
				nextstate->updateFCost(); 
				if(!IsInExpandedList(nextstate) && !IsInQueue(nextstate, minheap)) {
					minheap.push_back(nextstate);
					maxQLength++;	
					make_heap(minheap.begin(), minheap.end(), compare());
				} else if(!IsInExpandedList(nextstate) && IsInQueue(nextstate, minheap)) { numOfDeletionsFromMiddleOfHeap ++;}
			}

			if(min->canMoveLeft(3) == true) {															//repret for moving left
				Puzzle* nextstate = min->moveLeft();
				nextstate->updateHCost(heuristic);
				nextstate->updateFCost(); 
				if(!IsInExpandedList(nextstate) && !IsInQueue(nextstate, minheap)) {
					minheap.push_back(nextstate);
					maxQLength++;	
					make_heap(minheap.begin(), minheap.end(), compare());
				} else if(!IsInExpandedList(nextstate) && IsInQueue(nextstate, minheap)) { numOfDeletionsFromMiddleOfHeap ++;}
			}
		}
	}																															
    //  cout << "QUEUE is empty, no solution found" << endl;	
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
    pathLength = path.size();
	return path;		
		
}

//***********************************************************************************************************
// int main() {
//   	const string start = "120483765";
// 	// const string start = "208135467";
// 	// const string start = "704851632";
// 	// const string start = "536407182";
// 	// const string start = "638541720";

// 	const string goal = "123456780";

// 	cout << "//-----------------------------------START-----------------------------------//" << endl;
// 	cout << "Start state: " << start << endl;
//     //uc_explist(start, goal, 0, 0, 0, 0.0, 0, 0, 0);
// 	// aStar_ExpandedList(start, goal, 0, 0, 0, 0.0, 0, 0, 0, misplacedTiles);
// 	aStar_ExpandedList(start, goal, 0, 0, 0, 0.0, 0, 0, 0, manhattanDistance);
// }
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T_S 1000000000

using namespace std;

//-------------------------------HASH_Functions----------------------------//
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
         return k % T_S;
      }
      
      void Insert(int k, int v) {
         int h = HashFunc(k);
         while (t[h] != NULL && t[h]->k != k) {
            h = HashFunc(h+1);
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
         if (t[h] == 0)
            return false; //in the hastable
         else
            return true;
      }

      bool IsNewValueLessThanExisting(int k, int x) {
         int h = HashFunc(k);
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
            return;
         } else {
            delete t[h];
         }
      }

    //   ~HashMapTable() {
    //      for (int i = 0; i < T_S; i++) {
    //            delete t[i];
    //            delete[] t;
    //      }
    //   }
};

//-------------------------------Helper_Functions--------------------------//
struct compare{																							//Orders the heap via the minimum condition
	bool operator()(Puzzle* lhs,   Puzzle* rhs) {
		return (lhs->getFCost() > rhs->getFCost());
	}
};

struct compare_UC{																						//Orders the heap via the minimum condition for UC implementation
	bool operator()(Puzzle* lhs,   Puzzle* rhs) {
		return (lhs->getDepth() > rhs->getDepth());
	}
};

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
	HashMapTable *ExpandedList = new HashMapTable;                                                      //Hash for expanded list
	HashMapTable *OpenList = new HashMapTable;                                                          //Hash for open list
    Puzzle *root = new Puzzle(initialState, goalState);             			  						//create root node
	root->updateFCost();                                												//initialise its cost						                                                    //initialise the steps
	minheap.push_back(root);
	make_heap(minheap.begin(), minheap.end(), compare_UC());											//make vector a heap
	                                                      						
	while(!minheap.empty()) {																			//until the queue is empty
        pop_heap(minheap.begin(), minheap.end());														//take the top element and examine it (line 592 is examination)
		Puzzle* min = minheap.back();
		minheap.pop_back();
		
        if(min->goalMatch()==true) {																	//If this is the goal state, print diagnostics and end process
			// GoalDiagnostics(min, maxQLength, numOfStateExpansions, min->getPathLength(), numOfDeletionsFromMiddleOfHeap);	//used for debugging easily in this code file
            path = min->getPath();
            break;															
			}		

        if (ExpandedList->SearchKey(stoi(min->strBoard)) == true) {										//check if state in hand is in expanded list. If yes, don't add it to heap
			continue;
		} else { 																						//if no, add to expanded list and generate successors
			ExpandedList->Insert(stoi(min->strBoard), min->getDepth());
			numOfStateExpansions ++;
																										//now generate each successor node in the order U, R, D, L
			vector<Puzzle*> Successors;
			GenerateSuccessors_UC(min, &Successors); 

			for (int i =0; i<Successors.size(); i++ ){
				if(ExpandedList->SearchKey(stoi(Successors[i]->strBoard)) == true) {                     //already expanded, skip
					delete Successors[i];
                    continue;
				} else if (OpenList->SearchKey(stoi(Successors[i]->strBoard))==true) {                   //in open list. Check depth value
					if(OpenList->IsNewValueLessThanExisting(stoi(Successors[i]->strBoard), Successors[i]->getFCost())==true) {  //yes, new value is less
						OpenList->Remove(stoi(Successors[i]->strBoard));                                 //remove old value
						OpenList->Insert(stoi(Successors[i]->strBoard), Successors[i]->getFCost());      //add new, shallower value
						numOfDeletionsFromMiddleOfHeap++;
					}
					delete Successors[i];
                    continue;
				} else {
					minheap.push_back(Successors[i]);
                    OpenList->Insert(stoi(Successors[i]->strBoard), Successors[i]->getFCost());          //add key value to has table
					make_heap(minheap.begin(), minheap.end(), compare_UC());
					maxQLength++;
				} 
			}
            Successors.clear();
		}
        delete min;
	}																																																											
     //cout << "QUEUE is empty, no solution found" << endl;	
	free(OpenList);
    free(ExpandedList);	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	pathLength = path.size();
    minheap.clear();

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
    HashMapTable *ExpandedList = new HashMapTable;                                                       //Hash for expanded list
	HashMapTable *OpenList = new HashMapTable;                                                           //hash for open list
    Puzzle *root = new Puzzle(initialState, goalState);             			  					    //create root node
	root->updateHCost(heuristic);                                										//initialise its cost						                                                    //initialise the steps
	minheap.push_back(root);
	make_heap(minheap.begin(), minheap.end(), compare());												//make vector a heap
	                                                      						
	while(!minheap.empty()) {																			//until the queue is empty
        pop_heap(minheap.begin(), minheap.end());														//take the top element and examine it (line 592 is examination)
		Puzzle* min = minheap.back();
		minheap.pop_back();
		
        if(min->goalMatch()==true) {																	//If this is the goal state, print diagnostics and end process
            path = min->getPath();
			break;																
			}	

		if (ExpandedList->SearchKey(stoi(min->strBoard)) == true) {										//check if state in hand is in expanded list. If yes, don't add it to heap
			continue;
		} else { 																						//if no, add to expanded list and generate successors
			ExpandedList->Insert(stoi(min->strBoard), min->getFCost());
            numOfStateExpansions ++;

			vector<Puzzle*> Successors;
			GenerateSuccessors_aStar(min, &Successors, heuristic); 

			for (int i =0; i<Successors.size(); i++ ){
				if(ExpandedList->SearchKey(stoi(Successors[i]->strBoard)==true)) {                       //not in expanded list
					delete Successors[i];
                    continue;
				} else if (OpenList->SearchKey(stoi(Successors[i]->strBoard))==true) {
					if(OpenList->IsNewValueLessThanExisting(stoi(Successors[i]->strBoard), Successors[i]->getDepth())==true) {  //yes, new value is less
						OpenList->Remove(stoi(Successors[i]->strBoard));                                 //remove old value
						OpenList->Insert(stoi(Successors[i]->strBoard), Successors[i]->getFCost());      //add new value
						numOfDeletionsFromMiddleOfHeap++;
					}
					delete Successors[i];
                    continue;
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
     //cout << "QUEUE is empty, no solution found" << endl;												//if no solution is found	
	free(OpenList);
    free(ExpandedList);
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
    pathLength = path.size();
    minheap.clear();

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
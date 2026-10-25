vector<Puzzle*>::iterator iter = ExpandedList.begin();
					for(iter; iter < ExpandedList.end(); ++iter) {
						cout << &iter->toString();
						if(*iter == nextstate) {
							cout << "I AM IN THE EXPANDED LIST" << endl;
						} 
					}





bool contains(vector<Puzzle*> &ExpandedList, Puzzle* nextstate) {	
	vector<Puzzle*>::iterator iter;
	for(iter = ExpandedList.begin(); iter < ExpandedList.end(); ++iter) {
		Puzzle* expstate = *iter;
		//cout << expstate->toString() << endl;
		if(expstate->toString() == nextstate->toString()) {
			//cout << "DEBUG COMPARE: " << expstate->toString() << " " << expstate->publicfcost << " ;" << nextstate->toString() <<" "<< nextstate->publicfcost << endl;
			if(expstate->publicfcost > nextstate->publicfcost) {
				expstate->publicfcost = nextstate->publicfcost;
			//	cout << "DEBUG SWAPPED: " << expstate->toString() << " " << expstate->publicfcost << " ;" << nextstate->toString() <<" "<< nextstate->publicfcost << endl;
			delete nextstate;
			delete expstate;
			return true;
			break;
			}	
		} 
	}
	return false;
}


bool contains(vector<Puzzle*> &ExpandedList, Puzzle* nextstate) {
	vector<Puzzle*>::iterator iter;
	for(iter = ExpandedList.begin(); iter < ExpandedList.end(); ++iter) {
		Puzzle* expstate = *iter;
		if(expstate->toString() == nextstate->toString()) {
			return true;
			break;
			}
		}
		return false;
}
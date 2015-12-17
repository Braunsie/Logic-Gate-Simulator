// Author:  Chris Brauns and Lorenzo Pizarro
// Date:    11/17/15

#include "Wire.h"

#include<iostream>
using namespace std;

Wire::Wire(){
	State = UNKNOWN;
}

Wire::~Wire(){

	for (int i = 0; i < Gates.size(); i++){
		Gates.pop_back();
	}
	for (int i = 0; i < History.size(); i++){
		History.pop_back();
	}
}

int Wire::getState() {
	return State;
}

void Wire::setState(int s) {
	State = s;
}

void Wire::setHistory(int time, int state){
	int size;
	int change;
	int lastState;
	
	size = History.size();
	change = time - size;
	
	if (History.size() > 0 && change != -1){
		lastState = History[size-1];

		//fills in the history up to the point of the current event
		for (int i = 0; i < change; i++){
			History.push_back(lastState);
		}
		History.push_back(state);
	}

	//For the case that the wire has already been told a state for this moment in time
	//This overwrites the state. For our program, this would happen if two events
	//affect the same gate at the same time
	 if (change == -1){
		History[time] = state;
	}

	 //Accounts for a gate that never receives an initial state, but then
	 //gets a state later on in the simulation
	 if (change != 0 && History.size() == 0) {
		for (int i = 0; i < change; i++){
			History.push_back(UNKNOWN);
		}
		History.push_back(state);
	}

	 if (change == 0){
		History.push_back(state);
	}
}

vector<int> Wire::getHistory(){
	vector<int> temp = History;
	return temp;
}

int Wire::getHisSize(){
	int t = History.size();
	return t;
}

vector<Gate*> Wire::getGates(){
	vector<Gate*> temp = Gates;
	return temp;
}

void Wire::pushGates(Gate* g){
	Gates.push_back(g);
	return;
}

void Wire::fillHistory(int max){
	int change = (max - History.size());
	for (int i = 0; i < change; i++){
		History.push_back(State);
	}
}

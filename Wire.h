// Author:  Chris Brauns and Lorenzo Pizarro
// Date:    11/17/15
// Purpose: To pass the class

// The following pattern is used to prevent multiple inclusion 
// of class definitions
#ifndef WIRE_H
#define WIRE_H

#include <iostream>
#include<vector>
#include<map>
#include<string>
#include "Gate.h"
#include "Wire.h"

using namespace std;

class Gate;

class Wire {
public:
	// constructors
	Wire();

	// destructor
	~Wire();

	//functions
	int getState();
	void setState(int s);
	void setHistory(int time, int state);
	vector<int> getHistory();

	int getHisSize();
	vector<Gate*> getGates();

	void pushGates(Gate* g);
	void fillHistory(int max);

private:
	int State;
	vector<Gate*> Gates;
	vector<int> History;
};

#endif //WIRE_H

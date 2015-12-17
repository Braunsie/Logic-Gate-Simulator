// Author:  Chris Brauns and Lorenzo Pizarro
// Date:    11/17/15

#ifndef GATE_H
#define GATE_H

#include "Wire.h"
#include "Event.h"

#include <iostream>
#include<vector>
#include<map>
#include<string>

using namespace std;
const int HI = 1;
const int LOW = 0;
const int UNKNOWN = -1;

class Wire;

class Gate {
public:

	// constructors
	Gate();
	//We are using the parsing which will include a Gate* attribute
	//to define the values. It will set type, InputA, InputB, and delays
	//from the input file, so the parsing function will initialize these values.
	//The parsing function will also create the wires and make the gate inputs 
	//point to these values.

	// destructor
	~Gate();

	//functions

	Event logic();
	Event doLogic(int time);
	void setType(string);
	void setDelay(int);
	void setAIO(Wire* i, int o); //Only for the NOT gate
	void setBIO(Wire* ain, Wire* bin, int o); //For all gates except for NOT

private:
	string Type;
	Wire* inputA;
	Wire* inputB;
	int output;
	int delay;


};

#endif //GATE_H

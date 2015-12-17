// Author:  Chris Brauns and Lorenzo Pizarro
// Date:    11/17/15

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "Wire.h"
#include "Gate.h"
#include "Event.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

#include <map>

using namespace std;

class Circuit {
public:

	// constructors
	Circuit();

	// destructor
	~Circuit();

	//functions
	void parse();
	void simulation();
	void setName(string n);
	void setWireName(char l, int n);
	void setWireLetter(char c, int n);
	void setWires(int n);
	bool checkEmpty(Wire* w);
	void pushPrior(Event e);
	void pushPrior(int time, int wire, int state);
	void pushGatePrior(int time, int delay, int wire, int state);
	Event popPrior();
	bool shouldContinue();
	void setCircuitOrder();
	void fillPrintHistory();
	void setStream(string c);
	void closeStream();

private:
	string name;
	map<char, int> wireName;
	char wireLetter[100];
	Wire* wires[100];
	Gate* gates[100];
	priority_queue<Event> priority;
	int circuitOrder;
};

#endif //CIRCUIT_H

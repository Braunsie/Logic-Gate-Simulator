// Author:  Chris Brauns and Lorenzo Pizarro
// Date:    11/17/15

#include "Circuit.h"

#include<iostream>
#include<string>
using namespace std;

ifstream in;

Circuit::Circuit(){
	for (int i = 0; i < 100; i++){
		gates[i] = NULL;
		wires[i] = NULL;
		wireLetter[i] = NULL;
		
	}
	circuitOrder = 0;
}

Circuit::~Circuit(){

}

void Circuit::parse(){

	string temp;
	string delayTime;
	string x;

	int delayNum;
	int gatePosition = 0;
	
	int inOne;
	int inTwo;
	int outOne;
	Wire* ptOne;
	Wire* ptTwo;

	char letter;
	int number;
	int time;
	int state;

	bool leave = false;
	
	while (!in.eof()){

		if (in.eof()) return;
		in >> temp;
		if (temp == "CIRCUIT"){

			string s;
			in >> s;
			setName(s);
			in >> temp;
			while (temp == "INPUT" || temp == "OUTPUT"){

				in >> letter;
				in >> number;
				setWireName(letter, number);
				setWireLetter(letter, number);
				setWires(number);

				if (temp == "INPUT"){
				}
				if (temp == "OUTPUT"){
				}

				in >> temp;
			}
		}
			if (temp == "NOT"){
				in >> delayTime;
				in >> inOne;
				in >> outOne;

				if (checkEmpty(wires[inOne])){
					wires[inOne] = new Wire;
				}
				ptOne = wires[inOne];

				if (checkEmpty(wires[outOne])){
					wires[outOne] = new Wire;
				}

				delayTime = delayTime.substr(0, 1);
				delayNum = stoi(delayTime);

				gates[gatePosition] = new Gate;
				gates[gatePosition]->setDelay(delayNum);
				gates[gatePosition]->setType(temp);
				//Uses the specific assinger for the NOT gate
				gates[gatePosition]->setAIO(ptOne, outOne);

				wires[inOne]->pushGates(gates[gatePosition]);

				gatePosition++;

			}
			if (temp == "AND" || temp == "OR" || temp == "NAND" || temp == "NOR" || temp == "XOR" || temp == "XNOR"){
				in >> delayTime;
				in >> inOne;
				in >> inTwo;
				in >> outOne;


				//This section creates a new wire if it hasn't already
				//been made.
				if (checkEmpty(wires[inOne])){
					wires[inOne] = new Wire;
				}
				ptOne = wires[inOne];

				if (checkEmpty(wires[inTwo])){
					wires[inTwo] = new Wire;
				}
				ptTwo = wires[inTwo];

				if (checkEmpty(wires[outOne])){
					wires[outOne] = new Wire;
				}

				delayTime = delayTime.substr(0, 1);
				delayNum = stoi(delayTime);

				gates[gatePosition] = new Gate;
				gates[gatePosition]->setDelay(delayNum);
				gates[gatePosition]->setType(temp);
				gates[gatePosition]->setBIO(ptOne, ptTwo, outOne);

				wires[inOne]->pushGates(gates[gatePosition]);
				wires[inTwo]->pushGates(gates[gatePosition]);

				gatePosition++;
			}
		if (temp == "VECTOR"){
			string s; 
			in >> s;
			in >> temp;
			
			while (temp == "INPUT" && !in.eof()){
				in >> letter;
				in >> time;
				in >> state;
				Event t = Event(time, wireName[letter], state);
				t.setOrder(circuitOrder);
				setCircuitOrder();
				priority.push(t);
				if (!in.eof()) in >> temp;
				bool test = in.eof();
				if (in.eof()) return;
			}

		}
	}
}


//Takes events from the priority queue and creates any needed future events
void Circuit::simulation(){
	
	Event Action = popPrior();
	Event futureAction; 

	int wire = Action.getWire();
	int state = Action.getState();
	int time = Action.getTime();

	wires[wire]->setState(state);
	wires[wire]->setHistory(time, state);

	vector<Gate*> outGate = wires[wire]->getGates();
	for (int i = 0; i < outGate.size(); i++){
		futureAction = outGate[i]->doLogic(time);
		pushPrior(futureAction);
	}
}

void Circuit::setName(string s){
	name = s;
}

void Circuit::setWireName(char l, int n){
	wireName[l] = n;
}

void Circuit::setWireLetter(char c, int n){
	wireLetter[n] = c;
	return;
}

void Circuit::setWires(int n){
	wires[n] = new Wire();
}

bool Circuit::checkEmpty(Wire* w){
	if (w == NULL){
		return true;
	}
	else return false;
}

void Circuit::pushPrior(Event e){
	Event temp = e;
	setCircuitOrder();
	temp.setOrder(circuitOrder);
	priority.push(temp);
}

void Circuit::pushPrior(int time, int wire, int state){
	Event temp = Event(time, wire, state);
	setCircuitOrder();
	temp.setOrder(circuitOrder);
	priority.push(temp);
}

//This function returns the most recent event as well as then removing
//It from the queue
Event Circuit::popPrior(){
	Event n = priority.top();
	priority.pop();
	return n;
}

void Circuit::pushGatePrior(int time, int delay, int wire, int state){
	Event temp = Event(time + delay, wire, state);
	priority.push(temp);

}


//Tells the simulation whether or not to keep going based on whether there are
//events in the queue and if the History size in any of the wires is larger than 60
bool Circuit::shouldContinue(){
	if (priority.size() == 0) return false;

	for (int i = 0; i < 100; i++){
		if (wires[i] != NULL){
			if (wires[i]->getHisSize() >= 60) return false;
		}
	}

	return true;
}


//assigns a unique number to each event for better sorting in the queue
void Circuit::setCircuitOrder(){
	circuitOrder++;
}

void Circuit::fillPrintHistory(){
	int max = 0;

	//Some wires do not have the full history that others do because they are
	//only set at the very beginning. This fills in the history of these wires
	//for a more aesthetically pleasing print
	for (int i = 0; i < 100; i++){
		if (wires[i] != NULL){
			int t = wires[i]->getHisSize();
			if (t > max) max = t;
		}
	}

	for (int i = 0; i < 100; i++){
		if (wires[i] != NULL){
			if (wires[i]->getHisSize() < max){
				wires[i]->fillHistory(max);
			}
		}
	}

	cout << endl << "History of Circuit: " << name << endl << endl;

	for (int i = 0; i < 100; i++){
		if (wires[i] != NULL){
			vector<int> timeline = wires[i]->getHistory();
			cout << "Wire: ";
			cout << wireLetter[i] << " ";
			cout << i << " ";
			char symbol;
			for (int j = 0; j < max; j++){
				if (timeline[j] == 1) symbol = '-';
				if (timeline[j] == 0) symbol = '_';
				if (timeline[j] == -1) symbol = 'X';
				cout << symbol;
			}
			cout << endl;
		}
	}
	cout << "Time:     0    5    10   15   20   25   30   35   40   45   50   55   60";
}

void Circuit::setStream(string c){
	in.open(c);
	while (in.fail()){
		cout << endl << endl << "That File Name is Invalid!";
		cout << endl << "Please Enter a Correct File Name: ";
		cin >> c;
		in.open(c);
	}
}

void Circuit::closeStream(){
	in.close();
}

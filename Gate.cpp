// Author:  Chris Brauns and Lorenzo Pizarro
// Date:    11/17/15

#include "Gate.h"

#include<iostream>
using namespace std;

Gate::Gate(){
	inputA = new Wire();
}

Gate::~Gate(){
	delete inputA;
	delete inputB;
}

//This provides the event which simulation functions ask for, unique for each gate
Event Gate::logic(){
	if (Type == "NOT"){
		if (inputA->getState() == UNKNOWN){
			Event value = Event(delay, output, UNKNOWN);
			return value;
		}
		if (inputA->getState() == HI){
			Event value = Event(delay, output, LOW);
			return value;
		}
		if (inputA->getState() == LOW){
			Event value = Event(delay, output, HI);
			return value;
		}
	}
	if (Type == "AND") {
		if (inputA->getState() == HI && inputB->getState() == HI){
			Event value = Event(delay, output, HI);
			return value;
		}
		else if (inputA->getState() == LOW || inputB->getState() == LOW){
			Event value = Event(delay, output, LOW);
			return value;
		}
		else  {
			Event value = Event(delay, output, UNKNOWN);
			return value;
		}
	}
	if (Type == "OR") {
		if (inputA->getState() == HI || inputB->getState() == HI){
			Event value = Event(delay, output, HI);
			return value;
		}
		else if (inputA->getState() == UNKNOWN || inputB->getState() == UNKNOWN){
			Event value = Event(delay, output, UNKNOWN);
			return value;
		}
		else {
			Event value = Event(delay, output, LOW);
			return value;
		}
	}
	if (Type == "XOR"){

		if (inputA->getState() == UNKNOWN || inputB->getState() == UNKNOWN){
			Event value = Event(delay, output, UNKNOWN);
			return value;
		}
		else if (inputA->getState() != inputB->getState()){
			Event value = Event(delay, output, HI);
			return value;
		}
		else
		{
			Event value = Event(delay, output, LOW);
			return value;
		}
	}
	if (Type == "NAND"){
		if (inputA->getState() == HI && inputB->getState() == HI){
			Event value = Event(delay, output, LOW);
			return value;
		}
		else if (inputA->getState() == LOW || inputB->getState() == LOW){
			Event value = Event(delay, output, HI);
			return value;
		}
		else{
		
			Event value = Event(delay, output, UNKNOWN);
			return value;
		}
	}
	if (Type == "NOR"){
		if (inputA->getState() == LOW && inputB->getState() == LOW){
			Event value = Event(delay, output, HI);
			return value;
		}
		else if (inputA->getState() == HI || inputB->getState() == HI){
			Event value = Event(delay, output, LOW);
			return value;
		}
		else{
			
			Event value = Event(delay, output, UNKNOWN);
			return value;
		}
	}
	if (Type == "XNOR"){
		if (inputA->getState() == inputB->getState()){
			Event value = Event(delay, output, HI);
			return value;
		}
		else if (inputA->getState() == UNKNOWN || inputB->getState() == UNKNOWN){
			
			Event value = Event(delay, output, UNKNOWN);
			return value;
		}
		else
		{
			Event value = Event(delay, output, LOW);
			return value;
		}
	}
}

void Gate::setType(string t){
	Type = t;
}

void Gate::setDelay(int d){
	delay = d;
}

//We needed a unique function for the NOT gate since it only takes one input
void Gate::setAIO(Wire* ain, int o){
	inputA = ain;
	output = o;
}

void Gate::setBIO(Wire* ain, Wire* bin, int o){
	inputA = ain;
	inputB = bin;
	output = o;
}

Event Gate::doLogic(int time){
	Event value = logic();
	value.setTimeDelay(time);
	return value;
}

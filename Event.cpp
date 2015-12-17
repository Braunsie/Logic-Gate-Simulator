
#include "Event.h";

using namespace std;

Event::Event(){
	order = 0;
}

Event::Event(int t, int w, int s){
	time = t;
	wire = w;
	state = s;
	order = 0;
}

Event::~Event(){

}

int Event:: getTime(){
	int t = time;
	return t;
}

int Event::getWire(){
	int w = wire;
	return w;
}

int Event::getState(){
	int s = state;
	return s;
}

//Gives the unique order number from the Circuit class so that all of the 
//events have correct organization, even if the time is the same.
void Event::setOrder(int o){
	order = o;
}

void Event::setTimeDelay(int delay){
	time += delay;
	return;
}

bool operator<(const Event &a,const Event &b) {
	//Instead of trying to mess with changing the priority queue from greatest
	//to least, we simply inverted the comparison operator
	if (a.time > b.time) return true;
	if (a.time == b.time && a.order > b.order) return true;
	else return false;
}

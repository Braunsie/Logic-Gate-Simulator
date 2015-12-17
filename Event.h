#ifndef EVENT_H
#define EVENT_H

class Event{
public:

	Event();
	Event(int t, int w, int s);

	~Event();

	int getTime();
	int getWire();
	int getState();
	void setOrder(int o);

	void setTimeDelay(int t);

	friend bool operator<(const Event &a,const Event &b);
	//bool operator>(const Event &a);
	//bool operator==(const Event &a);
	//inline bool operator<(const Event&a);

	//bool operator() (const Event& a, const Event& b);

private:
	int time;
	int wire;
	int state;
	int order;
};


#endif // !EVENT_H

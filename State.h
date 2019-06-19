#pragma once
#include <map>
class State {
protected:	
	int ID;
	bool isFinal;
public:
	State();
	const int getID() const;
	void setID(const int newID);
	void setFinalTrue();
	void print();
	const bool getFinal() const;
	std::multimap<char, int> Transition;
	//void addTransition(char with, int to);
};
#pragma once
#include <map>
class State {
protected:	
	int ID; //Creating ID of the state
	bool isFinal; // Checking if it is final
public:
	State(); //Constructor for State
	const int getID() const; // Getting ID
	void setID(const int newID); // Setting ID
	void setFinalTrue(); // Setting State to Final
	void print(); // Printing State
	const bool getFinal() const; // Checking if it is final
	std::multimap<char, int> Transition; // Map with transitions
};
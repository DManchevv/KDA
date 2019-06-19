#pragma once
#include "State.h"
class Automat {
	char alphabet[40];
	int size;
	int id;
	int numb;
	char letter;
	std::string storeLetter;
	int To;
	int StatesNumb;
	int StartState;
	int NumbFinalStates;
	int FinalStates[100];
	int NumbTransitions;
public:
	State* States;
	Automat();
	~Automat();
	Automat(const Automat& CopyFrom);
	const int getSize() const;
	void addState(State newState);
	void PrintStates(int index);
	void PrintStateID(int index);
	void setID(const int newID);
	void setNumb(const int newNumb);
	void setTo(const int newTo);
	void setNumbFinal(const int newNumbFinal);
	void setStatesNumb(const int newStatesNumb);
	void setStartState(const int newStartState);
	void setNumbTransitions(const int newNumbTransitions);
	void setFinalStates(int* newFinalStates);
	void setAlphabet(const char newAlphabet[40]);
	const int getNumb() const;
	const int getTo() const;
	const int getNumbFinal() const;
	const int getStatesNumb() const;
	const int getStartState() const;
	const int getNumbTransitions() const;
	const int getFinalStates(int index) const;
	const int getAlphabet() const;
	const int getID() const;
};
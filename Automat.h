#pragma once
#include "State.h"
class Automat {
	char epsilon = 17;
	std::string alphabet; // automat's alphabet
	int size; // the size of the current alphabet, used to store the number of states when adding a new one
	int id; // the id of the automat
	int numb; // the number of the state on which transition will be added
	char letter; // the symbol of the transition
	std::string storeLetter; // used to help read the automat from a file
	int To; // to which state the transition goes
	int StatesNumb; // the number of states in the automat
	int StartState; // the id of the start state
	int NumbFinalStates; // the number of final states
	int* FinalStates; // used to set the states with the stored id to final
	int NumbTransitions; // the number of all transitions in the automat
public:
	State* States; // a pointer to all states in the automat
	Automat();
	~Automat();
	Automat(const Automat& CopyFrom);
	Automat& operator=(const Automat& other);
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
	void setNumbTransitions(const int newNumbTransitions);          // getters and setters and print functions
	void setFinalStates(int* newFinalStates);
	void setAlphabet(std::string newAlphabet);
	const int getNumb() const;
	const int getTo() const;
	const int getNumbFinal() const;
	const int getStatesNumb() const;
	const int getStartState() const;
	const int getNumbTransitions() const;
	const int getFinalStates(int index) const;
	const std::string getAlphabet() const;
	const int getID() const;
};
#include "Automat.h"
#include "State.h"
#include <iostream>
Automat::Automat() {
	size = 0;
	States = new State[size];
	id = numb = To = StatesNumb = StartState = NumbFinalStates = NumbTransitions = 0;
	FinalStates = nullptr;
}

Automat::~Automat() {
	delete[] States;
	delete[] FinalStates;
}
Automat::Automat(const Automat& CopyFrom) {
	setAlphabet(CopyFrom.alphabet);
	setID(CopyFrom.id);
	setNumb(CopyFrom.numb);
	setStatesNumb(CopyFrom.StatesNumb);
	setStartState(CopyFrom.StartState);
	setNumbFinal(CopyFrom.NumbFinalStates);
	setNumbTransitions(CopyFrom.NumbTransitions);
	FinalStates = new int[CopyFrom.StatesNumb];
	for (size_t i = 0; i < CopyFrom.StatesNumb; i++) {
		FinalStates[i] = CopyFrom.FinalStates[i];
	}
	size = CopyFrom.size;
	States = new State[CopyFrom.size];
	for (size_t i = 0; i < CopyFrom.size; i++) {
		States[i] = CopyFrom.States[i];
	}
}
Automat& Automat::operator=(const Automat& other)
{
	if (this != &other) {
		delete[] States;
		delete[] FinalStates;
		setAlphabet(other.alphabet);
		setID(other.id);
		setNumb(other.numb);
		setStatesNumb(other.StatesNumb);
		setStartState(other.StartState);
		setNumbFinal(other.NumbFinalStates);
		setNumbTransitions(other.NumbTransitions);
		FinalStates = new int[other.StatesNumb];
		for (size_t i = 0; i < other.StatesNumb; i++) {
			FinalStates[i] = other.FinalStates[i];
		}
		size = other.size;
		States = new State[other.size];
		for (size_t i = 0; i < other.size; i++) {
			States[i] = other.States[i];
		}
	}
	return *this;
}
void Automat::setID(const int newID) {
	id = newID;
}
const int Automat::getID() const {
	return id;
}
void Automat::addState(State newState) {
	State* tmp = new State[size + 1];
	for (size_t i = 0; i < size; i++) {
		tmp[i] = States[i];
	}
	tmp[size] = newState;
	delete[] States;
	States = tmp;
	size++;
}
const int Automat::getSize() const {
	return size;
}
void Automat::PrintStates(int index) {
		if (States[index].getFinal()) std::cout << "The state is Final. " << std::endl;
		else std::cout << "The state is not Final. " << std::endl;
}
void Automat::PrintStateID(int index) {
	std::cout << "State: " << States[index].getID() << " : ";
}
void Automat::setNumb(const int newNumb) {
	numb = newNumb;
}
void Automat::setTo(const int newTo) {
	To = newTo;
}
void Automat::setNumbFinal(const int newNumbFinal) {
	NumbFinalStates = newNumbFinal;
	
}
void Automat::setNumbTransitions(const int newNumbTransitions) {
	NumbTransitions = newNumbTransitions;
}
void Automat::setStartState(const int newStartState) {
	StartState = newStartState;
}
void Automat::setFinalStates(int* newFinalStates) {
	for (size_t i = 0; i < StatesNumb; i++) {
		FinalStates[i] = newFinalStates[i];
	}
}
void Automat::setAlphabet(std::string newAlphabet) {
	alphabet = newAlphabet;
}
void Automat::setStatesNumb(const int newStatesNumb) {
	StatesNumb = newStatesNumb;
	FinalStates = new int[StatesNumb + 1];
}
const int Automat::getNumb() const{
	return numb;
}
const int Automat::getStartState() const {
	return StartState;
}
const int Automat::getNumbFinal() const {
	return NumbFinalStates;
}
const int Automat::getTo() const {
	return To;
}
const int Automat::getNumbTransitions() const {
	return NumbTransitions;
}
const int Automat::getFinalStates(int index) const {
	return FinalStates[index];
}
const int Automat::getStatesNumb() const {
	return StatesNumb;
}
const std::string Automat::getAlphabet() const{
	return alphabet;
}
#include "State.h"
#include <iostream>
#include <cstring>
State::State() {
	ID = 0;
	isFinal = false;
}
const int State::getID() const {
	return ID;
}
void State::print() {
	std::cout << ID << std::endl;
}
void State::setID(const int newID) {
	ID = newID;
}
void State::setFinalTrue() {
	isFinal = true;
}
void State::setFinalFalse() {
	isFinal = false;
}
const bool State::getFinal() const{
	return isFinal;
}
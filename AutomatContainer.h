#pragma once
#include "Automat.h"
class AutomatContainer {
private:
	int id;
	int Size;
public:
	AutomatContainer(); 
	~AutomatContainer();
	AutomatContainer(const AutomatContainer& CopyFrom);
	Automat* Container; // Pointer for the Automats in the container
	void addAutomat(Automat newAutomat); // Adding new Automat in the container
	void setID(const int newID); // Setting ID
	const int getID() const; // Getting ID
};
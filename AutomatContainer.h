#pragma once
#include "Automat.h"
class AutomatContainer {
private:
	int id;
	int size;
public:
	AutomatContainer();
	Automat* Container;
	void addAutomat(Automat newAutomat);
	void setID(const int newID);
	const int getID() const;
};
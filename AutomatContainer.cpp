#include "AutomatContainer.h"
AutomatContainer::AutomatContainer() {
	size = 0;
	id = 0;
	Container = new Automat[size];
}
void AutomatContainer::setID(const int newID) {
	id = newID;
}
const int AutomatContainer::getID() const {
	return id;
}
void AutomatContainer::addAutomat(Automat newAutomat) {
	Automat* tmp = new Automat[size + 1];
	for (size_t i = 0; i < size; i++) {
		tmp[i] = Container[i];
	}
	tmp[size] = newAutomat;
	delete[] Container;
	Container = tmp;
	size++;
}
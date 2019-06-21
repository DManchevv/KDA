#include "AutomatContainer.h"
AutomatContainer::AutomatContainer() {
	Size = 0;
	id = 0;
	Container = new Automat[Size];
}
AutomatContainer::~AutomatContainer() {
	delete[] Container;
}
AutomatContainer::AutomatContainer(const AutomatContainer& CopyFrom) {
	id = CopyFrom.id;
	Size = CopyFrom.Size;
	Container = new Automat[CopyFrom.Size + 1];
	for (size_t i = 0; i < CopyFrom.Size; i++) {
		Container[i] = CopyFrom.Container[i];
	}
}
void AutomatContainer::setID(const int newID) {
	id = newID;
}
const int AutomatContainer::getID() const {
	return id;
}
void AutomatContainer::addAutomat(Automat newAutomat) {
	Automat* tmp = new Automat[Size + 1];
	for (size_t i = 0; i < Size; i++) {
		tmp[i] = Container[i];
	}
	tmp[Size] = newAutomat;
	delete[] Container;
	Container = tmp;
	Size++;
}
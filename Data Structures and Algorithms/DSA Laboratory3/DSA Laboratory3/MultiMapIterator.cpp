#include "MultiMapIterator.h"


MultiMapIterator::MultiMapIterator(const MultiMap& map): map(map) {
	this->current_element = 0;
}


void MultiMapIterator::first() {
	this->current_element = 0;
}


bool MultiMapIterator::valid() const {
	if (this->current_element >= this->map.number_of_elements) {
		return false;
	}
	return true;
}

void MultiMapIterator::next() {
	if (!this->valid()) {
		throw 0;
	}
	this->current_element += 1;
}

TElem MultiMapIterator::getCurrent() const {
	if (!this->valid()) {
		throw 0;
	}
	//ihrugrgrggt
}
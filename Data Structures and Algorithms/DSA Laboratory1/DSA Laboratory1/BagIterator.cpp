#include "BagIterator.h"
#include <exception>


BagIterator::BagIterator(const Bag& bag): bag(bag) {
	this->current_element = 0;
}


void BagIterator::first() {
	this->current_element = 0;
}


bool BagIterator::valid() const {
	if (this->current_element >= this->bag.size()) {
		return false;
	}
	return true;
}


void BagIterator::next() {
	if (!this->valid()) {
		throw std::exception();
	}
	this->current_element += 1;
}


TElem BagIterator::getCurrent() const {
	if (!this->valid()) {
		throw std::exception();
	}
	return this->bag.elements[bag.positions[current_element]];
}
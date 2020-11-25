// For time complexity, n is the number of elements in the SMM container

#include "SMMIterator.h"


SMMIterator::SMMIterator(const SortedMultiMap& smm): smm(smm) {
	// time complexity: theta(1)
	this->current_element_position = 0;
	this->current_key_position = this->smm.head;
	this->current_value_position = 0;
}


void SMMIterator::first() {
	// time complexity: theta(1)
	this->current_element_position = 0;
	this->current_key_position = this->smm.head;
	this->current_value_position = 0;
}


void SMMIterator::next() {
	// time complexity: theta(1)
	if (!this->valid()) {
		throw 0;
	}
	this->current_element_position += 1;
	this->current_value_position += 1;

	// Move to the next set of values if needed
	if (this->current_value_position >= this->smm.elements[this->current_key_position].values->size()) {
		this->current_key_position = this->smm.next[this->current_key_position];
		this->current_value_position = 0;
	}
}


bool SMMIterator::valid() const {
	// time complexity: theta(1)
	return(this->current_element_position < this->smm.size());
}


TElem SMMIterator::getCurrent() const {
	// time complexity: theta(1)
	if (!this->valid()) {
		throw 0;
	}
	TKey current_key = this->smm.elements[this->current_key_position].key;
	TValue current_value = this->smm.elements[this->current_key_position].values->get(this->current_value_position);
	TElem result;
	result.first = current_key;
	result.second = current_value;
	return result;
}
#include "BagIterator.h"



BagIterator::BagIterator(const Bag& input_bag) : bag(input_bag) {
	this->current_chain = 0;
	this->current = this->bag.table[0];
	while (this->current == nullptr && this->current_chain < this->bag.table_size - 1) {
		this->current_chain += 1;
		this->current = this->bag.table[current_chain];
	}
}


void BagIterator::first() {
	this->current_chain = 0;
	this->current = this->bag.table[0];
	while (this->current == nullptr && this->current_chain < this->bag.table_size - 1) {
		this->current_chain += 1;
		this->current = this->bag.table[current_chain];
	}
}


void BagIterator::next() {
	if (!this->valid()) {
		throw std::exception{ "Invalid iterator" };
	}
	this->current = this->current->next;
	while (this->current == nullptr && this->current_chain < this->bag.table_size - 1) {
		this->current_chain += 1;
		this->current = this->bag.table[current_chain];
	}
}


bool BagIterator::valid() const {
	if (this->current_chain >= this->bag.table_size) {
		return false;
	}
	return this->current != nullptr;
}


TElem BagIterator::getCurrent() const {
	if (!this->valid()) {
		throw std::exception{ "Invalid iterator" };
	}
	return this->current->info;
}
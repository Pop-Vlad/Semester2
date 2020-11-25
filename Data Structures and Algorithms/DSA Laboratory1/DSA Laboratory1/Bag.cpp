#include <iostream>

#include "Bag.h"
#include "BagIterator.h"



Bag::Bag() {
	this->elements_capacity = 10;
	this->elements_size = 0;
	this->positions_capacity = 10;
	this->positions_size = 0;
	this->elements = new TElem[this->elements_capacity];
	this->positions = new int[this->positions_capacity];
}


Bag::~Bag() {
	delete[] this->elements;
	delete[] this->positions;
}


void Bag::add(TElem new_element) {
	this->resizeIfRequired();
	for (int i = 0; i < this->elements_size; i++) {
		//int dbg = *(this->elements + i*sizeof(int));
		if (this->elements[i] == new_element) {
			this->positions[this->positions_size] = i;
			this->positions_size += 1;
			return;
		}
	}
	this->elements[this->elements_size] = new_element;
	this->positions[this->positions_size] = this->elements_size;
	this->elements_size += 1;
	this->positions_size += 1;
}


bool Bag::remove(TElem element_to_remove) {
	bool at_least_two_occurences = false;
	for (int i = 0; i < this->elements_size; i++) {
		if (this->elements[i] == element_to_remove) {
			for (int j = 0; j < this->positions_size; j++) {
				if (this->positions[j] == i) {
					this->positions[j] = this->positions[this->positions_size - 1];
					this->positions_size -= 1;
					for (int k = j; k < this->positions_size; k++) {
						if (this->positions[k] == i) {
							at_least_two_occurences = true;
							break;
						}
					}
					if (!at_least_two_occurences) {
						this->removeElement(i);
					}
					break;
					
				}
			}
			return true;
		}
	}
	return false;
}


bool Bag::search(TElem element) const {
	for (int i = 0; i < this->elements_size; i++) {
		if (this->elements[i] == element) {
			return true;
		}
	}
	return false;
}


int Bag::nrOccurrences(TElem element) const {
	int occurences = 0;
	int element_index = -1;
	
	if (!this->search(element)) {
		return 0;
	}

	for (int i = 0; i < this->elements_size; i++) {
		if (this->elements[i] == element) {
			element_index = i;
			break;
		}
	}
	for (int j = 0; j < this->positions_size; j++) {
		if (this->positions[j] == element_index) {
			occurences += 1;
		}
	}

	return occurences;
}


int Bag::size() const {
	return this->positions_size;
}


bool Bag::isEmpty() const {
	return (this->size() == 0);
}


BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


void Bag::resizeIfRequired() {
	if (this->elements_size >= this->elements_capacity) {
		this->elements_capacity = (int)(this->elements_capacity*1.5);
		TElem* resized_list = new TElem[this->elements_capacity];
		for (int i = 0; i < this->elements_size; i++) {
			resized_list[i] = this->elements[i];
		}
		delete[] this->elements;
		this->elements = resized_list;
	}
	if (this->positions_size >= this->positions_capacity) {
		this->positions_capacity = (int)(this->positions_capacity*1.5);
		int* resized_list = new int[this->positions_capacity];
		for (int i = 0; i < this->positions_size; i++) {
			resized_list[i] = this->positions[i];
		}
		delete[] this->positions;
		this->positions = resized_list;
	}
}


void Bag::removeElement(int index) {
	this->elements[index] = this->elements[this->elements_size - 1];
	for (int j = 0; j < this->positions_size; j++) {
		if (this->positions[j] == this->elements_size - 1) {
			this->positions[j] = index;
		}
	}
	this->elements_size -= 1;
}
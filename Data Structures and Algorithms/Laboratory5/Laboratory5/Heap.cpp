#include "Heap.h"



int Heap::size() {
	return this->length;
}


Heap::Heap(Relation rel) {
	this->capacity = 10;
	this->length = 0;
	this->elements = new TElem[this->capacity + 1];
	this->relation = rel;
}


Heap::~Heap() {
	delete[] this->elements;
}


void Heap::resize() {
	this->capacity *= 2;
	TElem* new_list = new TElem[this->capacity + 1];
	for (int i = 1; i <= this->length; i++) {
		new_list[i] = this->elements[i];
	}
	delete[] this->elements;
	this->elements = new_list;
}


void Heap::add(TElem new_elem) {
	if (this->length >= this->capacity) {
		this->resize();
	}
	this->length += 1;
	this->elements[this->length] = new_elem;
	this->bubbleUp(this->length);
}


void Heap::bubbleUp(int position) {
	int child = position;
	int parent = position / 2;
	while (!(this->relation(this->elements[parent], this->elements[child])) && parent != 0) {
		TElem aux;
		aux = this->elements[child];
		this->elements[child] = this->elements[parent];
		this->elements[parent] = aux;
		child = parent;
		parent = child / 2;
	}
}


TElem Heap::remove() {
	if (this->length == 0) {
		throw std::exception("Empty heap");
	}
	TElem removed_elem = this->elements[1];
	this->elements[1] = this->elements[this->length];
	this->length -= 1;
	this->bubbleDown(1);
	return removed_elem;
}


void Heap::bubbleDown(int position) {
	int parent = position;
	while (parent <= this->length) {
		int child1 = parent * 2;
		int child2 = parent * 2 + 1;
		int minChild = -1;
		if (child1 <= this->length) {
			minChild = child1;
		}
		if (child2 <= this->length && this->relation(this->elements[child2], this->elements[child1])) {
			minChild = child2;
		}
		if (minChild != -1 && this->relation(this->elements[minChild], this->elements[parent])) {
			TElem aux = this->elements[parent];
			this->elements[parent] = this->elements[minChild];
			this->elements[minChild] = aux;
			parent = minChild;
		}
		else {
			break;
		}
	}
}
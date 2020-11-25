// For time complexity, m is the number of elements in the Values container

#include "Values.h"



Values::Values() {
	// time complexity: theta(1)
	this->capacity = 10;
	this->number_of_elements = 0;
	this->elements = new TValue[this->capacity];
	this->next = new int[this->capacity];
	this->previous = new int[this->capacity];
	this->head = -1;
	this->tail = -1;
	this->first_empty = 0;
	for (int i = 0; i < this->capacity; i++) {
		this->next[i] = i + 1;
		this->previous[i] = i - 1;
	}
	this->next[this->capacity - 1] = -1;
}


Values::~Values() {
	// time complexity: theta(1)
}


int Values::size() {
	// time complexity: theta(1)
	return this->number_of_elements;
}


bool Values::empty() {
	// time complexity: theta(1)
	return(this->number_of_elements == 0);
}


void Values::push_back(TValue new_value) {
	// time complexity: theta(1)
	this->resize();

	// In the case there are no elements yet
	if (this->head == -1) {
		this->head = this->first_empty;
		this->tail = this->first_empty;
		this->first_empty = this->next[this->first_empty];
		this->elements[this->head] = new_value;
		this->next[this->tail] = -1;
		this->number_of_elements += 1;
		return;
	}

	// In the case there are elements
	int new_tail = this->first_empty;
	this->first_empty = this->next[this->first_empty];
	this->elements[new_tail] = new_value;
	this->next[new_tail] = -1;
	this->previous[new_tail] = this->tail;
	this->next[this->tail] = new_tail;
	this->tail = new_tail;
	this->number_of_elements += 1;
}


void Values::pop_back() {
	// time complexity: theta(1)
	this->previous[this->first_empty] = this->tail;
	this->next[this->tail] = this->first_empty;
	this->first_empty = this->tail;
	this->tail = this->previous[this->tail];
	this->previous[this->first_empty] = -1;
	this->next[this->tail] = -1;
}


TValue Values::get(int index) {
	// time complexity: O(m)
	int current_element = this->head;
	for (int i = 0; i < index; i++) {
		current_element = this->next[current_element];
	}
	return this->elements[current_element];
}


void Values::set(int index, TValue value) {
	// time complexity: O(m)
	int current_element = this->head;
	for (int i = 0; i < index; i++) {
		current_element = this->next[current_element];
	}
	this->elements[current_element] = value;
}


TValue Values::back() {
	// time complexity: theta(1)
	return this->elements[this->tail];
}


void Values::resize() {
	this->capacity *= 1.5;

	// Create new arrays
	TValue* new_elements = new TValue[this->capacity];
	int* new_next = new int[this->capacity];
	int* new_previous = new int[this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		new_next[i] = i + 1;
		new_previous[i] = i - 1;
	}
	new_next[this->capacity - 1] = -1;

	// Copy the data
	int i = 0;
	int current_element = this->head;
	while (current_element != -1) {
		new_elements[i] = this->elements[current_element];
		current_element = this->next[current_element];
		i++;
	}
	new_next[i - 1] = -1;
}
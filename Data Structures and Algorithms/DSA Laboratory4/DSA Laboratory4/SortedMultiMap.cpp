// For time complexity, n is the number of elements in the SortedMultiMap container

#include "SortedMultiMap.h"
#include "SMMIterator.h"



SortedMultiMap::SortedMultiMap(Relation relation) {
	// time complexity: theta(1)
	this->relation = relation;
	this->capacity = 1000;
	this->number_of_elements = 0;
	this->elements = new Info[capacity];
	this->next = new int[capacity];
	this->previous = new int[capacity];

	// Initialize the data of next[] and previous[]
	for (int i = 0; i < capacity; i++) {
		this->next[i] = i + 1;
		this->previous[i] = i - 1;
	}
	this->next[capacity - 1] = -1;
	this->head = -1;
	this->tail = -1;
	this->first_empty = 0;
}


void SortedMultiMap::add(TKey key, TValue value) {
	// time complexity: O(n)
	int current_position = this->head;
	while (current_position != -1 && this->elements[current_position].key != key) {
		current_position = this->next[current_position];
	}
	if (current_position == -1) { // The key does not exist yet
		int position;
		position = this->insertNewKey(key);
		this->elements[position].values->push_back(value);
	}
	else { // The key already exists
		this->elements[current_position].values->push_back(value);
	}
	this->number_of_elements += 1;
}


vector<TValue> SortedMultiMap::search(TKey key) const {
	// time complexity: O(n)
	int current_position = this->head;
	while (current_position != -1 && this->elements[current_position].key != key) {
		current_position = this->next[current_position];
	}
	vector<TValue> new_vector;
	if (current_position == -1) { // The key does not exist
		return new_vector;
	}
	for (int i = 0; i < this->elements[current_position].values->size(); i++) {
		new_vector.push_back(this->elements[current_position].values->get(i));
	}
	return new_vector;
}


bool SortedMultiMap::remove(TKey key, TValue value) {
	// time complexity: O(n)
	int current_position = this->head;
	while (current_position != -1 && this->elements[current_position].key != key) {
		current_position = this->next[current_position];
	}
	if (current_position == -1) {
		return false;
	}
	for (int i = 0; i < this->elements[current_position].values->size(); i++) {
		if (this->elements[current_position].values->get(i) == value) {
			this->elements[current_position].values->set(i, this->elements[current_position].values->back());
			this->elements[current_position].values->pop_back();
			if (this->elements[current_position].values->empty()) { // Also remove the key
				this->removeKey(current_position);
			}
			this->number_of_elements -= 1;
			return true;
		}
	}
	return false;
}


int SortedMultiMap::size() const {
	// time complexity: theta(1)
	return this->number_of_elements;
}


bool SortedMultiMap::isEmpty() const {
	// time complexity: theta(1)
	return (this->number_of_elements == 0);
}


SMMIterator SortedMultiMap::iterator() const {
	// time complexity: theta(1)
	return SMMIterator(*this);
}


SortedMultiMap::~SortedMultiMap() {
	// time complexity: theta(1)
	int current_position = this->head;
	while (current_position != -1) {
		auto vector_to_remove = this->elements[current_position].values;
		delete vector_to_remove;
		current_position = this->next[current_position];
	}
	delete[] this->elements;
}


int SortedMultiMap::insertNewKey(TKey key) {
	this->resize();
	if (this->head == -1) { // The SMM is empty, add first key
		this->head = this->first_empty;
		this->tail = this->head;
		this->first_empty = this->next[this->first_empty];
		Values* empty_vector = new Values();
		this->elements[this->head].key = key;
		this->elements[this->head].values = empty_vector;
		this->next[this->tail] = -1;
		return this->head;
	}

	int current_position = this->head;
	while (current_position != -1 && this->relation(this->elements[current_position].key, key)) {
		current_position = this->next[current_position];
	}

	if (current_position == this->head) { // Insert at beginning
		current_position = this->first_empty;
		this->first_empty = this->next[first_empty];
		this->next[current_position] = this->head;
		this->previous[current_position] = -1;
		this->previous[this->head] = current_position;
		this->head = current_position;
	}
	else if (current_position == -1) { // Insert at end
		current_position = this->first_empty;
		this->previous[current_position] = this->tail;
		this->next[this->tail] = current_position;
		this->first_empty = this->next[this->first_empty];
		this->tail = current_position;
		this->next[this->tail] = -1;
	}
	else { // Insert somewhere between
		int previous_position = this->previous[current_position];
		int next_position = current_position;
		current_position = this->first_empty;
		this->first_empty = this->next[first_empty];
		this->previous[current_position] = previous_position;
		this->next[current_position] = next_position;
		this->next[previous_position] = current_position;
		this->previous[next_position] = current_position;
	}

	Values* empty_vector = new Values();
	this->elements[current_position].key = key;
	this->elements[current_position].values = empty_vector;
	return current_position;
}


void SortedMultiMap::removeKey(int position) {
	if (position == this->head) { // Remove head
		int next_element = this->next[position];
		this->previous[next_element] = -1;
		this->head = next_element;
	}
	else if (position == this->tail) { // Remove tail
		int previous_element = this->previous[position];
		this->next[previous_element] = -1;
		this->tail = previous_element;
	}
	else { // Remove middle
		int previous_element = this->previous[position];
		int next_element = this->next[position];
		this->next[previous_element] = next_element;
		this->previous[next_element] = previous_element;
	}
	auto vector_to_remove = this->elements[position].values;
	delete vector_to_remove;
	this->next[position] = this->first_empty;
	this->first_empty = position;
}


void SortedMultiMap::resize() {
	if (this->first_empty == -1) {
		this->capacity *= 1.5;
		Info* new_elements = new Info[this->capacity];
		int* new_next = new int[this->capacity];
		int* new_previous = new int[this->capacity];

		for (int i = 0; i < this->capacity; i++) {
			new_next[i] = i + 1;
			new_previous[i] = i - 1;
		}
		new_next[capacity - 1] = -1;

		int new_index = 0;
		int old_index = this->head;
		while (old_index != -1) {
			new_elements[new_index] = this->elements[old_index];
			new_index += 1;
			old_index = this->next[old_index];
		}
		new_next[new_index - 1] = -1;
		this->first_empty = new_index;

		this->elements = new_elements;
		this->next = new_next;
		this->previous = new_previous;
	}
}


vector<TValue> SortedMultiMap::RemoveKey(TKey key) {
	// Time complexity: O(n*m);
	vector<TValue> values = this->search(key);
	for (int i = 0; i < values.size(); i++) {
		this->remove(key, values.at(i));
	}
	return values;
}
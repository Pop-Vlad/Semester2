#include "Bag.h"
#include "BagIterator.h"



unsigned int h(TElem k){
	double temp = k * ratio;
	double fractional_part = temp - (int)temp;
	if (fractional_part < 0) {
		fractional_part += 1;
	}
	return (unsigned int)(UINT32_MAX * fractional_part);
};



Bag::Bag(const int& table_size) {
	this->table_size = table_size;
	this->number_of_elements = 0;
	this->hash = h;
	this->table = new Node*[this->table_size]();
}


void Bag::resizeAndRehash() {
	const int number_of_elements = this->number_of_elements;
	TElem* elements = new TElem[number_of_elements];
	int index = 0;

	for (int i = 0; i < this->table_size; i++) {
		Node* current = this->table[i];
		Node* to_remove;
		while (current != nullptr) {
			elements[index] = current->info;
			index++;
			to_remove = current;
			current = current->next;
			delete to_remove;
		}
	}

	delete[] this->table;
	this->table_size = this->table_size * 2;
	this->table = new Node*[this->table_size]();

	for (int i = 0; i < index; i++) {
		int position = this->hash(elements[i]) % this->table_size;
		Node* new_node = new Node;
		new_node->info = elements[i];
		new_node->next = this->table[position];
		this->table[position] = new_node;
	}

	delete[] elements;
}


void Bag::add(TElem e) {
	if (this->number_of_elements / this->table_size >= 3) {
		this->resizeAndRehash();
	}
	int position = this->hash(e) % this->table_size;
	Node* new_node = new Node;
	new_node->info = e;
	new_node->next = this->table[position];
	this->table[position] = new_node;
	this->number_of_elements += 1;
}


bool Bag::remove(TElem e) {
	int position = this->hash(e) % this->table_size;
	Node* current = this->table[position];
	if (current == nullptr) {
		return false;
	}
	if (current->info == e) {
		this->table[position] = current->next;
		this->number_of_elements -= 1;
		delete current;
		return true;
	}
	while (current->next != nullptr && current->next->info != e) {
		current = current->next;
	}
	if (current->next == nullptr) {
		return false;
	}
	Node* node_to_remove = current->next;
	current->next = node_to_remove->next;
	this->number_of_elements -= 1;
	delete node_to_remove;
	return true;
}


bool Bag::search(TElem e) const {
	int position = this->hash(e) % this->table_size;
	Node* current = this->table[position];
	while (current != nullptr && current->info != e) {
		current = current->next;
	}
	if (current == nullptr) {
		return false;
	}
	return true;
}


int Bag::nrOccurrences(TElem e) const {
	int position = this->hash(e) % this->table_size;
	Node* current = this->table[position];
	int count = 0;
	while (current != nullptr) {
		if (current->info == e) {
			count += 1;
		}
		current = current->next;
	}
	return count;
}


int Bag::size() const {
	return this->number_of_elements;
}


BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

bool Bag::isEmpty() const {
	return this->number_of_elements == 0;
}


int Bag::uniqueCount() const {
	int count = 0;
	std::vector<TElem> unique_elements;
	bool new_element;
	for (int i = 0; i < this->table_size; i++) { // for each chain in the hastable
		Node* current = this->table[i];
		new_element = true;
		while (current != nullptr) { // for each node in the chain
			for (int j = 0; j < unique_elements.size(); j++) {
				if (unique_elements[j] == current->info) { // check if element is already in unique_elements
					new_element = false;
					break;
				}
			}
			if (new_element) {
				unique_elements.push_back(current->info);
				count++;
			}
			current = current->next;
		}
	}
	return count;
}


Bag::~Bag() {
	delete[] this->table;
}
#include "MultiMap.h"
#include "MultiMapIterator.h"


MultiMap::MultiMap() {
	this->keys_list.head->next_node = this->keys_list.tail;
	this->keys_list.head->previous_node = NULL;
	this->keys_list.head->key = NULL;
	this->keys_list.tail->next_node = NULL;
	this->keys_list.tail->previous_node = this->keys_list.head;
	this->keys_list.tail->key = NULL;
	this->number_of_nodes = 2;
	this->number_of_elements = 0;
}


MultiMap::~MultiMap() {
	Node* current_node = this->keys_list.head;
	while (current_node != this->keys_list.tail) {
		current_node = current_node->next_node;
		delete current_node->previous_node;
	}
	delete this->keys_list.tail;
	delete this;
}


void MultiMap::add(TKey key, TValue value) {
	Node* current_node = this->keys_list.head;
	for (int i = 1; i < this->number_of_nodes - 1; i++) {
		if (current_node->key == key) {
			break;
		}
		current_node = current_node->next_node;
	}
	if (current_node->key == key) {
		current_node->values.push_back(value);
	}
	else {
		this->insertNewNode(key, value);
		this->number_of_nodes += 1;
	}
	this->number_of_elements += 1;
}


bool MultiMap::remove(TKey key, TValue value) {
	Node* current_node = this->keys_list.head;
	for (int i = 1; i < this->number_of_nodes - 1; i++) {
		if (current_node->key == key) {
			break;
		}
		current_node = current_node->next_node;
	}
	if (current_node->key == key) {
		for (int j = 0; j < (int)current_node->values.size(); j++) {
			if (current_node->values[j] == value) {
				current_node->values[j] = current_node->values.back();
				current_node->values.pop_back();
				if (current_node->values.empty()) {
					this->removeNode(current_node);
					this->number_of_nodes -= 1;
				}
				this->number_of_elements -= 1;
				return true;
			}
		}
	}
	return false;
}


vector<TValue> MultiMap::search(TKey key) const {
	Node* current_node = this->keys_list.head;
	while (current_node->key != key || current_node->next_node == NULL) {
		current_node = current_node->next_node;
	}
	if (current_node->key == key) {
		return current_node->values;
	}
	vector<TValue> empty;
	return empty;
}


int MultiMap::size() const{
	return this->number_of_elements;
}


bool MultiMap::isEmpty() const {
	return(this->number_of_elements == 0);
}


MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


void MultiMap::insertNewNode(TKey key, TValue value) {
	Node* left_node = this->keys_list.tail;
	Node* right_node = left_node->previous_node;
	Node* new_node = new Node();
	new_node->next_node = left_node;
	new_node->previous_node = right_node;
	new_node->key = key;
	new_node->values.push_back(value);
	left_node->next_node = new_node;
	right_node->previous_node = new_node;
}


void MultiMap::removeNode(Node* node_to_remove) {
	Node* left_node = node_to_remove->previous_node;
	Node* right_node = node_to_remove->next_node;
	delete node_to_remove;
	left_node->next_node = right_node;
	right_node->previous_node = left_node;
}
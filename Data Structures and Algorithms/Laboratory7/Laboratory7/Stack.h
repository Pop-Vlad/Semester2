#pragma once



template <typename GenericElement>
class Stack {


private:

	GenericElement** elements;
	int capacity;
	int size;

	void resize();


public:

	Stack();

	void push(GenericElement e);

	GenericElement pop();

	bool empty();


};



template <typename GenericElement>
Stack<GenericElement>::Stack() {
	this->elements = new GenericElement*[100];
	this->capacity = 100;
	this->size = 0;
}


template <typename GenericElement>
void Stack<GenericElement>::push(GenericElement e) {
	if (this->size >= this->capacity)
		this->resize();
	GenericElement* new_element = new GenericElement;
	*new_element = e;
	this->elements[this->size] = new_element;
	this->size += 1;
}


template <typename GenericElement>
GenericElement Stack<GenericElement>::pop() {
	GenericElement removed = *this->elements[this->size - 1];
	delete this->elements[this->size - 1];
	this->size -= 1;
	return removed;
}


template <typename GenericElement>
void Stack<GenericElement>::resize() {
	this->capacity *= 1.618;
	GenericElement** new_array = new GenericElement*[this->capacity];
	for (int i = 0; i < this->size; i++) {
		new_array[i] = this->elements[i];
	}
	delete[] this->elements;
	this->elements = new_array;
}


template <typename GenericElement>
bool Stack<GenericElement>::empty() {
	return this->size == 0;
}
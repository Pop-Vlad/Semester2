#pragma once

typedef int TValue;



class Values {


private:

	int capacity;
	int number_of_elements;
	TValue* elements;
	int* next;
	int* previous;
	int head;
	int tail;
	int first_empty;

	void resize();


public:

	Values();

	~Values();

	int size();

	bool empty();

	void push_back(TValue new_value);

	void pop_back();

	TValue get(int index);

	void set(int index, TValue value);

	TValue back();


};
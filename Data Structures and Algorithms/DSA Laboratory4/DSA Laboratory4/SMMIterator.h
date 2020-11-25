#pragma once

#include "SortedMultiMap.h"


//unidirectional iterator for a container
class SMMIterator {


private:

	//contains a reference of the container it iterates over
	const SortedMultiMap& smm;

	int current_element_position;
	int current_key_position;
	int current_value_position;


public:

	//Constructor receives a reference of the container.
	//after creation the iterator will refer to the first element of the container, or it will be invalid if the container is empty
	SMMIterator(const SortedMultiMap& smm);

	//sets the iterator to the first element of the container
	void first();

	//moves the iterator to the next element
	//throws exception if the iterator is not valid
	void next();

	//checks if the iterator is valid
	bool valid() const;

	//returns the value of the current element from the iterator
	// throws exception if the iterator is not valid
	TElem getCurrent() const;


};
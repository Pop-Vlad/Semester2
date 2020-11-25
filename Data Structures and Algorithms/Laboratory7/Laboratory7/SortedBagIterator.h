#pragma once

#include "SortedBag.h"
#include "Stack.h"

#include <exception>
#include <stack>
#include <vector>



//unidirectional iterator for a container
class SortedBagIterator {


private:

	//contains a reference of the container it iterates over
	const SortedBag& sb;

	/* representation specific for the iterator*/
	BSTNode* current_node;
	Stack<BSTNode*> stack;
	Stack<BSTNode*> prev_stack;
	std::vector<Stack<BSTNode*>> history;


public:

	//Constructor receives a reference of the container.
	//after creation the iterator will refer to the first element of the container, or it will be invalid if the container is empty
	//Time complexity: O(n)
	SortedBagIterator(const SortedBag& sb);

	//sets the iterator to the first element of the container
	//Time complexity: O(n)
	void first();

	//moves the iterator to the next element
	//throws exception if the iterator is not valid
	//Time complexity: O(n)
	void next();

	//changes teh current element from the iterator to the previous element, or, if the current element was the first, makes the iterator invalid
	//throws an exception if the iterator is not valid
	void previous();

	//checks if the iterator is valid
	//Time complexity: theta(1)
	bool valid() const;

	//returns the value of the current element from the iterator
	// throws exception if the iterator is not valid
	//Time complexity: theta(1)
	TElem getCurrent() const;


};
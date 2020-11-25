#pragma once

#include <exception>

typedef int TElem;

typedef bool(*Relation) (TElem e1, TElem e2);



class Heap {


private:

	// The capacity of the array containing the elements
	int capacity;

	// The number of the elements in the heap
	int length;

	// The array containing the elements
	TElem* elements;

	// The relation by which the elements are sorted
	Relation relation;

	// Resize the capacity of the array of elements
	// Time complexity: theta(n)
	void resize();

	// Sort the elements up the heap from a given position
	// Time complexity: O(log2(n))
	void bubbleUp(int position);

	// Sort the elements down the heap from a given position
	// Time complexity: O(log2(n))
	void bubbleDown(int position);


public:

	// Get the number of elements in the heap
	// Time complexity: theta(1)
	int size();

	// Constructor for the heap structure
	// Time complexity: theta(1)
	Heap(Relation rel);

	// Add a new element to the heap
	// Time complexity: O(log2(n))
	void add(TElem new_elem);

	// Remove the root of the heap
	// Time complexity: O(log2(n))
	TElem remove();

	// Destructor for the heap structure
	// Time complexity: theta(1)
	~Heap();


};


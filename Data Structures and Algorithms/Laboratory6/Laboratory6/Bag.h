#pragma once

#define ratio 0.61803398875

#include <vector>

typedef int TElem;

typedef unsigned int(*TFunction)(TElem e);

typedef struct Node{
	TElem info;
	Node* next;
} Node;



class Bag {


private:

	friend class BagIterator;

	/*representation of Bag*/
	int table_size;
	TFunction hash;
	Node** table;
	int number_of_elements;

	//Modify the size of the hashtable
	void resizeAndRehash();


public:

	//constructor
	Bag(const int& table_size = 1000);

	//adds an element to the bag
	void add(TElem e);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//count the number of unique elements in the bag
	//Time complexity: O(n*k)
	int uniqueCount() const;

	//destructor
	~Bag();


};
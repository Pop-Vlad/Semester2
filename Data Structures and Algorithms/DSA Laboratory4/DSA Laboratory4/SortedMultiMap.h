#pragma once

#include <utility>
#include <vector>

#include "Values.h"

typedef int TKey;

typedef std::pair<TKey, TValue> TElem;

typedef bool(*Relation)(TKey, TKey);

using namespace std;

typedef struct {
	Values* values;
	TKey key;
} Info;



class SortedMultiMap {


private:

	friend class SMMIterator;

	Relation relation;
	Info* elements;
	int* next;
	int* previous;
	int head;
	int tail;
	int first_empty;
	int number_of_elements;
	int capacity;

	void resize();

	int insertNewKey(TKey key);

	void removeKey(int position);


public:

	// constructor
	SortedMultiMap(Relation relation);

	//adds a new key value pair to the sorted multi map
	void add(TKey key, TValue value);

	//returns the values belonging to a given key
	vector<TValue> search(TKey key) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
	bool remove(TKey key, TValue value);

	//returns the number of key-value pairs from the sorted multimap
	int size() const;

	//verifies if the sorted multi map is empty
	bool isEmpty() const;

	// returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
	SMMIterator iterator() const;

	// destructor
	~SortedMultiMap();

	// removes a key with all its values
	// returns a vector with the values that were previously associated with this value (and were removed)
	vector<TValue> RemoveKey(TKey key);

};
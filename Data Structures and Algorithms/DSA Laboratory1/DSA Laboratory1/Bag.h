#pragma once

typedef int TElem;



class Bag {


	private:

		//allow the iterator to access the elements
		friend class BagIterator;

		//representation of Bag
		TElem* elements;
		int* positions;
		int elements_size;
		int elements_capacity;
		int positions_size;
		int positions_capacity;

		//resize to a greater capacity
		void resizeIfRequired();

		//remove an element from the unique elements list (used when the last occurence is removed)
		void removeElement(int index);


	public:

		//constructor
		Bag();

		//adds an element to the bag
		void add(TElem element);

		//removes one occurrence of an element from a bag
		//returns true if an element was removed, false otherwise (if e was not part of the bag)
		bool remove(TElem element);

		//checks if an element appearch is the bag
		bool search(TElem element) const;

		//returns the number of occurrences for an element in the bag
		int nrOccurrences(TElem element) const;

		//returns the number of elements from the bag
		int size() const;

		//returns an iterator for this bag
		BagIterator iterator() const;

		//checks if the bag is empty
		bool isEmpty() const;

		//destructor
		~Bag();


};
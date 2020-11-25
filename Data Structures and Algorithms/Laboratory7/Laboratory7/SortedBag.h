#pragma once



typedef int TComp;

typedef TComp TElem;

typedef bool(*Relation)(TComp, TComp);

typedef struct BSTNode{
	TElem info;
	BSTNode* left;
	BSTNode* right;
} BSTNode;



class SortedBag {


private:

	/*representation of SortedBag*/
	BSTNode* root;
	Relation r;
	int nr_elements;

	BSTNode* initNode(TComp e);
	void insertRecursive(BSTNode* node, const TComp& e);
	void removeSubtree(BSTNode* node);

	friend class SortedBagIterator;


public:

	//constructor
	//Time complexity: theta(1)
	SortedBag(Relation r);

	//adds an element to the sorted bag
	//Time complexity: O(n)
	void add(TComp e);

	//removes one occurrence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	//Time complexity: O(n)
	bool remove(TComp e);

	//checks if an element appearch is the sorted bag
	//Time complexity: O(n)
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	//Time complexity: O(n)
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	//Time complexity: theta(1)
	int size() const;

	//returns an iterator for this sorted bag
	//Time complexity: O(n)
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	//Time complexity: theta(1)
	bool isEmpty() const;

	//destructor
	//Time complexity: theta(n)
	~SortedBag();


};
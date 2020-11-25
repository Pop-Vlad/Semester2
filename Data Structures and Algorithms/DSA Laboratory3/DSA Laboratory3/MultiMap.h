#pragma once

#include <vector>
#include <utility>

using namespace std;

typedef int TKey;

typedef int TValue;

typedef std::pair<TKey, TValue> TElem;



typedef struct Node {
	Node* previous_node;
	Node* next_node;
	TKey key;
	vector<TValue> values;
} Node;

typedef struct DLL {
	Node* head;
	Node* tail;
} DLL;



class MultiMap {


	private:

		//allow the iterator to access the elements
		friend class MultiMapIterator;

		//adds a new nude in the dll
		void insertNewNode(TKey key, TValue value);

		//remove a node from dll
		void removeNode(Node* node_to_remove);

		/* representation of the MultiMap */
		DLL keys_list;
		int number_of_nodes;
		int number_of_elements;


	public:

		//constructor
		MultiMap();

		//adds a key value pair to the multimap
		void add(TKey key, TValue value);

		//removes a key value pair from the multimap
		//returns true if the pair was removed (if it was in the multimap) and false otherwise
		bool remove(TKey key, TValue value);

		//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
		vector<TValue> search(TKey key) const;

		//returns the number of pairs from the multimap
		int size() const;

		//checks whether the multimap is empty
		bool isEmpty() const;

		//returns an iterator for the multimap
		MultiMapIterator iterator() const;

		//descturctor
		~MultiMap();


};

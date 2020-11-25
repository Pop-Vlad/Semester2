#include "ExtraFeature.h"
#include <iostream>


Bag* difference(Bag minuend, Bag subtracthend) {
	Bag* result = new Bag();
	TElem unique_elements[1000];
	int unique_elements_size = 0;
	BagIterator minuend_iterator = minuend.iterator();
	int i;

	// Create the list with unique elements from the minuend
	while (minuend_iterator.valid()) {
		TElem current_element = minuend_iterator.getCurrent();
		for (i = 0; i < unique_elements_size; i++) {
			if (unique_elements[i] == current_element) {
				break;
			}
		}
		if (unique_elements[i] != current_element) {
			unique_elements[unique_elements_size] = current_element;
			unique_elements_size += 1;
		}
		minuend_iterator.next();
	}

	//Add to the new bag
	for (i = 0; i < unique_elements_size; i++) {
		TElem current_element = unique_elements[i];
		int difference;
		difference = minuend.nrOccurrences(current_element) - subtracthend.nrOccurrences(current_element);
		while (difference > 0) {
			printf("added %d \n", (int)current_element );
			result->add(current_element);
			difference -= 1;
		}
	}

	return result;
}


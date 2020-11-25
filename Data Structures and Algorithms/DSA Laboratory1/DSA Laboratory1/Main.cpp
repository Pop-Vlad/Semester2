#include <iostream>
#include <assert.h>

#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include "ExtraFeature.h"

using namespace std;



int main() {
	testAll();
	testAllExtended();
	
	Bag bag1 = Bag();
	Bag bag2 = Bag();
	bag1.add(1);
	bag1.add(1);
	bag1.add(1);
	bag1.add(2);
	bag1.add(2);
	bag1.add(3);
	bag1.add(4);
	bag2.add(10);
	bag2.add(10);
	bag2.add(1);
	bag2.add(1);
	bag2.add(2);
	bag2.add(3);
	bag1.add(1);
	Bag* result = difference(bag1, bag2);

	assert(result->size() == 4);
	assert(result->nrOccurrences(2) == 1);
	assert(result->search(1));
	assert(!result->search(3));
	
}
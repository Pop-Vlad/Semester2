#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

#include <assert.h>
#include <ctime>
#include <iostream>


void testUniqueCount() {
	Bag b1;
	b1.add(0);
	b1.add(1);
	b1.add(2);
	b1.add(0);
	b1.add(0);
	b1.add(2);
	assert(b1.uniqueCount() == 3);
	Bag b2;
	b2.add(-12);
	assert(b2.uniqueCount() == 1);
	for (int i = 0; i < 100; i++) {
		b2.add(1);
		b2.add(2);
		b2.add(i % 10);
	}
	assert(b2.uniqueCount() == 11);
	for (int i = 0; i < 100; i++) {
		b2.add(2 * (i / 2));
	}
	assert(b2.uniqueCount() == 54);
}



int main() {
	testUniqueCount();
	clock_t start = clock();
	testAll();
	testAllExtended();
	clock_t finish = clock();
	std::cout << "Execution time: " << finish - start << "ms\n";
	return 0;
}
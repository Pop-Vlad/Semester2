#include "SortedBag.h"
#include "SortedBagIterator.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

#include <time.h>
#include <iostream>
#include <assert.h>

bool relation(TComp r1, TComp r2) {
	return r1 <= r2;
}

void testPrevious() {
	SortedBag sb = SortedBag{relation};
	sb.add(10);
	sb.add(5);
	sb.add(15);
	sb.add(7);
	sb.add(3);
	sb.add(12);
	sb.add(18);
	sb.add(1);
	SortedBagIterator it = sb.iterator();
	// 1 3 5 7 10 12 15 18
	assert(it.getCurrent() == 1);
	it.previous();
	try {
		it.getCurrent();
		assert(false);
	}
	catch (std::exception& e) {
		assert(true);
	}
	it.first();
	assert(it.getCurrent() == 1);
	it.next();
	assert(it.getCurrent() == 3);
	it.next();
	assert(it.getCurrent() == 5);
	it.next();
	assert(it.getCurrent() == 7);
	it.previous();
	assert(it.getCurrent() == 5);
	it.previous();
	assert(it.getCurrent() == 3);
	it.previous();
	assert(it.getCurrent() == 1);
}

int main() {
	testPrevious();
	clock_t start = clock();
	testAll();
	testAllExtended();
	clock_t finish = clock();
	std::cout << "Execution time: " << finish - start << "ms\n";
	return 0;
}
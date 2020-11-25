#include "SortedMultiMap.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

#include <assert.h>

bool relation2(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}



int main() {
	SortedMultiMap smm = SortedMultiMap(relation2);
	smm.add(1, 2);
	smm.add(1, 3);
	smm.add(2, 2);
	smm.add(2, 3);
	smm.add(1, 1);
	smm.add(1, 0);
	vector<TValue> results = smm.RemoveKey(1);
	assert(results.size() == 4);
	assert(results.at(0) == 2);
	assert(results.at(1) == 3);
	assert(results.at(2) == 1);
	assert(results.at(3) == 0);
	testAll();
	testAllExtended();
	return 0;
}
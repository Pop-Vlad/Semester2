#include <crtdbg.h>

#include "SortedMultiMap.h"
#include "ShortTest.h"
#include "ExtendedTest.h"


int main() {
	testAll();
	testAllExtended();
	_CrtDumpMemoryLeaks();
	return 0;
}
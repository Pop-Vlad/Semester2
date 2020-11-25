#pragma once

#include <list>

#include "Heap.h"

using namespace std;



// Merges k sorted lists into one single list.
// The input lists are sorted considering the relation and the results should be sorted in the same way.
// Time complexity: O(n*log2(n)), n = the number of all the elements in the lists combined
list<TElem> mergeLists(list<list<TElem>> inputLists, Relation rel);
#include "P1.h"



list<TElem> mergeLists(list<list<TElem>> input_lists, Relation relation) {
	Heap heap(relation);
	list<TElem> res;
	for (auto current_list = input_lists.begin(); current_list != input_lists.end(); current_list++) {
		for (auto current_elem = current_list->begin(); current_elem != current_list->end(); current_elem++) {
			heap.add(*current_elem);
		}
	}
	while (heap.size() > 0) {
		res.push_back(heap.remove());
	}
	return res;
}

#include "SortedBagIterator.h"
#include "SortedBag.h"



SortedBagIterator::SortedBagIterator(const SortedBag& sb) : sb(sb) {
	this->first();
}


void SortedBagIterator::first() {
	this->stack = Stack<BSTNode*>{};
	this->prev_stack = Stack<BSTNode*>{};
	this->history = std::vector<Stack<BSTNode*>>{};
	this->prev_stack.push(nullptr);
	this->history.push_back(this->stack);
	BSTNode* current = this->sb.root;
	if (current == nullptr) {
		this->current_node = current;
		return;
	}
	while (current != nullptr) {
		this->stack.push(current);
		current = current->left;
	}
	this->current_node = stack.pop();
}


void SortedBagIterator::next() {
	this->history.push_back(this->stack);
	this->prev_stack.push(this->current_node);
	if (!this->valid())
		throw std::exception{ "Invalid iterator" };

	if (this->current_node->right != nullptr) {
		this->current_node = this->current_node->right;
		while (this->current_node->left != nullptr) {
			this->stack.push(this->current_node);
			this->current_node = this->current_node->left;
		}
		
	}
	else {
		if (this->stack.empty())
			this->current_node = nullptr;
		else {
			this->current_node = this->stack.pop();
		}
	}
}


void SortedBagIterator::previous() {
	if (!this->valid())
		throw std::exception{ "Invalid iterator" };

	this->current_node = this->prev_stack.pop();
	this->stack = this->history.back();
	this->history.pop_back();
}


bool SortedBagIterator::valid() const {
	return this->current_node != nullptr;
}


TElem SortedBagIterator::getCurrent() const {
	if (!this->valid())
		throw std::exception{ "Invalid iterator" };
	return this->current_node->info;
}
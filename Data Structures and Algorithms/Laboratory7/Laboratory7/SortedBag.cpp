#include "SortedBag.h"
#include "SortedBagIterator.h"



SortedBag::SortedBag(Relation r) {
	this->root = nullptr;
	this->r = r;
	this->nr_elements = 0;
}


void SortedBag::add(TComp e) {
	if (this->root == nullptr) {
		this->root = this->initNode(e);
		this->nr_elements = 1;
	}
	else {
		this->insertRecursive(this->root, e);
		this->nr_elements++;
	}
}


BSTNode* SortedBag::initNode(TComp e) {
	BSTNode* new_node = new BSTNode;
	new_node->info = e;
	new_node->left = nullptr;
	new_node->right = nullptr;
	return new_node;
}


void SortedBag::insertRecursive(BSTNode* node, const TComp& e) {
	if (this->r(node->info, e)) {
		if (node->right == nullptr) {
			node->right = initNode(e);
			return;
		}
		else
			this->insertRecursive(node->right, e);
	}
	else {
		if (node->left == nullptr) {
			node->left = initNode(e);
			return;
		}
		else
			this->insertRecursive(node->left, e);
	}
}


bool SortedBag::remove(TComp e) {
	BSTNode* current = this->root;
	BSTNode* parent = nullptr;
	bool found = false;

	while (current != nullptr && !found) {
		if (current->info == e)
			found = true;
		else {
			if (this->r(current->info, e)) {
				parent = current;
				current = current->right;
			}
			else {
				parent = current;
				current = current->left;
			}
		}
	}
	if (!found)
		return false;

	if (parent == nullptr) {
		if (current->left == nullptr && current->right == nullptr)
			this->root = nullptr;
		else if (current->left != nullptr && current->right == nullptr)
			this->root = current->left;
		else if (current->left == nullptr && current->right != nullptr)
			this->root = current->right;
		else {
			BSTNode* max_node = current->right;
			BSTNode* parent = current;
			while (max_node->left != nullptr) {
				parent = max_node;
				max_node = max_node->left;
			}
			current->info = max_node->info;
			if (parent->left == max_node)
				parent->left = max_node->right;
			else
				parent->right = max_node->right;
			current = max_node;
		}
		delete current;
		this->nr_elements--;
		return true;
	}

	if (current->left == nullptr && current->right == nullptr) {
		if (parent->left == current)
			parent->left = nullptr;
		else
			parent->right = nullptr;
	}
	else if (current->left != nullptr && current->right == nullptr) {
		if (parent->left == current)
			parent->left = current->left;
		else
			parent->right = current->left;
	}
	else if (current->left == nullptr && current->right != nullptr) {
		if (parent->left == current)
			parent->left = current->right;
		else
			parent->right = current->right;
	}
	else {
		BSTNode* max_node = current->right;
		BSTNode* parent = current;
		while (max_node->left != nullptr) {
			parent = max_node;
			max_node = max_node->left;
		}
		current->info = max_node->info;
		if (parent->left == max_node)
			parent->left = max_node->right;
		else
			parent->right = max_node->right;
		current = max_node;
	}
	delete current;
	this->nr_elements--;
	return true;
}


bool SortedBag::search(TComp e) const {
	BSTNode* current = this->root;
	bool found = false;

	while (current != nullptr && !found) {
		if (current->info == e) 
			found = true;
		else {
			if (this->r(current->info, e))
				current = current->right;
			else
				current = current->left;
		}
	}
	return found;
}


int SortedBag::nrOccurrences(TComp e) const {
	BSTNode* current = this->root;
	int count = 0;

	while (current != nullptr) {
		if (current->info == e) 
			count++;
		if (current->left != nullptr && current->left->info == e)
			current = current->left;
		else {
			if (this->r(current->info, e))
				current = current->right;
			else
				current = current->left;
		}
	}
	return count;
}


int SortedBag::size() const {
	return this->nr_elements;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator{ *this };
}


bool SortedBag::isEmpty() const {
	return this->root == nullptr;
}


SortedBag::~SortedBag() {
	this->removeSubtree(this->root);
}


void SortedBag::removeSubtree(BSTNode* node) {
	if (node == nullptr)
		return;
	this->removeSubtree(node->left);
	this->removeSubtree(node->right);
	delete node;
}
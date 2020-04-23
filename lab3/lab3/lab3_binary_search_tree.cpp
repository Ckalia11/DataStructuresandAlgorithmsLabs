// Lab 03
// Chetan Kalia (20771400) 
// Amay Shah

#include <iostream>
#include "lab3_binary_search_tree.hpp"
#include <queue>


using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	root = NULL;
	size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	if (!root) {
		return;
	}
	std::queue<BinarySearchTree::TaskItem*> node_queue;
	node_queue.push(root);
	while (!node_queue.empty()) {
		BinarySearchTree::TaskItem* cur_node = node_queue.front();
		node_queue.pop();
		if (cur_node->left) {
			node_queue.push(cur_node->left);
		}
		if (cur_node->right) {
			node_queue.push(cur_node->right);
		}
		delete cur_node;
	}
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	if (!root) {
		return BinarySearchTree::TaskItem(-1, "N/A");
	}
	BinarySearchTree::TaskItem* cur_node = root;
	while (cur_node->right) {
		cur_node = cur_node->right;
	}
	return *cur_node;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if (!root) {
		return BinarySearchTree::TaskItem(-1, "N/A");
	}
	BinarySearchTree::TaskItem* cur_node = root;

	while (cur_node->left) {
		cur_node = cur_node->left;
	}
	return *cur_node;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {

	BinarySearchTree::TaskItem* cur_node = root;
	if (!cur_node) {
		return 0;
	}
	queue<BinarySearchTree::TaskItem* > q;
	q.push(cur_node);
	unsigned int height = 0; // start at 0
	while (true) {
		int cnt = q.size();
		if (cnt == 0) {
			if (height == 0) return 0;
			return height - 1;
		}
		height++;
		while (cnt > 0) {
			BinarySearchTree::TaskItem* node = q.front();
			q.pop();
			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
			cnt--;
		}
	}
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	if (!root) {
		return;
	}
	std::queue<BinarySearchTree::TaskItem*> nq;
	nq.push(root);
	while (!nq.empty()) {
		BinarySearchTree::TaskItem* cur_node = nq.front();
		nq.pop();
		if (cur_node->left) {
			nq.push(cur_node->left);
		}
		if (cur_node->right) {
			nq.push(cur_node->right);
		}
	}
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists(BinarySearchTree::TaskItem val) const {
	if (!root) {
		return false;
	}
	BinarySearchTree::TaskItem* cur_node = root;
	while (cur_node) {
		if (val.priority > cur_node->priority) {
			if (cur_node->right) {
				cur_node = cur_node->right;
			}
			else {
				return false;
			}
		}
		else if (val.priority < cur_node->priority) {
			if (cur_node->left) {
				cur_node = cur_node->left;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
	return NULL;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
	return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth(BinarySearchTree::TaskItem* n) const {
	return 0;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert(BinarySearchTree::TaskItem val) {

	if (!root) {
		root = new TaskItem(val);
		++size;
		return true;
	}

	TaskItem* cur_node = root;
	TaskItem* temp = NULL;

	while (cur_node) {
		if (val.priority == cur_node->priority)
			return false;
		temp = cur_node;
		if (val.priority < cur_node->priority)
			cur_node = cur_node->left;
		else
			cur_node = cur_node->right;
	}
	cur_node = new TaskItem(val);
	cur_node->left = NULL;
	cur_node->right = NULL;

	if (cur_node->priority > temp->priority)
		temp->right = cur_node;
	else
		temp->left = cur_node;

	++size;
	return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove(BinarySearchTree::TaskItem val) {
	if (!root)
		return false;

	TaskItem* cur_node = root;
	TaskItem* temp = NULL;

	while (cur_node) {
		if (val.priority == cur_node->priority) {
			TaskItem* temp1 = cur_node->right;
			TaskItem* temp2 = cur_node;
			if (temp1) {
				while (temp1->left) {
					temp2 = temp1;
					temp1 = temp1->left;
				}
				temp1->left = cur_node->left;
				if (temp2->left && temp1->priority == temp2->left->priority)
					temp2->left = NULL;
				else
					temp2->right = NULL;
			}
			else
				temp1 = cur_node->left;
			if (temp)
				if (cur_node == temp->left)
					temp->left = temp1;
				else
					temp->right = temp1;
			else
				root = temp1;
			if (cur_node->right && temp1 != cur_node->right) {
				while (temp1->right)
					temp1 = temp1->right;
				temp1->right = cur_node->right;
			}
			delete cur_node;
			--size;
			return true;
		}
		temp = cur_node;
		if (val.priority < cur_node->priority)
			cur_node = cur_node->left;
		else
			cur_node = cur_node->right;
	}
	return false;
}
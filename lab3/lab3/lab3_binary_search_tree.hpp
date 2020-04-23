#ifndef LAB3_BINARY_SEARCH_TREE_HPP
#define LAB3_BINARY_SEARCH_TREE_HPP

#include <string>

using namespace std;

// PURPOSE: Models a Binary Search Tree of Task Items
class BinarySearchTree {
protected:
	// PURPOSE: Models a single Task Item as a Tree Node
	struct TaskItem {
		int priority; // normal values are greater than zero
		string description; // task description
		TaskItem(int new_priority, string new_desc) :
			priority(new_priority), description(new_desc), left(NULL), right(NULL) {}
		TaskItem* left;    // pointer to the left node
		TaskItem* right;   // pointer to the right node
		bool operator==(const TaskItem& rhs) {
			bool are_equal = priority == rhs.priority;
			return are_equal && description == rhs.description;
		}
	};

	friend class BinarySearchTreeTest;

	// pointer to the root node of the tree	
	TaskItem* root;

	// number of nodes in the tree
	unsigned int size;

public:
	// CONSTRUCTOR AND DESTRUCTOR

	// PURPOSE: Default/empty constructor
	BinarySearchTree();

	// PURPOSE: Explicit destructor of the class BinarySearchTree
	~BinarySearchTree();

	// ACCESSORS  
	// PURPOSE: Returns the number of nodes in the tree
	unsigned int get_size() const;

	// PURPOSE: Returns the maximum value of a node in the tree
	// if the tree is empty, it returns (-1, "N/A")
	TaskItem max() const;

	// PURPOSE: Returns the minimum value of a node in the tree
	// if the tree is empty, it returns (-1, "N/A")
	TaskItem min() const;

	// PURPOSE: Returns the tree height
	unsigned int height() const;

	// PURPOSE: Prints the contents of the tree; format not specified
	void print() const;

	// PURPOSE: Returns true if a node with the value val exists in the tree	
	// otherwise, returns false
	bool exists(TaskItem val) const;

	// PURPOSE: Optional helper function that returns a pointer to the root node
	TaskItem* get_root_node();

	// PURPOSE: Optional helper function that returns the root node pointer address
	TaskItem** get_root_node_address();

	// PURPOSE: Optional helper function that gets the maximum depth for a given node
	int get_node_depth(TaskItem* n) const;

	// MUTATORS

	// PURPOSE: Inserts the value val into the tree if it is unique
	// returns true if successful; returns false if val already exists
	bool insert(TaskItem val);

	// PURPOSE: Removes the node with the value val from the tree
	// returns true if successful; returns false otherwise
	bool remove(TaskItem val);
};
#endif
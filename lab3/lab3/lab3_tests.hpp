#ifndef LAB3_TESTS_HPP
#define LAB3_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include <algorithm>
#include <sstream>
#include <queue>

#include "lab3_priority_queue.hpp"
#include "lab3_binary_search_tree.hpp"

class PriorityQueueTest {
public:
	// PURPOSE: Tests if the new queue is valid
	bool test1() {
		PriorityQueue q(5);
		ASSERT_TRUE(q.empty());
		ASSERT_TRUE(!q.full());
		ASSERT_TRUE(q.get_size() == 0);
		return true;
	}

	// PURPOSE: Tests enqueue of one item and then dequeue of that item
	bool test2() {
		PriorityQueue q(2);
		ASSERT_TRUE(q.enqueue(PriorityQueue::TaskItem(35, "Test2")));
		ASSERT_TRUE(q.get_size() == 1);
		ASSERT_TRUE(!q.empty());
		ASSERT_TRUE(q.dequeue());
		ASSERT_TRUE(q.get_size() == 0);
		ASSERT_TRUE(q.empty());
		ASSERT_FALSE(q.full());
		return true;
	}

	// PURPOSE: Tests enqueue too many
	bool test3() {
		PriorityQueue q(3);
		ASSERT_TRUE(q.enqueue(PriorityQueue::TaskItem(15, "Test")));
		ASSERT_TRUE(q.enqueue(PriorityQueue::TaskItem(8, "Test")));
		ASSERT_TRUE(q.max().priority == 15);
		ASSERT_FALSE(q.full());
		ASSERT_TRUE(q.enqueue(PriorityQueue::TaskItem(20, "Test")));
		ASSERT_TRUE(q.max().priority == 20);
		ASSERT_TRUE(q.full());
		ASSERT_TRUE(!q.enqueue(PriorityQueue::TaskItem(7, "Test")));
		return true;
	}

	// PURPOSE: Tests enqueue too many then dequeue too many
	bool test4() {
		PriorityQueue q(3);
		ASSERT_TRUE(q.enqueue(PriorityQueue::TaskItem(5, "Test Task")));
		ASSERT_TRUE(q.max().priority == 5);
		ASSERT_TRUE(q.enqueue(PriorityQueue::TaskItem(3, "Test Task")));
		ASSERT_TRUE(q.enqueue(PriorityQueue::TaskItem(4, "Test Task")));
		ASSERT_TRUE(q.max().priority == 5);
		ASSERT_FALSE(!q.full());
		ASSERT_TRUE(!q.enqueue(PriorityQueue::TaskItem(7, "Test Task")));
		ASSERT_TRUE(q.full());
		ASSERT_TRUE(q.dequeue());
		ASSERT_TRUE(q.max().priority == 4);
		ASSERT_TRUE(q.dequeue());
		ASSERT_TRUE(q.max().priority == 3);
		ASSERT_TRUE(q.dequeue());
		ASSERT_TRUE(q.empty());
		ASSERT_TRUE(!q.full());
		ASSERT_TRUE(!q.dequeue());
		return true;
	}
};

class BinarySearchTreeTest {
public:
	bool insert_nodes(BinarySearchTree& tree, int* in, int nin) {
		for (int i = 0; i < nin; i++) {
			ASSERT_TRUE(tree.insert(BinarySearchTree::TaskItem(in[i], "Test")));
		}
		return true;
	}

	// PURPOSE: Traverse the tree using breadth-first traversal
	// Output is as follows: "val1 val2 ... valN"
	std::string level_order(BinarySearchTree::TaskItem* root) {
		if (!root) {
			return "";
		}

		std::stringstream ss;
		std::queue<BinarySearchTree::TaskItem*> node_queue;
		node_queue.push(root);
		while (!node_queue.empty()) {
			BinarySearchTree::TaskItem* cur_node = node_queue.front();
			node_queue.pop();
			ss << cur_node->priority << " ";
			if (cur_node->left) {
				node_queue.push(cur_node->left);
			}
			if (cur_node->right) {
				node_queue.push(cur_node->right);
			}
		}

		std::string level_order_str = ss.str();

		return level_order_str.substr(0, level_order_str.size() - 1);
	}

	// PURPOSE: Tests if the new tree is valid
	bool test1() {
		std::string expected_tree_level_order = "";
		BinarySearchTree bst;
		ASSERT_TRUE(bst.root == NULL);
		ASSERT_TRUE(bst.size == 0 && bst.get_size() == 0);
		// compare the tree's representation to the expected tree
		std::string tree_level_order = level_order(bst.root);
		ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
		return true;
	}

	// PURPOSE: Tests a tree with one node
	bool test2() {
		std::string expected_tree_level_order = "15";
		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(15, "Test")));
		ASSERT_TRUE(!bst.remove(BinarySearchTree::TaskItem(2, "Test")));
		ASSERT_TRUE(bst.exists(BinarySearchTree::TaskItem(15, "Test")));
		ASSERT_TRUE(bst.max() == bst.min() && bst.max() == BinarySearchTree::TaskItem(15, "Test"));
		ASSERT_TRUE(bst.get_size() == 1);
		std::string tree_level_order = level_order(bst.root);
		ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
		return true;
	}

	// PURPOSE: Tests insert, remove, and size on linear list formation with three elements
	bool test3() {
		std::string expected_tree_level_order = "15 2";
		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(15, "Test")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(2, "Test")));
		ASSERT_TRUE(bst.get_size() == 2);
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(20, "Test")));
		ASSERT_TRUE(bst.get_size() == 3);
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(20, "Test")));
		ASSERT_TRUE(bst.get_size() == 2);
		std::string tree_level_order = level_order(bst.root);
		ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
		return true;
	}

	// PURPOSE: Tests removal of a node with one child
	bool test4() {
		std::string expected_tree = "5 1 6";
		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(5, "Test Task")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(7, "Test Task")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(6, "Test Task")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(1, "Test Task")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(7, "Test Task")));
		ASSERT_TRUE(!bst.exists(BinarySearchTree::TaskItem(7, "Test Task")));
		ASSERT_TRUE(level_order(bst.root).compare(expected_tree) == 0)
			return true;
	}

	// PURPOSE: Tests insert of multiple elements and remove till nothing remains
	bool test5() {
		std::string expected_tree = "";
		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(8, "Test")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(3, "Test")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(10, "Test")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(15, "Test")));
		ASSERT_TRUE(!bst.remove(BinarySearchTree::TaskItem(9, "Test")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(8, "Test")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(15, "Test")));
		ASSERT_TRUE(bst.min() == BinarySearchTree::TaskItem(3, "Test"));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(10, "Test")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(3, "Test")));
		ASSERT_TRUE(bst.root == NULL);
		ASSERT_TRUE(level_order(bst.root).compare(expected_tree) == 0)
			return true;
	}

	// PURPOSE: Tests removal of root node when both children of root have two children
	bool test6() {
		std::string expected_tree1 = "6 3 10 1 9 15";
		std::string expected_tree2 = "9 3 10 1 6 15";
		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(8, "Test")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(3, "Test")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(10, "Test")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(1, "Test")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(6, "Test")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(9, "Test")));
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(15, "Test")));
		ASSERT_TRUE(!bst.remove(BinarySearchTree::TaskItem(12, "Test")));
		ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(8, "Test")));
		ASSERT_TRUE(level_order(bst.root).compare(expected_tree1) == 0 ||
			level_order(bst.root).compare(expected_tree2) == 0)
			return true;
	}

	// PURPOSE: Tests depth with many inserts and some removes
	bool test7() {
		std::string expected_tree = "5 0 15 3 6 1 4";
		BinarySearchTree bst;
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(5, "Test")));
		ASSERT_TRUE(bst.height() == 0)
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(15, "Test")));
		ASSERT_TRUE(bst.height() == 1)
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(0, "Test")));
		ASSERT_TRUE(bst.height() == 1)
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(3, "Test")));
		ASSERT_TRUE(bst.height() == 2);
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(1, "Test")));
		ASSERT_TRUE(bst.height() == 3);
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(4, "Test")));
		ASSERT_TRUE(bst.height() == 3);
		ASSERT_TRUE(bst.insert(BinarySearchTree::TaskItem(6, "Test")));
		ASSERT_TRUE(bst.height() == 3);
		ASSERT_TRUE(level_order(bst.root).compare(expected_tree) == 0)
			return true;
	}

	// PURPOSE: Tests lots of inserts and removes
	bool test8() {
		std::string expected_tree = "9 3 10 2 8 5 4 6 7";
		BinarySearchTree bst;
		int num[] = { 9, 3, 8, 5, 6, 4, 2, 10, 7 };
		int p = 9;
		ASSERT_TRUE(insert_nodes(bst, num, p));
		ASSERT_TRUE(level_order(bst.root).compare(expected_tree) == 0)
			for (int i = 0; i < p; ++i) {
				ASSERT_TRUE(bst.remove(BinarySearchTree::TaskItem(num[i], "Test")));
			}
		ASSERT_TRUE(!bst.remove(BinarySearchTree::TaskItem(num[0], "Test")));
		return true;
	}
};
#endif
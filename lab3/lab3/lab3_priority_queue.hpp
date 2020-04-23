#ifndef LAB3_PRIORITY_QUEUE_HPP
#define LAB3_PRIORITY_QUEUE_HPP
#include <string>
using namespace std;

// PURPOSE: Models a Priority Queue of Task Items
class PriorityQueue {
protected:
	// PURPOSE: Models a single Task Item
	struct TaskItem {
		int priority; // normal values are greater than zero
		string description; // task description
		TaskItem(int new_priority, string new_desc) :
			priority(new_priority), description(new_desc) {}
		bool operator==(const TaskItem& rhs) {
			bool are_equal = priority == rhs.priority;
			return are_equal && description == rhs.description;
		}
	};

	friend class PriorityQueueTest;

	// sequential representation of the priority queue.
	TaskItem** heap;

	// total number of elements that the priority queue can store
	unsigned int capacity;

	// current number of elements in the priority queue
	unsigned int size;

public:
	// CONSTRUCTOR AND DESTRUCTOR

	// PURPOSE: Parametric constructor 
	// initializes heap to an array of (n_capacity + 1) elements
	PriorityQueue(unsigned int n_capacity);

	// PURPOSE: Explicit destructor of the class PriorityQueue
	~PriorityQueue();

	// ACCESSORS

	// PURPOSE: Returns the number of elements in the priority queue
	unsigned int get_size() const;

	// PURPOSE: Returns true if the priority queue is empty; false, otherwise
	bool empty() const;

	// PURPOSE: Returns true if the priority queue is full; false, otherwise
	bool full() const;

	// PURPOSE: Prints the contents of the priority queue; format not specified
	void print() const;

	// PURPOSE: Returns the max element of the priority queue without removing it
	// if the priority queue is empty, it returns (-1, "N/A")
	TaskItem max() const;

	// MUTATORS

	// PURPOSE: Inserts the given value into the priority queue
	// re-arranges the elements back into a heap
	// returns true if successful and false otherwise
	// priority queue does not change in capacity
	bool enqueue(TaskItem val);

	// PURPOSE: Removes the top element with the maximum priority
	// re-arranges the remaining elements back into a heap
	// returns true if successful and false otherwise
	// priority queue does not change in capacity
	bool dequeue();
};
#endif 
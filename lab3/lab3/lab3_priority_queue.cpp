// Lab 03
// Chetan Kalia (20771400)
// Amay Shah

#include <iostream>
#include "lab3_priority_queue.hpp"

using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
    heap = new TaskItem * [n_capacity + 1];
    size = 0;
    capacity = n_capacity;
    
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
    delete[] heap;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
    return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
    return size < 1;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
    return size == capacity;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
    for (int i = 0; i < size; i++) {
        cout << heap[i]->priority;
        cout << heap[i]->description << endl;
    }
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
    if (empty()) {
        return TaskItem(-1, "N/A");
    }
    return *heap[size - 1];
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue(TaskItem val) {
    TaskItem* temp = new TaskItem(val.priority, val.description);
    
    if (full()) {
        return false;
    }
    if (empty()) {
        heap[0] = temp;
    }
    else if (max().priority <= temp->priority) {
        heap[size] = temp;
    }
    else {
        TaskItem* temp1 = nullptr;
        TaskItem* temp2 = nullptr;
        for (int i = 0; i < size; i++) {
            if (temp->priority < heap[i]->priority && temp1 == nullptr) {
                temp1 = heap[i];
                heap[i] = temp;
            }
            if (temp1 != nullptr) {
                temp2 = heap[i + 1];
                heap[i + 1] = temp1;
                temp1 = temp2;
            }
        }
    }
    size++;
    return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
    if (empty()) {
        return false;
    }
    delete heap[size - 1];
    heap[size - 1] = nullptr;
    size--;
    return true;
}
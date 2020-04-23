#include <iostream>
#include <string>
#include "lab3_tests.hpp"

using namespace std;

// PURPOSE: Returns the test result
string get_status_str(bool status) {
    return status ? "TEST PASSED" : "TEST FAILED";
}

int main() {
    PriorityQueueTest pqueue_test;
    BinarySearchTreeTest bst_test;

    string pqueue_test_descriptions[4] = {
      "Test1: New queue is valid",
      "Test2: Enqueue one item and then dequeue it",
      "Test3: Enqueue too many",
      "Test4: Enqueue too many then dequeue too many"
    };

    bool pqueue_test_results[4];
    pqueue_test_results[0] = pqueue_test.test1();
    pqueue_test_results[1] = pqueue_test.test2();
    pqueue_test_results[2] = pqueue_test.test3();
    pqueue_test_results[3] = pqueue_test.test4();

    cout << "PRIORITY QUEUE TESTING RESULTS \n";
    cout << "****************************** \n";
    for (int i = 0; i < 4; ++i) {
        cout << pqueue_test_descriptions[i] << endl << get_status_str(pqueue_test_results[i]) << endl;
    }
    cout << endl;

    string bst_test_descriptions[8] = {
      "Test1: New tree is valid",
      "Test2: Test a tree with one node",
      "Test3: Insert, remove, and size on linear list formation with three elements",
      "Test4: Test removal of a node with one child",
      "Test5: Insert multiple elements and remove till nothing remains",
      "Test6: Test removal of root node when both children of root have two children",
      "Test7: Test depth with many inserts and some removes",
      "Test8: Lots of inserts and removes"
    };
    bool bst_test_results[8];
    bst_test_results[0] = bst_test.test1();
    bst_test_results[1] = bst_test.test2();
    bst_test_results[2] = bst_test.test3();
    bst_test_results[3] = bst_test.test4();
    bst_test_results[4] = bst_test.test5();
    bst_test_results[5] = bst_test.test6();
    bst_test_results[6] = bst_test.test7();
    bst_test_results[7] = bst_test.test8();

    cout << "BINARY SEARCH TREE TESTING RESULTS \n";
    cout << "********************************** \n";
    for (int i = 0; i < 8; ++i) {
        cout << bst_test_descriptions[i] << endl << get_status_str(bst_test_results[i]) << endl;
    }
    cout << endl;
} 
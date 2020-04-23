// Chetan Kalia (20771400)

#include <iostream>

using namespace std;

void find_and_print_sum_of_nodes(BinarySearchTree* T, int desired_sum, int cur_sum, string buffer) {
    
    if (!T) return;

    int new_sum = cur_sum + T->value;

    string new_buffer = buffer + " " + int2ascii(T->value);

    if (new_sum == desired_sum) {
        cout << new_buffer << endl;
    }

    find_and_print_sum_of_nodes(T->left, desired_sum, cur_sum, buffer);
    find_and_print_sum_of_nodes(T->left, desired_sum, 0, "");
    find_and_print_sum_of_nodes(T->right, desired_sum, cur_sum, buffer);
    find_and_print_sum_of_nodes(T->right, desired_sum, 0, "");
}
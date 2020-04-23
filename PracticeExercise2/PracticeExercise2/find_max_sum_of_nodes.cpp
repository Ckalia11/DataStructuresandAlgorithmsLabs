#include <iostream>
#include <climits>

using namespace std;

int find_max_sum_of_nodes(BinaryTreeNode* T, int& temp_max_sum) {
    
    if (!T) return 0;
    int left_sum = find_max_sum_of_nodes(T->left, temp_max_sum);
    int right_sum = find_max_sum_of_nodes(T->right, temp_max_sum);
    int max1;
    int max2;
    if (T->value > left_sum + T->value && T->value > right_sum + T->value) {
        max1 = T->value;
    }
    else if (left_sum + T->value < right_sum + T->value) {
        max1 = right_sum + T->value;
    }
    else {
        max1 = left_sum + T->value;
    }
    if (left_sum + right_sum + T->value < max1) {
        max2 = max1;
    }
    else {
        max2 = left_sum + right_sum + T->value;
    }
    if (max1 > max2) {
        temp_max_sum = max1;
    }
    else {
        temp_max_sum = max2;
    }
    return max1;
}

int find_max_sum_of_nodes(BinaryTreeNode* T) {
    int temp_max_sum = INT_MIN;

    find_max_sum_of_nodes(T, temp_max_sum);

    return temp_max_sum;
}
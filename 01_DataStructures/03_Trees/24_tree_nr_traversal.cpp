/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdlib.h>
#include <iostream>
#include <stack>

using namespace std;

#define MAX_NUM_STACK_ELEMS (10)
#define MAX_VALUE   (10)
#define MAX_NUM_NODES_IN_TREE (10)

void handle_error(void)
{
    cout << "Test failed\n";
    exit(1);
}

int nr_result_array[MAX_NUM_NODES_IN_TREE];
int nr_index;


struct node
{
    int data;

    struct node *left;
    struct node *right;

    struct node *parent;
};


/*
Include the header file for printing the tree. The header file should be included
only after defining struct node
*/
#include "print_tree.h"



struct node * construct_bst (struct node *parent, int values[], int low, int high)
{
    int middle;

    struct node *new_node;

    if (low > high)
        return NULL;

    middle = (low + high) / 2;

    new_node = (struct node*) calloc(1, sizeof(struct node));
    if (!new_node)
        return NULL;

    /*Construct the new node using the middle value*/
    new_node->data = values[middle];
    new_node->parent = parent;

    /*Construct the left sub-tree using values[low] to values[middle-1]*/
    new_node->left = construct_bst(new_node, values, low, middle - 1);

    /*Construct the right sub-tree using values[middle+1] to values[high]*/
    new_node->right = construct_bst(new_node, values, middle + 1, high);

    return new_node;

}

void destroy_tree(struct node *cur_node) 
{
    if (!cur_node)
        return;

    destroy_tree(cur_node->left);
    destroy_tree(cur_node->right);

    free(cur_node);
}

void process(struct node *cur_node)
{
    nr_result_array[nr_index++] = cur_node->data;
    cout << cur_node->data << " ";
}


/*
root: root node of the binary tree
s: stack for storing the nodes for in-order traversal
*/
void non_recursive_in_order(struct node *root, stack<struct node*>& s)
{
    struct node *cur_node;

    cur_node = root;
    while (cur_node || !s.empty()) {

        if (cur_node) {
            /*push the current node onto stack*/
            s.push(cur_node);

            /*Traverse to the left sub-tree*/
            cur_node = cur_node->left;

        } else {
            /*remove the node from top of stack and process it*/
            cur_node = s.top();
            s.pop();

            /*process or print the node in-order*/
            process(cur_node);

            /*Traverse to the right sub-tree*/
            cur_node = cur_node->right;
        }
    }
}




void recursive_in_order(struct node *node)
{
    if (!node)
        return;

    recursive_in_order(node->left);

    if (nr_result_array[nr_index] != node->data)
        handle_error();

    ++nr_index;

    recursive_in_order(node->right);

}

void test_01()
{
    struct node *root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];
    stack<struct node*> s;

    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {
        /*Construct the tree*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);

        cout << "Printing tree:\n";
        print_tree(root, num_elems);

        /*Perform the non-recursive in-order traversal. Store the node data
        in nr_result_array*/
        nr_index = 0;
        cout << "Non Recursive In-order : ";
        non_recursive_in_order(root, s);

        /*Verify the non-recursive in-order result stored in nr_result_array
        by comparing it with the recursive in-order traversal*/
        nr_index = 0;
        recursive_in_order(root);

        destroy_tree(root);

        cout << "\n__________________________________________________\n";

    }

    cout << "Test passed\n";

    return ;
}



int main()
{
    test_01();

    return 0;
}

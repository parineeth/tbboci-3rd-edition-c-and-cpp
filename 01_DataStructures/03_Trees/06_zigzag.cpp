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

#define MAX_NUM_NODES_IN_TREE (10)

#define MAX_NODE_VALUE (10)


struct node
{
    int data;

    int depth;

    struct node *left;
    struct node *right;

    struct node *parent;

};

/*
Include the header file for printing the tree. The header file should be included
only after defining struct node
*/
#include "print_tree.h"




/*Recursively Construct a Binary Search Tree from the input array sorted in ascending order*/
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

    if (parent)
        new_node->depth = parent->depth + 1;
    else
        new_node->depth = 0;

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



void print_data(int data)
{
    cout << data << " ";
}

void handle_error()
{
    cout << "Test failed\n";
    exit(1);
}

int max(int a, int b)
{
    return ((a > b) ? a: b);
}



/* Helper function for printing in zig zag order
print_stack: stack used for printing the nodes
store_stack: stack that stores the children of nodes in print_stack
left_to_right: if set to 1, left child is stored first followed by right child
*/
void process_stacks(stack<struct node*>& print_stack, 
        stack<struct node*>& store_stack, int left_to_right)
{
    struct node * cur_node;

    while (!print_stack.empty()) {

        cur_node = print_stack.top();
        print_stack.pop();
        print_data( cur_node->data);

        if (left_to_right) {
            if (cur_node->left)
                store_stack.push(cur_node->left);
            if (cur_node->right)
                store_stack.push(cur_node->right);
        } else {
            if (cur_node->right)
                store_stack.push(cur_node->right);
            if (cur_node->left)
                store_stack.push(cur_node->left);
        }
    }
}

/*root: root of the binary tree to be printed spirally
s0, s1: stacks used for storing nodes of the binary tree
*/
void print_zig_zag(struct node *root, stack<struct node*>& s0, 
        stack<struct node*>& s1)
{
    if (!root)
        return;

    /*Push root into stack s0 and start processing*/
    s0.push(root);

    while (!s0.empty()) {
        /*s0 is used for printing. The children of nodes in s0 are
        stored in s1 in left to right direction*/
        process_stacks(s0, s1, 1);
        cout << endl;

        /*s1 is used for printing. The children of nodes in s1 are
        stored in s0 in right to left direction*/
        process_stacks(s1, s0, 0);
        cout << endl;
    }
}







void test_01()
{
    struct node *root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];
    stack<struct node*> s1, s2;


    /*number_array contains data in ascending order from 0*/
    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*Construct the tree based on the data stored in the number array*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);

        cout << "Printing tree:\n";
        print_tree(root, num_elems);

        cout << "Zig Zag order is:\n";
        print_zig_zag(root, s1, s2);

        destroy_tree(root);

        cout << "___________________________________________________\n";

    }

}


int main()
{

    test_01();

    printf("Test passed\n");

    return 0;
}

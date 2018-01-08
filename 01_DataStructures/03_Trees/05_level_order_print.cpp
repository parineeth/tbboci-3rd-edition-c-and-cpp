/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdlib.h>
#include <iostream>
#include <queue>

using namespace std;

#define MAX_NUM_NODES_IN_TREE (10)


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




void handle_error(void)
{
    cout << "Test failed\n";
    exit(1);
}






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




/*
root: root node of the tree 
q: queue that helps in printing in level order
*/
void print_level_order(struct node *root, queue<struct node*>& q)
{
    struct node *n;
    int num_nodes_in_cur_level, num_nodes_in_next_level;

    if (!root)
        return;

    /*Add the root node to the empty queue*/
    q.push(root);
    num_nodes_in_cur_level = 1;
    num_nodes_in_next_level = 0;

    /*Process the nodes in the queue in Breadth First manner*/
    while (!q.empty()) {

        /*Remove the node at the head of the queue*/
        n = q.front();
        q.pop();

        print_data(n->data); /*print the data in the node*/

        /*Add the left child to the end of the queue*/
        if (n->left) {
            q.push(n->left);
            num_nodes_in_next_level++;
        }

        /*Add the right child to the end of the queue*/
        if (n->right) {
            q.push(n->right);
            num_nodes_in_next_level++;
        }

        num_nodes_in_cur_level--;

        /*go to next line, if all nodes in current level are processed*/
        if (num_nodes_in_cur_level == 0) {
            cout << endl;
            num_nodes_in_cur_level = num_nodes_in_next_level;
            num_nodes_in_next_level = 0;
        }
    }
}



int main()
{
    struct node *root;
    queue<struct node*> q;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];

    /*number_array contains data in ascending order from 0*/
    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*Construct the tree based on the data stored in the number array*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);
    
        cout << "Printing tree\n";
        print_tree(root, num_elems);

        cout << "Level order is:\n";
        print_level_order(root, q);

        destroy_tree(root);

        cout << ("__________________________________________________________\n");

    }

    cout << "Test passed\n";
    return 0;
}

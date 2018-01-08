/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_NODES_IN_TREE (10)


struct node
{
    int data;

    int depth;

    struct node *left;
    struct node *right;

    struct node *parent;

    struct node *next;

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



void handle_error()
{
    printf("Test failed\n");
    exit(1);
}

void swap_children(struct node *cur_node)
{
    struct node *temp;

    if (!cur_node)
        return;

    temp = cur_node->left;
    cur_node->left = cur_node->right;
    cur_node->right = temp;

    swap_children(cur_node->left);
    swap_children(cur_node->right);

}



/*cur_node: current node whose left and right sub-trees need to be checked
prev_node_pp: the in-order predecessor of cur_node
Return value: 1 if the tree is a binary search tree, 0 otherwise
*/
int is_bst(struct node *cur_node, struct node ** prev_node_pp)
{
    if (!cur_node)
        return 1;

    /*Check if the left sub-tree is a BST*/
    if (!is_bst(cur_node->left, prev_node_pp)) 
        return 0;

    /*If data in cur_node is <= to previous node then it is not a BST*/
    if (*prev_node_pp && cur_node->data <= (*prev_node_pp)->data)
        return 0;

    /*Update previous node to current node*/
    *prev_node_pp = cur_node;

    /*Check if the right sub-tree is a BST*/
    return is_bst(cur_node->right, prev_node_pp); 
}

void print_result(int result)
{
    if (result) 
        printf("The tree is a Binary Search Tree\n\n\n"); 
    else {
        printf("The tree is NOT a Binary Search Tree\n\n");
    }
}



int main()
{
    struct node *root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];
    struct node *prev_node;
    int result;

    /*number_array contains data in ascending order from 0 to MAX_NUM_NODES_IN_TREE*/
    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*Construct the tree based on the data stored in the number array*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Printing tree\n");
        print_tree(root, num_elems);

        /*Verify if the tree is binary search tree. Verification should pass*/
        prev_node = NULL;
        result = is_bst(root, &prev_node);
        print_result(result);
        if (!result)
            handle_error();

        /*Swap the left and right child of the root*/
        swap_children(root);

        printf("Printing tree:\n");
        print_tree(root, num_elems);

        /*Verify if the tree is binary search tree. Verification should fail if num_elems > 1
        since we have swapped the left and right child of the root*/
        prev_node = NULL;
        result = is_bst(root, &prev_node);
        print_result(result);
        if (result && num_elems > 1)
            handle_error();

        destroy_tree(root);

        printf("_____________________________________________________\n");

    }



    printf("Test passed\n");

    return 0;
}


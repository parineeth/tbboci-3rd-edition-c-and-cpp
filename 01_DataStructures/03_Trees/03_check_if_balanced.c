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


struct node * construct_unbalanced_tree(int num_nodes)
{
    struct node *new_node, *prev_node, *root;
    int i;

    root = prev_node = NULL;
    for (i = 0; i < num_nodes; ++i) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->data = i;

        if (!root)
            root = new_node;

        if (prev_node) {
            prev_node->right = new_node;
        }
        prev_node = new_node;
    }
    
    return root;
}


void print_unbalanced_tree(struct node *root)
{
    struct node *cur_node;
    int count, i;
    
    cur_node = root;
    count = 0;
    while (cur_node) {
        for (i = 0; i < count; ++i) {
            printf("\t");
        }
        
        printf("%d\n", cur_node->data);

        ++count;
        cur_node = cur_node->right;
    }

}


void handle_error()
{
    printf("Test failed\n");
    exit(1);
}

int max(int a, int b)
{
    return (a > b ? a : b);
}


/*cur_node: cur node of the binary tree being checked
height: height of the current node is returned here
Return value: 1 if the tree is balanced, 0 otherwise
*/
int is_balanced(struct node *cur_node, int *height)
{
    int is_left_balanced, is_right_balanced;
    int left_height, right_height;

    if (!cur_node) {
        *height = 0;
        return 1;
    }

    is_left_balanced = is_balanced(cur_node->left, &left_height);
    is_right_balanced = is_balanced(cur_node->right, &right_height);

    if (!is_left_balanced || !is_right_balanced)
        return 0;

    /*If the difference between height of left subtree and height of
    right subtree is more than 1, then the tree is unbalanced*/
    if (abs(left_height - right_height) > 1)
        return 0;

    /*To get the height of the current node, we find the maximum of the  
    left subtree height and the right subtree height and add 1 to it*/
    *height = max(left_height, right_height) + 1;

    return 1;   
}

void print_result(int result)
{
    if (result) 
        printf("The tree is balanced\n\n\n"); 
    else {
        printf("The tree is NOT balanced\n\n");
    }
}



int main()
{
    struct node *root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];
    int result, height;

    /*number_array contains data in ascending order from 0 to MAX_NUM_NODES_IN_TREE*/
    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in a balanced tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*Construct a balanced tree based on the data stored in the number array*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Printing tree\n");
        print_tree(root, num_elems);

        result = is_balanced(root, &height);

        print_result(result);

        if (result != 1)
            handle_error();

        destroy_tree(root);

        printf("_____________________________________________________\n");

    }

    /*Test for different number of nodes in a unbalanced tree*/
    for (num_elems = 3; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*Construct an unbalanced tree */
        root = construct_unbalanced_tree(num_elems);

        print_unbalanced_tree(root);

        result = is_balanced(root, &height);

        print_result(result);

        if (result != 0)
            handle_error();

        destroy_tree(root);

        printf("_____________________________________________________\n");
    }


    printf("Test passed\n");

    return 0;
}


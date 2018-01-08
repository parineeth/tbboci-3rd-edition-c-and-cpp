/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_NODES_IN_TREE (10)

#define MAX_NODE_VALUE (10)


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

int max(int a, int b)
{
    return ((a > b) ? a: b);
}


/*
cur_node: current node of the binary tree 
height: height of current node is returned here. Leaf node has a height of 1
diameter: the diameter of the tree is returned here
*/
void find_diameter(struct node *cur_node, int *height, int *diameter)
{
    int left_height, right_height;
    int longest_path;

    if (!cur_node) {
        *height = 0;
        return;
    }

    /*Find the height of the left sub-tree*/
    find_diameter(cur_node->left, &left_height, diameter);

    /*Find the height of the right sub-tree*/
    find_diameter(cur_node->right, &right_height, diameter);

    /*Calculate height of cur_node*/
    *height = 1 + max(left_height, right_height);

    /*Calculate longest path between any two leafs passing through cur_node*/
    longest_path = left_height + right_height + 1;

    /*If the length of longest path through cur_node is greater than 
    the current diameter, then assign it to the diameter*/
    if (longest_path > *diameter)
        *diameter = longest_path;
}





void test()
{
    struct node *root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];
    int height, diameter;

    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of elements in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*Construct the tree from the array*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Printing tree:\n");
        print_tree(root, num_elems);

        /*Find the diameter*/
        height = diameter = 0;
        find_diameter(root, &height, &diameter);

        printf("Height = %d, Diameter = %d\n", height, diameter);

        destroy_tree(root);

        printf("___________________________________________________\n");

    }

}


int main()
{
    test();

    printf("Test passed \n");

    return 0;
}

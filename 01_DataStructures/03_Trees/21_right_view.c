/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


#define MAX_NUM_NODES_IN_TREE (10)

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}



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


void print_data(int data)
{
    printf("%d ", data);
}

struct node * construct_bst (struct node *parent, int values[], int low, int high)
{
    int middle;

    struct node *new_node;

    if (low > high) {
        return NULL;
    }

    middle = (low + high) / 2;

    new_node = (struct node*) calloc(1, sizeof(struct node));

    new_node->data = values[middle];

    new_node->parent = parent;

    new_node->left = construct_bst(new_node, values, low, middle - 1);

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

/*cur_node: current node in the tree being processed
cur_level: the depth of the current node. Root node of tree has a level of 0
max_level: Maximum level seen in the tree so far. We pass -1 for the root node
*/
void print_right_view(struct node *cur_node, int cur_level, int *max_level) {
    if (!cur_node)
        return;

    /*If the current node is the first node we have observed in current level,
    then print it*/
    if (*max_level < cur_level) {
        print_data(cur_node->data);
        *max_level = cur_level;
    }   

    /*First expand the right child and then the left child*/    
    print_right_view(cur_node->right, cur_level + 1, max_level);
    print_right_view(cur_node->left, cur_level + 1, max_level);
}


int main()
{
    struct node *root1;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];
    int max_level;

    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*construct the tree using the number_array*/
        root1 = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Printing tree:\n");
        print_tree(root1, num_elems);

        /*Print the right view nodes*/
        max_level = -1;
        printf("The right view nodes are : ");
        print_right_view(root1, 0, &max_level);

        destroy_tree(root1);

        printf("\n__________________________________________\n");

    }


    printf("Test passed\n");

    return 0;
}

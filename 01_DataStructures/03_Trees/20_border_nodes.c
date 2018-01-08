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

/*Print the left border nodes of the tree*/
void print_left_border(struct node *cur_node)
{
    /*Keep traversing left and print the non-leaf nodes*/
    while (cur_node) {
        /*If node has a left or right child, then it is a non-leaf node*/
        if (cur_node->left || cur_node->right)
            print_data( cur_node->data);

        cur_node = cur_node->left;
    }
}

/*Print the leaf nodes of the tree*/
void print_leaf_nodes(struct node *cur_node)
{
    if (!cur_node)
        return;

    if (!cur_node->left && !cur_node->right)
        print_data(cur_node->data);

    print_leaf_nodes(cur_node->left);
    print_leaf_nodes(cur_node->right);
}

/* Print the right border nodes of the tree*/
void print_right_border(struct node *cur_node)
{
    if (!cur_node)
        return;

    /*First reach the deepest right node and then start printing bottom-up*/
    print_right_border(cur_node->right);

    /*If the node has a left or right child, then it is a non-leaf node. 
    So print it*/
    if (cur_node->left || cur_node->right)
        print_data(cur_node->data);

}


/*Main function that prints the border nodes of a binary tree*/
void print_border_nodes(struct node *root)
{
    if (!root)
        return;

    print_left_border(root);
    print_leaf_nodes(root);
    print_right_border(root);
}



int main()
{
    struct node *root1;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];

    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*construct the tree using the number_array*/
        root1 = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Printing tree:\n");
        print_tree(root1, num_elems);

        /*Print the border nodes*/
        printf("The border nodes are : ");
        print_border_nodes(root1);

        destroy_tree(root1);

        printf("\n__________________________________________\n");

    }


    printf("Test passed\n");

    return 0;
}

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

void print_array(int array[], int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


void traverse_pre_order(struct node *cur_node, int *in_array, int *pos_p)
{
    if (!cur_node)
        return;

    in_array[*pos_p] = cur_node->data;
    (*pos_p)++;

    traverse_pre_order(cur_node->left, in_array, pos_p);
    traverse_pre_order(cur_node->right, in_array, pos_p);
}


void traverse_in_order(struct node *cur_node, int *in_array, int *pos_p)
{
    if (!cur_node)
        return;

    traverse_in_order(cur_node->left, in_array, pos_p);

    in_array[*pos_p] = cur_node->data;
    (*pos_p)++;


    traverse_in_order(cur_node->right, in_array, pos_p);
}




/*
pre_order: array containing the data of nodes of the binary tree in pre-order
in_order: array containing the data of nodes of the binary tree in in-order
in_start: starting index of current region in the in_order array 
in_end: ending index of current region in the in_order array 
pre_pos: index in the pre-order array
Return value: newly created binary tree node
*/
struct node* construct_tree(int * pre_order, int * in_order, int in_start, 
            int in_end, int *pre_pos)
{
    struct node *new_node;
    int in_location;
    int pivot;

    /*Termination condition for recursion*/
    if (in_start > in_end)
        return NULL;

    /* Assign the pivot from pre-order array*/
    pivot = pre_order[*pre_pos];

    /*Find pivot in in-order array*/
    for (in_location = in_start; in_location <= in_end; ++in_location) {
        if (in_order[in_location] == pivot) {
            break;
        }
    }

    /*Create the new node and assign the pivot data*/
    new_node = (struct node*) calloc(1, sizeof(struct node));
    new_node->data = pivot;

    /*Advance to the next member in the pre-order array*/
    (*pre_pos)++;

    /*First recursively construct the left sub-tree */
    new_node->left = construct_tree(pre_order, in_order, in_start, 
                        in_location - 1, pre_pos);

    /*Recursively construct the right sub-tree*/
    new_node->right = construct_tree(pre_order, in_order, in_location + 1, 
                        in_end, pre_pos);

    return new_node;
}



void verify_trees(struct node *n1, struct node *n2)
{
    if (!n1 && !n2)
        return;

    if ( (!n1 && n2) || (n1 && !n2))
        handle_error();


    if (n1->data != n2->data)
        handle_error();


    verify_trees(n1->left, n2->left);

    verify_trees(n1->right, n2->right);
}

void test_01()
{
    struct node *root, *assembled_root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];
    int pos;
    int pre_order[MAX_NUM_NODES_IN_TREE], in_order[MAX_NUM_NODES_IN_TREE];
    int in_start, in_end, pre_pos;

    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of elements in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*Construct the original tree*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);

        /*Traverse the original tree in pre-order and store the result in array pre_order*/
        pos = 0;
        traverse_pre_order(root, pre_order, &pos);

        printf("Pre-order is : ");
        print_array(pre_order, num_elems);

        /*Traverse the original tree in in-order and store the result in array in_order*/
        pos = 0;
        traverse_in_order(root, in_order, &pos);

        printf("In-order is : ");
        print_array(in_order, num_elems);

        /*Re-construct the tree using the pre_order and in_order arrays*/
        in_start = 0;
        in_end = num_elems - 1;
        pre_pos = 0;
        assembled_root = construct_tree(pre_order, in_order, in_start, in_end, &pre_pos);

        printf("Printing tree:\n");
        print_tree(root, num_elems);

        /*Verify if the original tree and reconstructed tree match*/
        verify_trees(root, assembled_root);

        destroy_tree(root);
        destroy_tree(assembled_root);

        printf("___________________________________________________________________\n");

    }

}


int main()
{

    test_01();

    printf("Test passed\n");

    return 0;
}

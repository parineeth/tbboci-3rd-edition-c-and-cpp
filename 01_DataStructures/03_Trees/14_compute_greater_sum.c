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

    int sum;

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


void print_data(int data)
{
    printf("%d ", data);
}

void handle_error()
{
    printf("Error occured while comparing tree and sum array\n");
    exit(1);
}




/*
cur_node: current node of the binary search tree 
sum_p: sum of nodes greater than current node is returned here
*/
void compute_sum_of_greater_nodes(struct node *cur_node, int *sum_p)
{
    if (!cur_node)
        return;

    /*Since greater elements are in the right sub-tree, first process the
    right sub-tree*/
    compute_sum_of_greater_nodes(cur_node->right, sum_p);

    /*Assign the sum of the greater nodes*/
    cur_node->sum = *sum_p;

    /*Add the current nodes data to the sum*/
    *sum_p += cur_node->data;

    /*Process the left sub-tree*/
    compute_sum_of_greater_nodes(cur_node->left, sum_p);
}



void verify_sum (struct node *cur_node, int *sum_array, int* index_p)
{
    if (!cur_node)
        return;

    verify_sum(cur_node->left, sum_array, index_p);

    printf("Node data = %d, Greater sum =%d\n", cur_node->data, cur_node->sum);

    if (sum_array[*index_p] != cur_node->sum)
        handle_error();

    (*index_p)++;

    verify_sum(cur_node->right, sum_array, index_p);
}


int main()
{
    struct node *root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE], sum_array[MAX_NUM_NODES_IN_TREE];
    int bst_sum, sum_so_far, index;

    /*number_array contains numbers from 0 in ascending order*/
    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
        sum_array[i] = 0;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*construct the tree using the number_array*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Printing tree:\n");
        print_tree(root, num_elems);

        /*For each node, compute the sum of greater nodes and store in the node itself */
        bst_sum = 0;
        compute_sum_of_greater_nodes(root, &bst_sum);

        /*Compute the greater sum of the number array and store it in sum_array*/
        sum_so_far = 0;
        for (i = num_elems - 1; i >= 0; --i) {
            sum_array[i] = sum_so_far;
            sum_so_far += number_array[i] ;
        }

        /*Verify the greater sum stored in the nodes of the tree with the sum_array*/
        index = 0;
        verify_sum(root, sum_array, &index);

        destroy_tree(root);

        printf("___________________________________________________\n");

    }



    printf("Test passed \n");

    return 0;
}

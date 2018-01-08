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


/* n is a pointer to root of the binary search tree
Returns - The maximum element of the binary search tree
*/
struct node* get_max(struct node *n)
{
    if (!n)
        return NULL;

    /*The rightmost node has the maximum value*/
    while (n->right)
        n = n->right;

    return n;
}

/*x is a node in the binary search tree
Returns - the node previous to x
*/
struct node* get_previous(struct node *x)
{
    struct node *y;

    /*Handle Case - 1*/
    if (x->left) {
        return get_max(x->left);
    }

    /*Handle Case - 2*/
    y = x->parent;
    while (y && y->left == x) {
        x = y;
        y = y->parent;
    }

    return y;
}


/*
root: the root node of the binary search tree 
k: indicates the kth largest value. k >= 1
Return value: kth largest node in the binary search tree
*/
struct node* find_kth_largest(struct node *root, int k)
{
    struct node *n;
    int i;

    if (!root || k < 1)
        return NULL;

    /*Find the node with the maximum value*/
    n = root;
    while (n->right)
        n = n->right;

    /*Find the k-1 previous nodes */
    for (i = 1; i < k; ++i) {
        n = get_previous(n);
        if (!n) {
            return NULL;
        }
    }

    return n;
}





int main()
{
    struct node *root1, *cur_node;
    int i, k, num_elems, number_array[MAX_NUM_NODES_IN_TREE];

    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*construct the Binary Search Tree*/
        root1 = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Printing tree:\n");
        print_tree(root1, num_elems);

        /*Find the kth largest. k can take values from 1 to num_elems*/
        for (k = 1; k <= num_elems; ++k) {
            cur_node = find_kth_largest(root1, k);

            printf("K = %d, Kth Largest = %d\n", k, cur_node->data);

            /*Verify the result returned*/
            if (cur_node->data != num_elems - k )
                handle_error();
        }

        /*If we pass k value that is > than num_elems, we should get NULL*/
        cur_node = find_kth_largest(root1, num_elems + 1);
        if (cur_node != NULL)
            handle_error();

        destroy_tree(root1);

        printf("_________________________________________________________\n");
    }


    printf("Test passed \n");

    return 0;
}

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


/* n: root of the binary search tree
Returns - The maximum node of the binary search tree
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



/*
x: node in the binary search tree
Return value: the node previous to node x
*/
struct node* get_previous(struct node *x)
{
    struct node *y;

    /*Handle Case-1, left child exists*/
    if (x->left) {
        y = x->left;
        while (y->right) {
            y = y->right;
        }
        return y;
    }

    /*Handle Case-2, left child doesn't exist*/
    y = x->parent;
    while (y && y->left == x) {
        x = y;
        y = y->parent;
    }

    return y;
}





/*
x: node in the binary search tree
Return value: the node after node x
*/
struct node* get_next(struct node *x)
{
    struct node *y;

    /*Handle Case-1: right child exists*/
    if (x->right) {
        y = x->right;
        while (y->left) {
            y = y->left;
        }
        return y;
    }

    /*Handle Case-2: right child doesn't exist*/
    y = x->parent;
    while (y && y->right == x) {
        x = y;
        y = y->parent;
    }

    return y;
}

void print_node (struct node *n)
{
    if (n)
        printf("%d", n->data);
    else
        printf("NULL");
}

/*Verify the previous and next functions*/
void verify_previous_next(struct node *cur_node, int num_elems)
{
    struct node *prev_node, *next_node;

    if (!cur_node)
        return;

    /*Get the previous and next node for the current node*/
    prev_node = get_previous(cur_node);
    next_node = get_next(cur_node);

    printf("Cur node = ");
    print_node(cur_node);

    printf(": Prev node = ");
    print_node(prev_node);

    printf(", Next node = ");
    print_node(next_node);
    printf("\n");

    if (cur_node->data == 0) {
        /*If cur_node has data = 0, it is the first node
        The previous node should be NULL*/
        if (prev_node != NULL)
            handle_error();
    } else {
        /*cur_node->data should be prev_node->data + 1*/
        if (prev_node->data + 1 != cur_node->data)
            handle_error();
    }

    if (cur_node->data == num_elems - 1) {
        /*If cur_node has data = num_elems - 1, it is the last node
        The next node should be NULL*/
        if (next_node != NULL)
            handle_error();
    } else {
        /*next_node->data should be cur_node->data + 1 */
        if (cur_node->data + 1 != next_node->data)
            handle_error();
    }

    verify_previous_next(cur_node->left, num_elems);
    verify_previous_next(cur_node->right, num_elems);
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

        /*construct the Binary Search Tree*/
        root1 = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Printing tree:\n");
        print_tree(root1, num_elems);

        /*verify the get_previous and get_next functions*/
        verify_previous_next(root1, num_elems);

        destroy_tree(root1);

        printf("____________________________________________________\n");

    }


    printf("Test passed\n");

    return 0;
}

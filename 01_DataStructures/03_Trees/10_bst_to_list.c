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


void destroy_list(struct node* head) 
{
    struct node* cur_node = head, *temp_node;

    while (cur_node != NULL) {
        temp_node = cur_node;
        cur_node = cur_node->right;
        free(temp_node);
    }
}




/*
cur_node: the current BST node being processed
prev_node_pp: node that is previous to the current node in linked list
list_head_pp: head of the result linked list
Returns: 0 on success
*/
int bst_to_list(struct node *cur_node, struct node **prev_node_pp, 
        struct node **list_head_pp)
{
    if (!cur_node)
        return 0;

    /*In-Order Traversal of the BST*/

    /*Convert the left sub-tree of node to linked list*/
    bst_to_list(cur_node->left, prev_node_pp, list_head_pp);

    /*Link the previous node and the current node*/
    cur_node->left = *prev_node_pp;

    if (*prev_node_pp) {
        (*prev_node_pp)->right = cur_node;
    } else {
        /*Since previous node is NULL, this is the first node of the list
        So make head point to it*/
        *list_head_pp = cur_node;
    }

    /*Make the current node the previous node*/
    *prev_node_pp = cur_node;

    /*Convert the right sub-tree of node to linked list*/
    bst_to_list(cur_node->right, prev_node_pp, list_head_pp);

    return 0; /*return success*/
}




void verify_list(struct node *head)
{
    struct node *iter_node, *prev_node, *last_node = NULL;

    if (!head)
        return;

    /*Traverse the doubly linked list from left to right*/
    prev_node = head;
    iter_node = head->right;
    last_node = head;
    while (iter_node) {
        /*The data should be arranged in increasing order*/
        if (prev_node->data >= iter_node->data) {
            handle_error();
        }

        /*Find the last node in the doubly linked list*/
        if (!iter_node->right)
            last_node = iter_node;

        prev_node = iter_node;
        iter_node = iter_node->right;
    }

    /*Traverse the doubly linked list from right to left*/
    prev_node = last_node;
    iter_node = last_node->left;
    while (iter_node) {

        /*The data should be arranged in decreasing order*/
        if (prev_node->data <= iter_node->data) {
            handle_error();
        }

        prev_node = iter_node;
        iter_node = iter_node->left;
    }
}

static void print_list(struct node* head) 
{
    struct node* cur_node = head;

    while (cur_node != NULL) {
        printf("%d ", cur_node->data);
        cur_node = cur_node->right;
    }
    printf("\n\n");
}


int main()
{
    struct node *root, *head, *prev;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];

    /*number_array contains data in ascending order from 0*/
    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*construct the Binary Search Tree*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Printing tree:\n");
        print_tree(root, num_elems);

        /*Convert the Binary Search Tree to Doubly Linked List*/
        prev = NULL;
        head = NULL;
        bst_to_list(root, &prev, &head);

        printf("Printing the Doubly Linked List:\n");
        print_list(head);

        /*Verify the Doubly Linked List*/
        verify_list(head);

        destroy_list(head);

        printf("___________________________________________________\n");

    }

    printf("Test passed \n");

    return 0;
}

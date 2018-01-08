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

/*
list_node_pp: node for traversing the doubly linked list
start: index of node in linked list at the beginning of region being operated on
end: index of node in linked list at the end of region being operated on
Returns: root of the binary search tree
*/
struct node * list_to_bst (struct node **list_node_pp, int start, int end)
{
    int middle;

    struct node *middle_node, *left_child;

    if (start > end)
        return NULL;

    middle = (start + end) / 2;

    /*Recursively construct the left subtree using the nodes before the 
    middle node and get the root of the left sub-tree*/
    left_child = list_to_bst(list_node_pp, start, middle - 1);

    /*list_node_pp will now be pointing to the middle node*/
    middle_node = *list_node_pp;

    /*Connect the left sub-tree to the middle node*/
    middle_node->left = left_child;

    /*Advance to the next node after the middle node*/
    *list_node_pp = (*list_node_pp)->right;

    /*Recursively construct the right subtree using the nodes after the 
    middle node and connect the root of right subtree to middle node*/
    middle_node->right = list_to_bst(list_node_pp, middle + 1, end);

    return middle_node;
}


void destroy_tree(struct node *cur_node) 
{
    if (!cur_node)
        return;

    destroy_tree(cur_node->left);
    destroy_tree(cur_node->right);

    free(cur_node);
}


/*cur_node: pointer to node whose left and right sub-trees need to be checked
prev_node_pp: pointer to the pointer of the node that is the in-order predecessor of cur_node
Return value: 1 if the tree is a binary search tree, 0 otherwise
*/
int is_bst(struct node *cur_node, struct node ** prev_node_pp)
{
    if (!cur_node)
        return 1;

    if (!is_bst(cur_node->left, prev_node_pp)) /*Check if the left sub-tree is a BST*/
        return 0;

    /*If data in cur_node is less than or equal to previous node then it is not a BST*/
    if (*prev_node_pp && cur_node->data <= (*prev_node_pp)->data)
        return 0;

    /*Update previous node to current node*/
    *prev_node_pp = cur_node;

    return is_bst(cur_node->right, prev_node_pp); /*Check if the right sub-tree is a BST*/
}

void print_result(int result)
{
    if (result) 
        printf("The tree is a Binary Search Tree\n"); 
    else 
        printf("The tree is NOT a Binary Search Tree\n");

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
    struct node *root, *new_node, *iter_node, *prev, *head;
    int i, num_elems, result;

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {
        
        /*Construct a doubly linked list*/
        head = prev = NULL;
        for (i = 0; i < num_elems; ++i) {
            new_node = (struct node*) calloc(1, sizeof(struct node *));
            new_node->right = NULL;
            new_node->left = prev;
            new_node->data = i;

            if (prev)
                prev->right = new_node;
    
            if (i == 0)
                head = new_node;

            prev = new_node;
        }

        printf("Printing the Doubly Linked List:\n");
        print_list(head);

        /*Convert the doubly linked list to a Binary Search Tree*/
        iter_node = head;
        root = list_to_bst(&iter_node, 0, num_elems - 1);

        printf("Printing tree:\n");
        print_tree(root, num_elems);

        /*Verify if the tree formed is a Binary Search Tree*/
        prev = NULL;
        result = is_bst(root, &prev);
        print_result(result);
        if (!result)
            handle_error();

        destroy_tree(root);

        printf("_____________________________________________________________\n");

    }

    printf("Test passed \n");

    return 0;
}

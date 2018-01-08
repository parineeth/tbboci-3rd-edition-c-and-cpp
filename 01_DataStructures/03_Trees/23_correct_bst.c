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



void handle_error()
{
    printf("Error occured\n");
    exit(1);
}




/*Helper function for finding the error nodes in a Binary Search Tree
cur_node: current tree node 
prev_node_pp: node that is the in-order predecessor of cur_node
error1_pp, error2_pp: the two error nodes are returned here
*/
void find_error_nodes(struct node *cur_node, struct node ** prev_node_pp, 
            struct node **error1_pp, struct node **error2_pp)
{
    if (!cur_node)
        return;

    /*Check for error node in the left sub-tree*/
    find_error_nodes(cur_node->left, prev_node_pp, error1_pp, error2_pp); 

    /*cur_node should be greater than previous node. So if data in cur_node  
     is less than or equal to previous node then we have found an error */
    if (*prev_node_pp && cur_node->data <= (*prev_node_pp)->data) {
        if (*error1_pp == NULL) {
            *error1_pp = *prev_node_pp;
            *error2_pp = cur_node; 
        } else {
            *error2_pp = cur_node;
            return;
        }
    }  

    /*Update previous node to current node*/
    *prev_node_pp = cur_node;

    /*Check for error node in the right sub-tree*/
    find_error_nodes(cur_node->right, prev_node_pp, error1_pp, error2_pp); 
}

/*Main function for correcting the Binary Search Tree
root: root node of the Binary Search Tree in which two nodes have been swapped
*/
void correct_bst(struct node *root) 
{
    struct node *error1, *error2, *prev_node;
    int temp_data;

    error1 = error2 = prev_node = NULL; 
    
    /*Find the two error nodes*/
    find_error_nodes(root, &prev_node, &error1, &error2);

    /*If we found two error nodes, then swap their data*/
    if (error1 != NULL && error2 != NULL) {
        temp_data = error1->data;
        error1->data = error2->data;
        error2->data = temp_data;
    }
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





int main()
{
    struct node *root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];
    struct node *prev_node;
    int index1, index2, temp;

    /*Test for different number of nodes in the tree*/
    for (num_elems = 2; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*Construct a sorted array*/
        for (i = 0; i < num_elems; ++i) {
            number_array[i] = i;
        }

        /*Choose two random indexes*/
        index1 = rand() % num_elems;
        index2 = rand() % num_elems;

        printf("Num elements = %d, Swapping node at %d with node at %d \n\n",
            num_elems, index1, index2);  

        /*Swap two locations in the sorted array*/
        temp = number_array[index1];
        number_array[index1] = number_array[index2];
        number_array[index2] = temp;

        /*Construct the Incorrect Binary Search Tree based on the number_array
        Since two locations in the number_array are incorrect, two nodes in the 
        Binary Search Tree will be incorrect.*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Printing the Incorrect tree: \n");      
        print_tree(root, num_elems);

        /*Correct the Binary Search Tree*/
        correct_bst(root);

        printf("Printing the Corrected tree: \n");      
        print_tree(root, num_elems);

        /*Verify if the Binary Search Tree is proper*/
        prev_node = NULL;
        if (!is_bst(root, &prev_node) )
            handle_error();



        printf("______________________________________________________\n");

    }



    printf("Test passed\n");

    return 0;
}


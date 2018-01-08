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
Inlcude the header file for printing the tree. The header file should be included
only after defining struct node
*/
#include "print_tree.h"

/*Recursively Construct a Binary Search Tree from the input array sorted in ascending order*/
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



/*
cur_node: current node of the tree whose mirror image should be computed
*/
void compute_mirror_image(struct node *cur_node) {
    struct node *temp_node;
    
    if (cur_node) {
        /*Swap the left child and right child of the current node*/
        temp_node = cur_node->left;
        cur_node->left = cur_node->right;
        cur_node->right = temp_node;

        /*Recursively compute the mirror image */
        compute_mirror_image(cur_node->left);
        compute_mirror_image(cur_node->right);
    }
}







int compare_nodes ( struct node *n1, struct node *n2) {
    if (!n1 && !n2)  /*If both the nodes are NULL */
        return 1;  /* return symmetric*/
    
    if ( (n1 && !n2) || (!n1 && n2)) /*If one node is NULL and other is not*/
        return 0; /*return not symmetric*/
    
    if (n1->data != n2->data) /*If data of two nodes don't match */
        return 0; /* return not symmetric */
        
    if (!compare_nodes (n1->left, n2->right)) 
        return 0;
    
    if (!compare_nodes (n1->right, n2->left)) 
        return 0;
    
    return 1; /*Return symmetric*/
}

/*Returns 1 if the tree is symmetric, 0 otherwise*/
int is_symmetric(struct node * root) {
    if (!root)
        return 1;
    
    return compare_nodes(root->left, root->right);
}






int main()
{
    struct node *root1, *root2;
    struct node main_root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];

    /*number_array contains data in ascending order from 0 to MAX_NUM_NODES_IN_TREE*/
    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*Construct the tree based on the data stored in the number array*/
        root1 = construct_bst(NULL, number_array, 0, num_elems - 1);

        /*Construct an identical tree and store root in root2*/
        root2 = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Original tree: \n");
        print_tree(root1, num_elems);

        /*Compute the mirror image*/
        compute_mirror_image(root2);

        printf("Mirror image: \n");
        print_tree(root2, num_elems);

        /*Root1 and Root2 have trees that are mirror images of each other.
        So if we now have a main_root whose left child is root1 and right child is root2
        then main_root should be symmetric*/
        main_root.left = root1;
        main_root.right = root2;

        if (!is_symmetric(&main_root))
            handle_error();

        destroy_tree(root1);
        destroy_tree(root2);

        printf("_____________________________________________________________\n");      

    }


    printf("Test passed \n");

    return 0;
}

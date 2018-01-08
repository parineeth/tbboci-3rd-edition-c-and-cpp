/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_NODES_IN_TREE (10)
#define INVALID_VALUE (100)


struct node
{
    int data;

    int depth;

    struct node *left;
    struct node *right;
    struct node *parent;

};




struct node * construct_tree (struct node *parent, int values[], int low, int high)
{
    int middle;

    struct node *new_node;

    if (low > high)
        return NULL;

    middle = (low + high) / 2;

    new_node =(struct node*) calloc(1, sizeof(struct node));
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
    new_node->left = construct_tree(new_node, values, low, middle - 1);

    /*Construct the right sub-tree using values[middle+1] to values[high]*/
    new_node->right = construct_tree(new_node, values, middle + 1, high);

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
    printf("Error occured\n");
    exit(1);
}

/*Helper function that compares the nodes 
n1: node belonging to the main tree
n2: node belonging to sub-tree being searched
Return value: 1 if sub-tree of n1 matches sub-tree of n2. 0 otherwise
*/
int compare_nodes(struct node *n1, struct node *n2)
{
    if (n1 == NULL && n2 == NULL)
        return 1;

    if (!n1 || !n2)
        return 0;

    if (n1->data != n2->data)
        return 0;

    return (compare_nodes(n1->left, n2->left) 
        && compare_nodes(n1->right, n2->right));
}

/*Main function that checks if tree under root2 is a subtree of tree under root1
root1: main tree node
root2: root of the sub-tree being searched
Return value: 1 if tree under root2 is present in tree under root1, 0 otherwise
*/
int is_sub_tree(struct node *root1, struct node *root2)
{
    /*empty tree is treated as a sub-tree of the main tree*/
    if(root2 == NULL)
        return 1;

    if (!root1)
        return 0;

    if (compare_nodes(root1, root2))
        return 1;

    /*Check if sub-tree being searched is present in left sub-tree of root1 
    or in right sub-tree of root1*/
    return (is_sub_tree(root1->left, root2) 
        || is_sub_tree(root1->right, root2));
} 



int main()
{
    struct node *sub_tree_root, *main_tree_root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];

    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*Construct the sub_tree to be searched*/
        sub_tree_root = construct_tree(NULL, number_array, 0, num_elems - 1);

        /*Create the main tree node*/
        main_tree_root = (struct node*) calloc(1, sizeof (struct node));
        main_tree_root->data =  INVALID_VALUE;
        main_tree_root->left = NULL;
        main_tree_root->right = NULL;
        
        /*main tree root has an invalid value and won't match with any of the 
        sub-tree nodes. So checking for sub-tree should fail*/
        if (is_sub_tree(main_tree_root, sub_tree_root))
            handle_error();
        
        /*Connect the sub-tree root to the left of the main-tree. We should
        now find the sub-tree in the main tree*/
        main_tree_root->left = sub_tree_root; 
        main_tree_root->right = NULL;
        if (!is_sub_tree(main_tree_root, sub_tree_root))
            handle_error();

        /*Connect the sub-tree root to the right of the main-tree. We should
        now find the sub-tree in the main tree*/
        main_tree_root->left = NULL; 
        main_tree_root->right = sub_tree_root;
        if (!is_sub_tree(main_tree_root, sub_tree_root))
            handle_error();

        /*We should find the sub-tree in the sub-tree itself*/
        if (!is_sub_tree(sub_tree_root, sub_tree_root))
            handle_error();

        /*If sub-tree is NULL, then we should still treat it as a sub-tree of main tree*/
        if (!is_sub_tree(main_tree_root, NULL))
            handle_error();

        /*If main-tree is NULL, then we shouldn't find the sub-tree*/
        if (is_sub_tree(NULL, sub_tree_root))
            handle_error();

        free(main_tree_root);
        destroy_tree(sub_tree_root);

    }



    printf("Test passed\n");

    return 0;
}


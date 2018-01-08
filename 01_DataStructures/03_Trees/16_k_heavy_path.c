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



void handle_error()
{
    printf("Test failed\n");
    exit(1);
}

int max(int a, int b)
{
    return ((a > b) ? a: b);
}




/*
cur_node: current node of the binary tree 
above_sum: sum of the nodes from root to the parent of current node
k: the threshold path value for retaining the nodes
Return value: length of the longest path from root to leaf in which current 
        node is present
*/
int k_heavy_path(struct node *cur_node, int above_sum, int k)
{
    int max_left_path, max_right_path, longest_path;

    if (!cur_node)
        return above_sum;

    above_sum += cur_node->data;

    /*Find the longest path in left sub-tree that contains the current node*/
    max_left_path = k_heavy_path(cur_node->left, above_sum, k);

    /*If longest left sub-tree path is below threshold, prune left sub-tree*/
    if (max_left_path < k)
        cur_node->left = NULL;

    /*Find longest path in right sub-tree that contains current node*/
    max_right_path = k_heavy_path(cur_node->right, above_sum, k);

    /*If longest right sub-tree path is below threshold, prune right sub-tree*/
    if (max_right_path < k)
        cur_node->right = NULL;

    longest_path = max(max_left_path, max_right_path);

    /*If all paths through node are below k, then free the node*/
    if (longest_path < k) 
        free(cur_node); 
    
    return longest_path;
}


/*Verify if all paths from the root to any leaf has a path sum >= K*/
int verify_path(struct node *cur_node, int top_sum, int K)
{
    int max_left_path, max_right_path;

    if (!cur_node)
        return top_sum;

    top_sum += cur_node->data;

    max_left_path = verify_path(cur_node->left, top_sum, K);
    max_right_path = verify_path(cur_node->right, top_sum, K);

    /*Only paths whose path sum is >= K should be present in the tree*/
    if (max_left_path < K && max_right_path < K)
        handle_error();

    return max (max_left_path, max_right_path);
}





void test()
{
    struct node *root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];
    int K;

    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of elements in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*Construct the tree from the array*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Original tree:\n");
        print_tree(root, num_elems);

        K = 20;

        /*if k_heavy_path returns a value less than K, then there is no path from
        the root to any leaf whose path sum is >= K. So the root itself will get removed.
        In this case set the root to NULL*/
        if (k_heavy_path(root, 0, K) < K)
            root = NULL;

        printf("After retaining only K-Heavy paths (K = %d):\n", K);
        print_tree(root, num_elems);


        /*Verify if all paths from the root to any leaf has a path sum >= K*/
        verify_path(root, 0, K);

        destroy_tree(root);

        printf("___________________________________________________\n");

    }

}


int main()
{
    test();

    printf("Test passed \n");

    return 0;
}

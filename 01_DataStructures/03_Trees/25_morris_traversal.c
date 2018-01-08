/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE   (10)
#define MAX_NUM_NODES_IN_TREE (10)

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}

int morris_result_array[MAX_NUM_NODES_IN_TREE];
int morris_index;


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

void destroy_tree(struct node *cur_node) 
{
    if (!cur_node)
        return;

    destroy_tree(cur_node->left);
    destroy_tree(cur_node->right);

    free(cur_node);
}



void print_morris(struct node *cur_node)
{
    printf("%d ", cur_node->data);
    morris_result_array[morris_index] = cur_node->data;
    morris_index++;
}


/*
root: root node of the binary tree
*/
void morris_traversal(struct node *root)
{
    struct node *cur_node, *left_pre;

    cur_node = root;
    while (cur_node) {
        /*If cur_node has no left sub_tree, then print/process the cur_node
        then move over to cur_node->right and continue*/
        if (!cur_node->left) {
            print_morris(cur_node);
            cur_node = cur_node->right;
            continue;
        } 
        
        /*cur_node has a left sub-tree. First store the left predecessor
        of cur_node in left_pre. Left predecessor can be found by 
        traversing to the left of current node and then repeatedly going 
        to the right till we hit a leaf node
        */
        left_pre = cur_node->left;
        while (left_pre->right != NULL && left_pre->right != cur_node)
            left_pre = left_pre->right;

        if (left_pre->right == NULL) {
            /*If left predecessor points to NULL, it means we have not   
            yet traversed the left sub-tree of current node. So create   
            a thread from left_pre->right to current node to remember 
            that on reaching left_pre the next in-order node is current
            node. Then proceed to cur_node->left
            */
            left_pre->right = cur_node;
            cur_node = cur_node->left;
        } else {
            /*If left predecessor does not point to NULL, then it means 
            that we have finished traversing the left sub-tree of 
            cur_node. So remove the thread from left_pre->right to 
            cur_node. The current node is the in-order node to be 
            processed. So process it and then move to right sub-tree 
            of cur_node
            */
            left_pre->right = NULL;
            print_morris(cur_node);
            cur_node = cur_node->right;
        }
    }
}




void recursive_in_order(struct node *node)
{
    if (!node)
        return;

    recursive_in_order(node->left);

    if (morris_result_array[morris_index] != node->data)
        handle_error();

    ++morris_index;

    recursive_in_order(node->right);

}

void test_01()
{
    struct node *root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];

    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*Construct the tree*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Printing tree:\n");
        print_tree(root, num_elems);

        /*Perform the morris in-order traversal. Store the node data
        in morris_result_array*/
        printf("Morris In-order : ");
        morris_index = 0;
        morris_traversal(root);

        /*Verify the morris in-order result stored in morris_result_array
        by comparing it with the recursive in-order traversal*/
        morris_index = 0;
        recursive_in_order(root);

        destroy_tree(root);

        printf("\n___________________________________________\n");

    }

    printf("Test passed\n");

    return ;
}



int main()
{
    test_01();

    return 0;
}



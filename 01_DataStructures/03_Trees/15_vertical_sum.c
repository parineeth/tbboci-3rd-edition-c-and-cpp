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

int max(int a, int b)
{
    return ((a > b) ? a: b);
}



/* Helper function to find the vertical sum
cur_node: current node being processed in the binary tree
col: column of the current node
sum_array: array containing the sum of nodes in each column
*/
void process_sum(struct node *cur_node, int col, int *sum_array)
{
    if (!cur_node)
        return;

    sum_array[col] += cur_node->data;

    /*column number of left child is col - 1*/
    process_sum(cur_node->left, col - 1, sum_array);

    /*column number of right child is col+1*/
    process_sum(cur_node->right, col +  1, sum_array);
}

/* Main function to find the vertical sum
root: root of the binary tree 
sum_array_pp: array which contains the vertical sum will be returned here
Return value: number of columns in the binary tree
*/
int compute_vertical_sum(struct node *root, int ** sum_array_pp)
{
    struct node *cur_node;
    int num_left_cols= 0, num_right_cols = 0, root_col, total_num_cols;
    
    *sum_array_pp = NULL;
    if (!root)
        return 0;


    /*Compute the number of left columns*/
    cur_node = root->left;
    while (cur_node) {
        ++num_left_cols;
        cur_node = cur_node->left;
    }

    /*Compute the number of right columns*/
    cur_node = root->right;
    while (cur_node) {
        ++num_right_cols;
        cur_node = cur_node->right;
    }

    total_num_cols = num_left_cols+ num_right_cols + 1;

    /*Dynamically create the array for storing the column sum*/
    *sum_array_pp = (int*) calloc(total_num_cols, sizeof(int));

    root_col = num_left_cols;

    /*Compute the vertical sum starting with the root*/
    process_sum(root, root_col, *sum_array_pp);

    return total_num_cols;
}







void test_01()
{
    struct node *root;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];
    int *sum_array, num_cols;


    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*construct the tree*/
        root = construct_bst(NULL, number_array, 0, num_elems - 1);

        /*Compute the vertical sum*/        
        num_cols = compute_vertical_sum(root, &sum_array);

        printf("Vertical sum is:");
        for (i = 0; i < num_cols; ++i) {
            printf("%d ", sum_array[i]);
        }

        destroy_tree(root);

        printf("\n___________________________________________________\n");

    }

}


int main()
{

    test_01();

    printf("Test passed\n");

    return 0;
}

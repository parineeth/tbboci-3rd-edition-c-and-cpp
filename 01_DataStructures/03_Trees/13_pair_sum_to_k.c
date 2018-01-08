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

void check_condition(int condition)
{
    if (!condition)
        handle_error();
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
        y = x->left;
        while (y->right) {
            y = y->right;
        }
        return y;
    }

    /*Handle Case - 2*/
    y = x->parent;
    while (y && y->left == x) {
        x = y;
        y = y->parent;
    }

    return y;
}


/*x is a node in the binary search tree
Returns - the node previous to x
*/
struct node* get_next(struct node *x)
{
    struct node *y;

    /*Handle Case - 1*/
    if (x->right) {
        y = x->right;
        while (y->left) {
            y = y->left;
        }
        return y;
    }

    /*Handle Case - 2*/
    y = x->parent;
    while (y && y->right == x) {
        x = y;
        y = y->parent;
    }

    return y;
}




/*
root: the root of the binary search tree
k: sum of two nodes should equal k
result1: first result node that sums to k is returned
result2: second result node that sums to k is returned
*/
void find_pair_sum_to_k(struct node *root, int k, struct node **result1, 
            struct node **result2)
{
    struct node *n1, *n2;

    *result1 = NULL;
    *result2 = NULL;

    if (!root)
        return;

    /*Store the leftmost node in n1*/
    n1 = root;
    while (n1->left)
        n1 = n1->left;
    
    /*Store the right most node in n2*/
    n2 = root;
    while (n2->right)
        n2 = n2->right;
    
    /*Process the tree by picking one node from left and one node from right*/
    while (n1 != n2) {
        int sum = n1->data + n2->data;

        /*check if the left node and right node sum to k*/
        if (sum == k) {
            *result1 = n1;
            *result2 = n2;
            break;
        }

        if (sum < k) {
            /*Pick the next higher value node from the left*/
            n1 = get_next(n1);
        } else {
            /*Pick the next smaller value from the right*/
            n2 = get_previous(n2);
        }
    }
}


/*val1 and val2 will contain the two value that sum to K in the number_array.
If there are no pair of values that sum to K, then val1 and val2 will contain -1*/
void find_array_sum_to_k(int number_array[], int num_elems, int K, int *val1, int *val2)
{
    int i, j;

    *val1 = -1;
    *val2 = -1;

    for (i = 0; i < num_elems - 1; ++i) {
        for (j = num_elems - 1; j > i; --j) {

            if (number_array[i] + number_array[j] == K) {
                *val1 = number_array[i];
                *val2 = number_array[j];
                return;
            }
        }
    }
}

int main()
{
    struct node *root1, *n1, *n2;
    int K;
    int num1, num2;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];

    /*number_array contains numbers from 0 in ascending order*/
    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    /*Test for different number of nodes in the tree*/
    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        /*construct the Binary Search Tree using the number_array*/
        root1 = construct_bst(NULL, number_array, 0, num_elems - 1);

        printf("Printing tree:\n");
        print_tree(root1, num_elems);

        /*Test for different values of K*/
        for (K = 0; K <= (2 * num_elems); ++K) {

            /*find the pair of nodes that sum to K in the tree*/
            find_pair_sum_to_k(root1, K, &n1, &n2);

            /*find the two numbers that add upto K in the number array*/
            find_array_sum_to_k(number_array, num_elems, K, &num1, &num2);

            /*The result from the tree and the array should match*/
            if (n1 == NULL || num1 == -1) {
                check_condition(n1 == NULL);
                check_condition(n2 == NULL);
                check_condition(num1 == -1);
                check_condition(num2 == -1);
            } else {

                check_condition(n1->data == num1);
                check_condition(n2->data == num2);

                printf("%d + %d = %d\n", n1->data, n2->data, K);

            }

        }

        destroy_tree(root1);

        printf("__________________________________________\n");

    }


    printf("Test passed\n");

    return 0;
}

/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE (100)
#define MAX_INT (1000000)

void handle_error()
{
    printf("Test failed \n");
    exit(1);
}





/*
n: total number of nodes in the binary search tree
Return value: Number of unique binary search trees that can be constructed with n nodes
*/
int find_num_unique_bst(int n)
{
    int *num_bst;
    int i, left_sub_tree_size, right_sub_tree_size;
    int result; 

    if (n <= 2)
        return n;

    num_bst = (int *) calloc(n+1, sizeof(int));

    num_bst[0] = 1; /*We are making this 1 to simplify the calculation*/
    num_bst[1] = 1;
    num_bst[2] = 2;

    for (i = 3; i <= n; ++i) {
        /*the left sub-tree size can vary from 0 to i-1 
        (one node has to be reserved for root)*/
        for (left_sub_tree_size = 0; left_sub_tree_size < i; 
                ++left_sub_tree_size) {
            /*Subtract the left subtree size and the root node to 
            get right subtree size*/
            right_sub_tree_size = i - 1 - left_sub_tree_size;

            num_bst[i] += num_bst[left_sub_tree_size] * 
                        num_bst[right_sub_tree_size];
        }
    }

    result = num_bst[n];
    free(num_bst);
    return result;
}





void test(int n, int expected_result)
{
    int result = find_num_unique_bst(n);

    printf("Number of unique BST with %d nodes = %d\n", n, result);

    if (result != expected_result)
        handle_error();
    
    printf("\n");  
}








int main()
{
    /*catalan numbers*/
    test(1, 1);
    test(2, 2);
    test(3, 5);
    test(4, 14);
    test(5, 42);
    test(6, 132);
    test(7, 429);

    printf("Test passed\n");
    return 0;
}

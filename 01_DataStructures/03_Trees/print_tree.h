/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>

#define MAX_NUM_COLS_ON_SCREEN (40)

/*Helper function for printing the binary tree
cur_node: current node being processed in pre-oder traversal
cur_depth: depth of the current node. Depth of root is 0
max_depth: maximum depth of the tree is returned here
print_array: The nodes of the binary tree are stored in this array. print_array[0] will contain the root.
    print_array[1] will store the left child of root. print_array[2] will store right child of root and so on
    In case, we get a NULL node while traversing the tree, we will still store it
pos: position of the current node in the print_array
*/
void fill_print_array(struct node *cur_node, int cur_depth, int *max_depth, struct node *print_array[], int pos)
{

    /*Store the node in the array (even if the node is NULL)*/
    print_array[pos] = cur_node;

    if (!cur_node)
        return;

    if (cur_depth > *max_depth)
        *max_depth = cur_depth;

    fill_print_array(cur_node->left, cur_depth + 1, max_depth, print_array, (2*pos) + 1);
    fill_print_array(cur_node->right, cur_depth + 1, max_depth, print_array, (2*pos) + 2);
        
}

/*
Main function for printing the tree
*/
void print_tree(struct node *root, int max_num_nodes_in_tree)
{
    struct node **print_array, *cur_node;
    int i, cur_depth, max_depth, num_nodes_in_this_level;
    int screen_pos, node_display_pos, start_display_pos, print_index, offset;
    int max_print_array_size;

    if (max_num_nodes_in_tree > 16) {
        printf("Oops, too many nodes in tree. Can't print the tree\n");
        return;
    }
 
    
    max_print_array_size = 1 << (max_num_nodes_in_tree + 2);
    print_array = (struct node**) calloc(max_print_array_size, sizeof(struct node*));


    /*Store the nodes of the tree in print_array. print_array[0] will hold the root.
    print_array[1] will hold root's left child. print_array[2] will hold root's right child
    print_array[3] to print[6] will hold the nodes at depth 2 and so on. 
    Even NULL nodes are stored in the array*/
    max_depth = -1;
    fill_print_array(root, 0, &max_depth, print_array, 0); 

    /*Our print function is limited by the number of columns on the screen. We can print
    properly on till a depth of 3*/
    if (max_depth > 3) {
        printf("Oops can't print the tree at depth more than 4 \n");
        return; 
    }

    /* If MAX_NUM_COLS_ON_SCREEN is 40,
    for depth 0, start_display_pos = 20, offset = 40: root is printed at column 20
    for depth 1, start_display_pos = 10, offset = 20: printing happens at column 10 and 30
    for depth 2, start_display_pos = 5,  offset = 10: printing happens at column 5, 15, 25 and 35
    */
    cur_depth = print_index = 0;
    start_display_pos = MAX_NUM_COLS_ON_SCREEN / 2;
    offset = MAX_NUM_COLS_ON_SCREEN;

    while (cur_depth <= max_depth) {
        num_nodes_in_this_level = (1 << cur_depth);
        screen_pos = 0;
        node_display_pos = start_display_pos;

        for (i = 0; i < num_nodes_in_this_level; ++i) {

            cur_node = print_array[print_index];

            /*We need to display current node at node_display_pos
            So print spaces on the screen till screen_pos reaches node_display_pos*/
            while (screen_pos < node_display_pos) {
                printf(" ");
                screen_pos++;
            }

            
            if (cur_node) {
                printf("%d", cur_node->data);
                screen_pos++;
            }

            node_display_pos += offset; /*Compute the position of the next node*/
            print_index++; /*Go to the next node in the print_array*/
        }

        /*We are going to nodes at next depth. So go to a new line*/
        printf("\n");

        cur_depth++;
        start_display_pos = start_display_pos / 2;
        offset = offset / 2;
    }

    printf("\n\n");
    
    free(print_array);

}


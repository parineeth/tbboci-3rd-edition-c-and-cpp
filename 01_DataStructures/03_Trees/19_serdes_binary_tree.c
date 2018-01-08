/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define SPECIAL_VALUE (-1)

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




/*cur_node: current node of the binary tree
fp: file where the binary tree should be stored
Return value: 0 on sucess 
*/
int serialize_tree(struct node *cur_node, FILE *fp) {
    /*If cur_node is NULL, then store the special value and return*/
    if (!cur_node) {
        fprintf(fp, "%d\n", SPECIAL_VALUE);
        return 0;
    }

    /*Traverse the nodes in pre-order*/
    /*First print the data of the node into the file*/
    fprintf(fp, "%d\n", cur_node->data);

    /*Traverse the left subtree*/
    serialize_tree(cur_node->left, fp);

    /*Traverse the right subtree*/
    serialize_tree(cur_node->right, fp);

    return 0;
}

/* fp: file where the data about binary tree was stored
Return value: the reconstructed node of the binary tree
*/
struct node *deserialize_tree(FILE *fp) {
    struct node *new_node;
    int value;

    fscanf(fp, "%d", &value);

    /*If the special value is read, then return NULL */
    if (value == SPECIAL_VALUE)
        return NULL;

    /*Traverse in pre-order*/
    /*Store the value read from the file in the new_node*/
    new_node = (struct node*) calloc(1, sizeof(struct node));
    new_node->data = value;
    
    new_node->left = deserialize_tree(fp); /*Construct the left subtree*/
    
    new_node->right = deserialize_tree(fp); /*Construct the right sub-tree*/
    
    return new_node;
}



int are_trees_identical(struct node *n1, struct node *n2)
{
    if (!n1 && !n2)
        return 1;

    if ( (n1 && !n2) || (!n1 && n2))
        return 0;

    if (n1->data != n2->data)
        return 0;

    if (!are_trees_identical(n1->left, n2->left))
        return 0;

    if (!are_trees_identical(n1->right, n2->right))
        return 0;

    return 1;
}








int main()
{
    struct node *root1, *root2;
    int i, num_elems, number_array[MAX_NUM_NODES_IN_TREE];
    FILE *fp;

    for (i = 0; i < MAX_NUM_NODES_IN_TREE; ++i) {
        number_array[i] = i;
    }

    for (num_elems = 1; num_elems <= MAX_NUM_NODES_IN_TREE; ++num_elems) {

        root1 = construct_bst(NULL, number_array, 0, num_elems - 1);

        if (num_elems == 10) {
            int x = 0;
            ++x;
        }

        fp = fopen("serial_tree.txt", "w");

        serialize_tree(root1, fp);

        fclose(fp);


        fp = fopen("serial_tree.txt", "r");

        root2 = deserialize_tree(fp);

        fclose(fp);

        if (!are_trees_identical(root1, root2))
            handle_error();

    }


    printf("Test passed \n");

    return 0;
}






/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


#define MAX_NUM_ELEMENTS_IN_LIST (10)

struct node
{
    int data;
    struct node *next;
};

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


/* 
n1: pointer to the node to be deleted
Return value: 0 on success, -1 on failure
*/
int delete_node(struct node *n1)
{
    struct node *n2;

    if (n1->next) {
        /*Get the pointer to the next node*/
        n2 = n1->next;

        /*Copy the contents of the next node into the current node*/
        n1->data = n2->data;
        n1->next = n2->next;

        /*Free the next node*/
        free(n2);

        /*Return indicating the operation is successful*/
        return 0;
    }

    /*return indicating the operation failed*/
    return -1;
}


struct node* construct_list(int num_elements)
{
    int i;
    struct node* head = NULL, *new_node;
    int value = num_elements;

    /*If num_elems = 1, the list will be 1
    If num_elems = 2, the list will be 1->2 
    */
    for (i = 0; i < num_elements; ++i) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->data = value;
        new_node->next = head;
        head = new_node;
        --value;
    }

    return head;
}

void destroy_list(struct node* head) 
{
    struct node* cur_node = head, *temp_node;

    while (cur_node != NULL) {
        temp_node = cur_node;
        cur_node = cur_node->next;
        free(temp_node);
    }
}

void print_list(struct node* head) 
{
    struct node* cur_node = head;

    while (cur_node != NULL) {
        printf("%d ", cur_node->data);
        cur_node = cur_node->next;
    }
    printf("\n");
}


int main()
{
    struct node *head, *cur_node;
    int num_elems, i, k, ret_val;

    /*We test for different list lengths */
    for (num_elems = 2; num_elems <= MAX_NUM_ELEMENTS_IN_LIST; ++num_elems) {

        /*Construct the list having num_elems. 
        If num_elems = 2, the list will be 1->2 */
        head = construct_list(num_elems);
        
        /*Choose a random position to delete. It should not be the last element*/
        k = rand() % (num_elems - 1);

        printf("Deleting %dth node \n", k);
        printf("Input  : ");
        print_list(head);

        /*Find the node at position k*/
        cur_node = head;
        for (i = 0; i < k; ++i) {
            cur_node = cur_node->next;
        }

        /*delete the node*/
        ret_val = delete_node(cur_node);

        printf("Output : ");
        print_list(head);

        /*Verify the result*/
        if (ret_val != 0)
            handle_error();

        destroy_list(head);

        printf("_____________________________________________\n");
    }

    printf("Test passed\n");

    return 0;
}

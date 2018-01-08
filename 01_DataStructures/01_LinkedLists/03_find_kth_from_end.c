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
head: first node of the linked list
k: node position from the end. k starts from 1 onwards
Return value: kth node from end if it exists, NULL otherwise
*/
struct node* find_kth_node_from_end(struct node *head, int k)
{
    struct node *n1;
    int i, length;

    length = 0;
    n1 = head;
    while (n1 != NULL) {
        length++;
        n1 = n1->next;
    }

    n1 = head;
    for (i = 1; i <= length; ++i) {
        if (i == length - k + 1) {
            return n1;  /*n1 is the kth node from end. So return it*/
        }
        n1 = n1->next;
    }

    /*k value passed doesn't match with the linked list. So return NULL */
    return NULL;
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

void print_list(struct node *head)
{
    struct node *cur_node = head;

    while (cur_node) {
        printf("%d ", cur_node->data);
        cur_node = cur_node->next;
    }
    printf("\n");
}

int main()
{
    struct node *head  ;
    struct node *k_node;
    int k, num_elems;

    /*We test for different list lengths ranging from 1 to MAX_NUM_ELEMENTS_IN_LIST*/
    for (num_elems = 1; num_elems <= MAX_NUM_ELEMENTS_IN_LIST; ++num_elems) {

        /*Construct the list having num_elems. 
        If num_elems = 1, the list will be 1
        If num_elems = 2, the list will be 1->2 */
        head = construct_list(num_elems);

        /*We test for different k values ranging from 0 to MAX_NUM_ELEMENTS_IN_LIST+1*/
        for (k = 0; k <= num_elems + 1; ++k) {
            printf("Input  : ");
            print_list(head);
            
            /*Find the kth node from the end*/
            k_node = find_kth_node_from_end(head, k);

            printf("Size = %d, %dth node from end is ", num_elems, k);

            if (k_node)
                printf("%d \n", k_node->data);
            else
                printf("Empty\n");

            /*Verify the kth node from the end*/
            if (k >= 1 && k <= num_elems) {
                if (k_node->data != num_elems - k + 1) {
                    handle_error();
                }
            } else {
                if (k_node != NULL) {
                    handle_error();
                }
            }

            printf("____________________________________________________\n");
        }

        destroy_list(head);
    }

    printf("Test passed\n");
    
    return 0;
}


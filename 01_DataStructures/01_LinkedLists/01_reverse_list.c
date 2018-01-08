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


void print_list(struct node* head) 
{
    struct node* cur_node = head;

    while (cur_node != NULL) {
        printf("%d ", cur_node->data);
        cur_node = cur_node->next;
    }
    printf("\n");
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



/* Reverses the linked list without using recursion
head: first node in the original linked list 
Return value: the first node of the reversed linked list
*/
struct node* reverse_linked_list(struct node *head)
{
    struct node *cur_node, *prev_node, *next_node;

    cur_node = head;
    prev_node = NULL;

    while (cur_node) {
        /*Store the next node in a temporary variable*/
        next_node = cur_node->next;

        /*Reverse the link so that current node points to the previous node*/
        cur_node->next = prev_node;

        /*Update the previous node to the current node */
        prev_node = cur_node;

        /*Proceed to the next node in the original linked list*/
        cur_node = next_node;
    }

    /*
    Once the linked list has been reversed, prev_node will be
    pointing to the new head. So return it
    */
    return prev_node;
}


/*Recursively reverses the linked list*/ 
/*cur_node : current node of the linked list being processed
Return value: new head to the reversed linked list*/
struct node* reverse_linked_list_r(struct node *cur_node) {
    struct node *new_head;
    if (!cur_node || !cur_node->next)
        return cur_node;/*return last node in original linked list as new head*/

    /*Recursively reverse the remaining nodes in the linked list*/
    new_head = reverse_linked_list(cur_node->next);

    /*Connect up the current node to the reversed linked list*/
    cur_node->next->next = cur_node;
    cur_node->next = NULL;
    return new_head;
}





struct node* construct_list(int num_elements)
{
    int i;
    struct node* head = NULL, *new_node;
    int value = num_elements;

    /*If num_elems = 1, the list will be 1->NULL
    If num_elems = 2, the list will be 1->2->NULL 
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

void test_non_recursive()
{
    struct node *head;
    struct node *cur_node;
    int num_elems, j;

    printf("Testing Non-Recursive Linked List Reversal\n\n");

    /*We test for different list lengths ranging from 0 to MAX_NUM_ELEMENTS_IN_LIST*/
    for (num_elems = 0; num_elems <= MAX_NUM_ELEMENTS_IN_LIST; ++num_elems) {
        
        /*Construct the list having num_elems. 
        If num_elems = 1, the list will be 1->NULL
        If num_elems = 2, the list will be 1->2->NULL */
        head = construct_list(num_elems);

        printf("Input  : ");
        print_list(head);

        /*Reverse the list*/
        head = reverse_linked_list(head);

        printf("Output : ");
        print_list(head);

        /*Iterate the reversed list and check if the list is in reverse order*/
        cur_node = head;
        for (j = 0; j < num_elems; ++j) {

            if (cur_node->data != num_elems - j) {
                handle_error();
            }

            cur_node = cur_node->next;
        }

        destroy_list(head);

        printf("_______________________________________________\n");
    }

}

void test_recursive()
{
    struct node *head;
    struct node *cur_node;
    int num_elems, j;

    printf("Testing Recursive Linked List Reversal\n\n");

    /*We test for different list lengths ranging from 0 to MAX_NUM_ELEMENTS_IN_LIST*/
    for (num_elems = 0; num_elems <= MAX_NUM_ELEMENTS_IN_LIST; ++num_elems) {
        
        /*Construct the list having num_elems. 
        If num_elems = 1, the list will be 1->NULL

        If num_elems = 2, the list will be 1->2->NULL */
        head = construct_list(num_elems);

        printf("Input  : ");
        print_list(head);

        /*Reverse the list*/
        head = reverse_linked_list_r(head);

        printf("Output : ");
        print_list(head);

        /*Iterate the reversed list and check if the list is in reverse order*/
        cur_node = head;
        for (j = 0; j < num_elems; ++j) {

            if (cur_node->data != num_elems - j) {
                handle_error();
            }

            cur_node = cur_node->next;
        }

        destroy_list(head);

        printf("_______________________________________________\n");
    }

}




int main()
{
    test_non_recursive();

    test_recursive();

    printf("Test passed\n");

    return 0;
}

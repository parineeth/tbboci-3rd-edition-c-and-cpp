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
    struct node *random;
};

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}



/*
original_head: head of the original linked list
Return value: head of the newly created linked list
*/
struct node* clone_list(struct node *original_head)
{
    struct node *n1, *n2, *new_head = NULL, *next_node;
    /*
    For each node in original linked list, create a new node. The new node
    initially will be placed next to the original node
    */
    n1 = original_head;
    while (n1) {
        next_node = n1->next;

        n2 = (struct node*) malloc(sizeof(struct node*));
        if (!n2) {
                return NULL;
        }
        n2->data = n1->data;

        if (!new_head) 
            new_head = n2;
        n1->next = n2;
        n2->next = next_node;
        n1 = next_node;
    }

    /*Set the random pointer correctly for the new nodes*/
    n1 = original_head;
    while (n1) {
        n1->next->random = n1->random->next;
        n1 = n1->next->next;
    }

    /*Disconnect new nodes from original linked list and form 
    a new linked list for them*/
    n1 = original_head;
    while (n1) {
        n2 = n1->next;
        n1->next = n1->next->next;
        if (n2->next)
            n2->next = n2->next->next;

        n1 = n1->next;
    }
    return new_head;
}




struct node* construct_list(int num_elements)
{
    int i;
    struct node* head = NULL, *new_node;
    int value = num_elements;
    struct node* ptr_array[MAX_NUM_ELEMENTS_IN_LIST];
    int rand_val;

    /*If num_elements is 2, the list created will be 1->2 */
    for (i = 0; i < num_elements; ++i) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->data = value;
        new_node->next = head;
        ptr_array[num_elements - 1 - i] = new_node;
        head = new_node;
        --value;
    }

    /*Connect each node in the list to a random node*/
    new_node = head;
    for (i = 0; i < num_elements; ++i) {
        rand_val = rand()% num_elements;
        new_node->random = ptr_array[rand_val];
        new_node = new_node->next;
    }


    return head;
}

void delete_list(struct node *head)
{
    struct node *cur_node = head;
    struct node *temp_node;

    while (cur_node) {
        temp_node = cur_node->next;
        free(cur_node);
        cur_node = temp_node;
    }
}


int main()
{
    struct node *head, *clone  ;
    struct node *n1, *n2;

    int num_elems;

    /*We test for different list lengths */
    for (num_elems = 0; num_elems <= MAX_NUM_ELEMENTS_IN_LIST; ++num_elems) {

        /*create a list with num_elems, where each node has a normal pointer and a
        random pointer*/
        head = construct_list(num_elems);

        /*Clone the original list to create another copy */
        clone = clone_list(head);

        /*Verify if the clone is a proper copy of the original list*/
        n1 = head;
        n2 = clone;
        while (n1 && n2) {
            if ( (n1->data != n2->data) || (n1->random->data != n2->random->data)) {
                handle_error();
            }

            n1 = n1->next;
            n2 = n2->next;
        }

        /*If the original list or the clone is longer than the other then return an error*/
        if (n1 || n2)
            handle_error();

        delete_list(head);
        delete_list(clone);
    }

    printf("Test passed\n");
    return 0;
}

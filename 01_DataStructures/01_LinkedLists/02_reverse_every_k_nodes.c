/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
head: the first node of the linked list
k: how many nodes should be reversed
Return value: first node of the new linked list after reversing every k nodes
*/
struct node * k_reverse_list(struct node *head, int k)
{
    struct node *cur_node,  *prev_node, *temp_node;
    int i = 0;

    if (!head || k == 0)
        return head;

    cur_node = head;
    prev_node = NULL;

    while (cur_node && i < k) {
        /*Store the next node in a temporary variable*/
        temp_node = cur_node->next;

        /*Reverse the link */
        cur_node->next = prev_node;

        /*Update the previous node to the current node */
        prev_node = cur_node;

        /*Proceed to the next node in the original linked list*/
        cur_node = temp_node;

        ++i;
    }

    /*
    We have reversed k nodes. cur_node points to the (k+1)th node
    and head points to the kth node.
    Now recursively process the remaining nodes from cur_node onwards 
    and assign the result to head->next.
    */
    if (cur_node)
        head->next = k_reverse_list(cur_node, k);

    /*prev_node will point to first node in linked list after reversal*/
    return prev_node;
}




void print_list(struct node *head)
{
    struct node *cur_node = head;

    while (cur_node) {
        printf("%d ", cur_node->data);
        cur_node = cur_node->next;
    }
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



void test_01()
{
    struct node *head;
    int num_elems, k;

    /*We test for different list lengths ranging from 0 to MAX_NUM_ELEMENTS_IN_LIST*/
    for (num_elems = 0; num_elems <= MAX_NUM_ELEMENTS_IN_LIST; ++num_elems) {

        /*We test for different k values ranging from 0 to MAX_NUM_ELEMENTS_IN_LIST+1*/
        for (k = 0; k <= MAX_NUM_ELEMENTS_IN_LIST + 1; ++k) {

            /*Construct the list having num_elems. 
            If num_elems = 1, the list will be 1
            If num_elems = 2, the list will be 1->2 */
            head = construct_list(num_elems);

            printf("Size = %d, K = %d\n", num_elems, k);

            printf("Original: ");
            print_list(head);
            printf("\n");


            head = k_reverse_list(head, k);

            printf("Reversed: ");
            print_list(head);
            printf("\n");

            printf("_________________________________________\n");

        }

        destroy_list(head);
    }

    printf("Test passed\n");
}




int main()
{
    test_01();

    return 0;
}

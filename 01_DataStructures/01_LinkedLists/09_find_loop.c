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


/*head: first node of the linked list 
Return value: first node in loop if loop exists, NULL otherwise
*/
struct node* find_loop( struct node *head) 
{
    struct node *n1 = head, *n2 = head, *n3;
    int found_loop = 0;

    /*n1 is the fast pointer. So advance it by two steps
    n2 is slow pointer. So advance it by one step
    */
    while (n1 != NULL) {
        n1 = n1->next;
        if (n1) {
            n1 = n1->next;
            n2 = n2->next;
        }

        /*If n1 and n2 meet then there is a loop in the linked list*/
        if (n1 == n2) {
            found_loop = 1;
            break;
        }
    }
    
    if (!found_loop)
        return NULL;

    /*Find the beginning of the loop*/
    n3 = head;
    while (n1 != n3) {
        n1 = n1->next;
        n3 = n3->next;
    }
    
    return n1;
}



struct node* construct_list(int num_elements)
{
    int i;
    struct node* head = NULL, *new_node;
    int value = num_elements - 1;

    /*If num_elems = 1, the list will be 0
    If num_elems = 2, the list will be 0->1 
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




/*Adds a loop to the linked list at a random position
Return value: the first node in the loop*/
struct node* add_loop_to_list(struct node *head, int num_elems)
{
    int i, low, high;
    struct node *ptr1 = NULL, *ptr2 = NULL, *cur_node;

    /*Randomly generate 2 values*/
    low = rand() % num_elems;
    high = rand() % num_elems;

    /*Make sure that low <= high*/
    if (low > high) {
        int temp = low;
        low = high;
        high = temp;
    }

    

    /*Find the nodes at positions low and high*/
    cur_node = head;
    i = 0;
    while (cur_node != NULL) {
        if (i == low)
            ptr1 = cur_node;

        if (i == high) {
            ptr2 = cur_node;
            break;
        }

        ++i;
        cur_node = cur_node->next;
    }

    printf("Adding loop from pos %d to pos %d\n", high, low);
    
    /*Add loop from node at position high to node at position low*/ 
    ptr2->next = ptr1;

    return ptr1;
}

void test_01()
{
    struct node *head;
    struct node *expected_loop_begin, *result;
    int num_elems;

    /*We test for different list lengths */
    for (num_elems = 0; num_elems <= MAX_NUM_ELEMENTS_IN_LIST; ++num_elems) {

        printf("Number of elements = %d\n", num_elems);

        /*Construct the list without any loops 
        If num_elems = 2, the list will be 0->1 */
        head = construct_list(num_elems);

        /*Currently there are no loops in the list. If we find a loop, report error*/
        if (find_loop(head))
            handle_error();

        if (head != NULL) {
            /*Add a loop to the list*/
            expected_loop_begin = add_loop_to_list(head, num_elems);

            /*We should find a loop in the list. If we don't find a loop, report error*/
            result = find_loop(head);
            if (result != expected_loop_begin )
                handle_error();

            printf("Found loop in list starting at node %d\n", result->data);
        }

        printf("____________________________________________________\n");
    }

}



int main()
{
    
    test_01();

    printf("Test passed\n");
    return 0;
}

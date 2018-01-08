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

static void print_list(struct node* head) 
{
    struct node* cur_node = head;

    while (cur_node != NULL) {
        printf("%d ", cur_node->data);
        cur_node = cur_node->next;
    }
    printf("\n");
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


struct node* find_kth_node_from_begin(struct node *head, int k, struct node **prev_pp)
{
    int i;
    struct node *cur_node = head;
    struct node *prev = NULL;

    if (prev_pp)
        *prev_pp = NULL;

    i = 1;
    while (cur_node != NULL) {
        if (i == k) {
            if (prev_pp)
                *prev_pp = prev;
            return cur_node;
        }

        prev = cur_node;
        cur_node = cur_node->next;
        ++i;
    }

    return NULL;
    
}




/* 
head: pointer to the the first element of the list
k: which element from the end.
length: number of elements in the list
prev_pp: pointer to element previous the kth element is returned here 
Return value: pointer to kth element from end if it exists, NULL otherwise
*/
struct node* find_kth_node_from_end(struct node *head, int k, int length, struct node **prev_pp)
{
    struct node *n1, *prev;
    int i;

    *prev_pp = NULL;

    n1 = head;
    prev = NULL;
    for (i = 1; i <= length; ++i) {
        if (i == length - k + 1) {
            *prev_pp = prev;
            return n1;  /*n1 is the kth element from end. So return it*/
        }
        prev = n1;
        n1 = n1->next;
    }

    /*k value passed doesn't match with the linked list. So return null */
    return NULL;
}






/*Helper function which swaps two neighbors n1 and n2
head: first node in the linked list
prev: node previous to n1
n1: first node to be swapped
n2: second node to be swapped. n2 occurs immediately after n1
Return value: head of the result linked list after swapping neighbors
*/
struct node* swap_neighbors(struct node *head, struct node *prev, 
            struct node *n1, struct node *n2)
{
    /*Swap n1 and n2*/
    n1->next = n2->next;
    n2->next = n1;

    if (prev) {
        prev->next = n2;
    } else {
        head = n2; /*If prev doesn't exist, update head to n2*/
    }
    return head; 
}



/*Main function for swapping the kth node from beginning and end
head: first node in the linked list
k: which node in the linked list should be swapped
length: number of nodes in the linked list
Return value: head of the result linked list on success, NULL on error
*/
struct node* swap_kth_node(struct node *head, int k, int length)  {
    struct node  *temp;
    struct node *k1, *k2, *prev1, *prev2;

    if (!head || k < 1 || k > length)
        return NULL;

    prev1 = prev2 = NULL;

    /*k1 is the kth node from begining and prev1 is previous to k1*/
    k1 = find_kth_node_from_begin(head, k, &prev1);

    /*k2 is the kth node from end and prev2 is previous to k2*/
    k2 = find_kth_node_from_end(head, k, length, &prev2);

    if (k1 == NULL || k2 == NULL)
        return NULL; /*the k value is incorrect*/

    if (k1 == k2)
        return head; /*both nodes are the same. So no need to swap*/
    
    /*Handle the case where k1 and k2 are neighbors and return*/
    if (k1->next == k2) 
        return swap_neighbors(head, prev1, k1, k2);

    if (k2->next == k1) 
        return swap_neighbors(head, prev2, k2, k1);

    /*k1 and k2 are not neighbors. So swap k1.next with k2.next*/
    temp = k1->next;
    k1->next = k2->next;
    k2->next = temp;

    if (prev1) {
        prev1->next = k2; 
    } else  {
        head = k2; /* After swap, k2 becomes new head*/
    }

    if (prev2) {
        prev2->next = k1; 
    } else  {
        head = k1; /* After swap, k1 becomes new head */
    }

    return head;
}







int main()
{
    struct node *head  ;
    struct node *k_node;
    int k, num_elems;

    /*We test for different list lengths */
    for (num_elems = 0; num_elems <= MAX_NUM_ELEMENTS_IN_LIST; ++num_elems) {

        /*Construct the list having num_elems. 
        If num_elems = 1, the list will be 1
        If num_elems = 2, the list will be 1->2 */
        head = construct_list(num_elems);

        /*Passing k value of 0 should return in an error*/
        if (swap_kth_node(head, 0, num_elems) != NULL)
            handle_error();

        /*We test for different k values*/
        for (k = 1; k <= num_elems; ++k) {

            printf("Size = %d, k = %d \n", num_elems, k);
            printf("Input  : ");
            print_list(head);

            /*Swap the kth element*/
            head = swap_kth_node(head, k, num_elems);

            printf("Output : ");
            print_list(head);

            /*Verify the result*/
            k_node = find_kth_node_from_begin(head, k, NULL);

            if (k_node->data != num_elems - k + 1) {
                handle_error();
            }

            /*Again swap the kth element to get back the original list*/
            head = swap_kth_node(head, num_elems - k + 1, num_elems);

            /*Verify the result*/
            k_node = find_kth_node_from_begin(head, k, NULL);

            if (k_node->data != k)
                handle_error();

            printf("_______________________________________\n");
            
        }

        /*Passing a value of k that is greater than length of list should return an error*/
        if (swap_kth_node(head, num_elems + 1, num_elems) != NULL)
            handle_error();

        destroy_list(head);
    }

    printf("Test passed\n");
    return 0;
}


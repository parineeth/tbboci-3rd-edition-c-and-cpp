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


struct node* construct_list(int num_elements)
{
    int i;
    struct node* head = NULL, *new_node;
    int value = num_elements;

    /*If num_elements is 2, then list will be 1->2 */
    for (i = 0; i < num_elements; ++i) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->data = value;
        new_node->next = head;
        head = new_node;
        --value;
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


/*
head: first node of the linked list
k: by how many positions the linked list should be rotated
length: number of nodes in the linked list
Return value: first node of the rotated linked list
*/
struct node* rotate_list(struct node *head, int k, int length)
{
    struct node *pivot, *prev, *last;

    /*If there are 0 or 1 nodes in the linked list, then simply return*/
    if (length < 2)
        return head;

    /*If we shift by k times, then we get back the same linked list. So we 
    just have to shift k % length times*/
    k = k % length;

    /*If k is 0, then no need to shift*/
    if (k == 0)
        return head;

    /*Find the kth node from the end. If k = 1, then pivot will have
    the last node and prev will be the node previous to last node*/
    prev = NULL;
    pivot = find_kth_node_from_end(head, k, length, &prev);

    /*Find the last node in the linked list*/
    last = pivot;
    while (last->next)
        last = last->next;

    /*Make the last node point to head and the node previous to pivot
    point to NULL*/
    last->next = head;
    prev->next = NULL;

    /*pivot will be the new head*/
    return pivot;
}


void compare_list(struct node *head, int expected_result[], int length)
{
    int i;
    struct node* cur_node = head;
    
    for (i = 0; i < length; ++i) {
        if (cur_node == NULL)
            handle_error();

        if (cur_node->data != expected_result[i]) 
            handle_error();
        
        cur_node = cur_node->next; 
    }

    if (cur_node != NULL)
        handle_error();
}   



void perform_test(struct node *head, int length, int num_rotations, int expected_result[])
{
    printf("Num Rotations = %d\n", num_rotations);

    printf("Before Rotating: ");
    print_list(head);

    head = rotate_list(head, num_rotations, length);
    compare_list(head, expected_result, length);

    printf("After  Rotating: ");
    print_list(head); 

    printf("________________________________________\n");   
}


void test1() 
{
    struct node *head;
    int expected_result[] = {1};
    int length = 1, num_rotations = 1;

    /*list initially contains 1->NULL */
    head = construct_list(length);
    perform_test(head, length, num_rotations, expected_result);
    delete_list(head);
}


void test2() 
{
    struct node *head;
    int expected_result[] = {5, 1, 2, 3, 4};
    int length = 5, num_rotations = 1;

    /*list initially contains 1->2->3->4->5 */
    head = construct_list(length);
    perform_test(head, length, num_rotations, expected_result);
    delete_list(head);
}


void test3() 
{
    struct node *head;
    int expected_result[] = {4, 5, 1, 2, 3};
    int length = 5, num_rotations = 2;

    /*list initially contains 1->2->3->4->5 */
    head = construct_list(length);
    perform_test(head, length, num_rotations, expected_result);
    delete_list(head);  
}


void test4() 
{
    struct node *head;
    int expected_result[] = {2, 3, 4, 5, 1};
    int length = 5, num_rotations = 4;

    /*list initially contains 1->2->3->4->5 */
    head = construct_list(length);
    perform_test(head, length, num_rotations, expected_result);
    delete_list(head);  
}

void test5() 
{
    struct node *head;
    int expected_result[] = {1, 2, 3, 4, 5};
    int length = 5, num_rotations = 5;

    /*list initially contains 1->2->3->4->5 */
    head = construct_list(length);
    perform_test(head, length, num_rotations, expected_result);
    delete_list(head);      
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();

    printf("Test passed\n");
    return 0;
}



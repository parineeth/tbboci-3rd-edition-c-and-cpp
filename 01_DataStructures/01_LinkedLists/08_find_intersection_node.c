/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_ELEMS (10)
#define MAX_NUM_TESTS (10)

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


struct node* construct_list(int num_elements, int start_value)
{
    int i;
    struct node *head = NULL, *new_node, *prev;
    int value = start_value;

    prev = NULL;
    for (i = 0; i < num_elements; ++i) {
        new_node = (struct node*) calloc(1, sizeof(struct node));

        if (prev == NULL)
            head = new_node;
        else 
            prev->next = new_node;
        
        new_node->data = value;
        new_node->next = NULL;

        prev = new_node;        

        ++value;
    }

    return head;
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

int find_length(struct node * n1)
{
    int length = 0;
    while (n1 != NULL) {
        n1 = n1->next;
        ++length;
    }
    return length;
}

/*
head1: first node of linked list1
head2: first node of linked list2
Return value: first common node between the two linked lists
*/
struct node * find_intersection_node(struct node * head1, struct node *head2)
{
    struct node *n1, *n2;
    int length1, length2, diff;

    /*Find the length of the two linked lists*/
    length1 = find_length(head1);
    length2 = find_length(head2);

    /*store head of the longer linked list in n1 and head of shorter 
    linked list in n2*/
    if (length1 >= length2) {
        n1 = head1;
        n2 = head2;
    } else {
        n1 = head2;
        n2 = head1;
    }

    /*Find the difference in length of the two linked lists. Then advance
    n1 by the difference*/
    diff = abs(length1 - length2);
    while (diff > 0) {
        n1 = n1->next;
        --diff;
    }

    /*Go on comparing the nodes in linked list1 starting from n1 and
    linked list2 starting from n2 till n1 and n2 match*/
    while (n1 && n2 && n1 != n2) {
        n1 = n1->next;
        n2 = n2->next;
    }

    /*n1 will have the common node if it exists, otherwise n1 will be NULL*/
    return n1;
}


void test()
{
    struct node *head1, *head2, *head3;
    struct node *n1, *n2;
    struct node *result, *expected_result;
    int length1, length2, length3, start_value;

    /*Randomly generate the length of list1 and generate the elements of the list
    If there are two elements in the list, then list is 0->1*/
    length1 = rand() % MAX_NUM_ELEMS;
    start_value = 0;
    head1 = construct_list(length1, start_value);

    /*Randomly generate the length of list2 and generate the elements of the list
    If there are two elements in the list, then list is 100->101*/
    length2 = rand() % MAX_NUM_ELEMS;
    start_value = 100;
    head2 = construct_list(length2, start_value);

    /*Randomly generate the length of list3 and generate the elements of the list
    If there are two elements in the list, then list is 200->201*/
    length3 = rand() % MAX_NUM_ELEMS;
    start_value = 200;
    head3 = construct_list(length3, start_value);

    /*Find the last element in list1 and store it in n1*/
    n1 = head1;
    while (n1 && n1->next) {
        n1 = n1->next;
    }

    /*Find the last element in list2 and store it in n2*/
    n2 = head2;
    while (n2 && n2->next) {
        n2 = n2->next;
    }

    /*Connect the last element of list1 to first element of list3*/
    if (n1)
        n1->next = head3;

    /*Connect the last element of list2 to first element of list3*/
    if (n2)
        n2->next = head3;


    printf("List 1 : ");
    print_list(head1);

    printf("List 2 : ");
    print_list(head2);

    /*Find the first common node between list1 and list2*/
    result = find_intersection_node(head1, head2);

    if (result)
        printf("Intersection node = %d\n", result->data);
    else 
        printf("No intersection node\n");

    /*The expected result is the first element in list3*/
    expected_result = NULL;
    if (n1 && n2)
        expected_result = head3;

    if (result != expected_result)
        handle_error();
    
    printf("________________________________________________\n");
}

int main()
{
    int i;

    for (i = 0; i < MAX_NUM_TESTS; ++i) {
        test();
    }

    printf("Test passed \n");
    return 0;   
}



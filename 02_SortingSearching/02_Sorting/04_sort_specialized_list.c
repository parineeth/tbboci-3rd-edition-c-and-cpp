/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


#define MAX_NUM_ELEMENTS (10)
#define MAX_NUM_LOOPS   (10)
#define MAX_VALUE   (3)


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
head: array of head pointers of the seperated lists
tail: array of tail pointers of the seperated lists
cur_node: current node being processed
i: data value of the node
*/
void add_node(struct node *head[], struct node *tail[], 
        struct node *cur_node, int i)
{
    cur_node->next = head[i];
    head[i] = cur_node;
    if (!tail[i])
        tail[i] = cur_node;

}

/*first_node: first node in list to be sorted 
num_distinct_values: number of distinct values in the nodes
Return value: head of the sorted list
*/
struct node * sort_list(struct node *first_node, int num_distinct_values)
{
    struct node **head, **tail; 
    struct node *result = NULL, *cur_node, *next_node, *last_element;
    int i;

    if (!first_node)
        return NULL;

    head = (struct node**) calloc(num_distinct_values, sizeof(struct node*));
    tail = (struct node**) calloc(num_distinct_values, sizeof(struct node*)); 

    for (i = 0; i < num_distinct_values; ++i) {
        head[i] = NULL;
        tail[i] = NULL;
    }

    /*Partition the list into seperate lists, (0-list, 1-list, 2-list)
    based on the data in the node*/
    cur_node = first_node;
    while (cur_node) {
        next_node = cur_node->next;
        add_node(head, tail, cur_node, cur_node->data);
        cur_node = next_node;
    }

    /*Connect the tail of first linked list with head of second linked list
    and so on*/
    result = head[0];
    last_element = tail[0];
    for (i = 1; i < num_distinct_values; ++i) {
        if (!result)
            result = head[i];

        /*Link last element of previous list with head of current list*/
        if (last_element)
            last_element->next = head[i];

        /*update the last element to the tail of current list*/
        if (tail[i])
            last_element = tail[i];
    }

    free(head);
    free(tail);

    return result;
}






struct node* construct_list(int num_elements)
{
    int i;
    struct node* head = NULL, *new_node;

    for (i = 0; i < num_elements; ++i) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->data = rand() % MAX_VALUE;
        new_node->next = head;
        head = new_node;
    }

    return head;
}


void verify_list(struct node *head)
{
    struct node *cur_node = head;
    struct node *prev_node = NULL;

    while (cur_node) {
        if (prev_node) {
            if (cur_node->data < prev_node->data) {
                handle_error();
            }
        }

        prev_node = cur_node;
        cur_node = cur_node->next;
    }
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

void print_list(struct node* head) 
{
    struct node* cur_node = head;

    while (cur_node != NULL) {
        printf("%d ", cur_node->data);
        cur_node = cur_node->next;
    }
    printf("\n");
}



int test()
{
    int num_elems1;
    struct node *list1;

    num_elems1 = rand() % MAX_NUM_ELEMENTS;

    list1 = construct_list(num_elems1);

    printf("Input  : ");
    print_list(list1);

    list1 = sort_list(list1, MAX_VALUE);

    printf("Output : ");
    print_list(list1);

    verify_list(list1);

    delete_list(list1);

    printf("__________________________________________________\n");

    return 0;
}


int main()
{
    int num_loops;

    for (num_loops = 0; num_loops < MAX_NUM_LOOPS; ++num_loops) {
        test();
    }

    printf("Test passed\n");

    return 0;
}

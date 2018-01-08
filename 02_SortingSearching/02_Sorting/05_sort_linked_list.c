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
#define MAX_VALUE   (100)


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
n1 - head of first sorted list
n2 - head of second sorted list
Result - head of merged sorted list
*/
struct node* merge_lists( struct node *n1, struct node *n2)
{
    struct node *merge_node, *result;

    /*If list1 is empty, return n2 */
    if (!n1)
        return n2;

    /*If list2 is empty, return n1*/
    if (!n2)
        return n1;

    /*Since we are sorting in ascending order, result points to
    the node with the smaller value */
    if (n1->data <= n2->data) {
        result = n1;
        n1 = n1->next;
    } else {
        result = n2;
        n2 = n2->next;
    }

    /*Process the two lists*/
    merge_node = result;
    while (n1 != NULL && n2 != NULL) {

        if (n1->data <= n2->data) {
            merge_node->next = n1;
            n1 = n1->next;
            merge_node = merge_node->next;
        } else {
            merge_node->next = n2;
            n2 = n2->next;
            merge_node = merge_node->next;
        }
    }

    /*If there are still nodes present in list1 or list2, then
    append them to the result list*/
    if (n1)
        merge_node->next = n1;
    else
        merge_node->next = n2;

    return result;

}



/*
first_node: head of the list to be sorted
num_elements: number of elements in the list
Return value: head of the merged and sorted list
*/
struct node * sort_list(struct node *first_node, int num_elements)
{
    struct node *list1, *list2, *cur_node;
    int i, count1, count2;

    if (num_elements == 0)
        return NULL;
    /*
    If there is only a single node in the list, then disconnect next 
    and return the node as the result without any further recursive calls
    */
    if (num_elements == 1) {
        first_node->next = NULL;
        return first_node;
    }

    /*
    Divide the list into two lists. list1 has count1 elements and
    list2 has count2 elements 
    */
    list1 = first_node;
    count1 = num_elements / 2;

    cur_node = first_node;
    for (i = 0; i < count1; ++i)
        cur_node = cur_node->next;

    list2 = cur_node;
    count2 = num_elements - count1;

    /*Call sort_list recursively on list1 and list2*/
    list1 = sort_list(list1, count1);
    list2 = sort_list(list2, count2);

    /*
    list1 and list2 are now sorted. So merge the two lists into a single
    sorted list and return its head node
    */
    return merge_lists(list1, list2);
}



struct node* construct_list(int num_elements, int max_value)
{
    int i;
    struct node* head = NULL, *new_node;

    for (i = 0; i < num_elements; ++i) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->data = rand() % max_value;
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

    list1 = construct_list(num_elems1, MAX_VALUE);

    printf("Input  : ");
    print_list(list1);

    list1 = sort_list(list1, num_elems1);

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



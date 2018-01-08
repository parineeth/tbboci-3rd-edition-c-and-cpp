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
#define MAX_VALUE   (10)


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
n1: head of the first linked list
n2: head of the second linked list
Return value: head of the merged linked list
*/
struct node* merge_lists( struct node *n1, struct node *n2)
{
    struct node *prev_merge_node, *result;

    if (!n1) 
        return n2; /*If linked list1 is empty, return n2 */

    if (!n2) 
        return n1; /*If linked list2 is empty, return n1*/

    /*Make the result point to the node with the smaller value */
    if (n1->data <= n2->data) {
        result = n1;
        prev_merge_node = n1;
        n1 = n1->next;
    } else {
        result = n2;
        prev_merge_node = n2;
        n2 = n2->next;
    }

    /*Process the two linked lists*/
    while (n1 != NULL && n2 != NULL) {
        if (n1->data <= n2->data) {
            prev_merge_node->next = n1;
            n1 = n1->next;
            prev_merge_node = prev_merge_node->next;
        } else {
            prev_merge_node->next = n2;
            n2 = n2->next;
            prev_merge_node = prev_merge_node->next;
        }
    }

    
    /*
    If there are still nodes present in linked list1 or linked list2, then
    append them to the result list
    */
    if (n1) 
        prev_merge_node->next = n1;
    else 
        prev_merge_node->next = n2;
    
    return result;
}



struct node* construct_list(int num_elements, int values[])
{
    int i;
    struct node* head = NULL, *new_node;

    for (i = 0; i < num_elements; ++i) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->data = values[num_elements - 1 - i ];
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
            /*If the elements are not in ascending order, then return an error*/
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


void print_list(struct node *head)
{
    struct node *cur_node = head;

    while (cur_node) {
        printf("%d ", cur_node->data);
        cur_node = cur_node->next;
    }
    printf("\n");
}


/*Sort the array */
void sort_array(int array[], int num_elems)
{
    int i, j, temp;

    for (i = 0; i < num_elems; ++i) {
        for (j = 0; j < num_elems - 1; ++j) {
            if (array[j] > array[j+1]) {
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

int test_merge_sort()
{
    int array1[MAX_NUM_ELEMENTS];
    int array2[MAX_NUM_ELEMENTS];

    int i;

    int num_elems1, num_elems2;

    struct node *list1, *list2, *merged_list;

    /*randomly decide the size of the lists*/
    num_elems1 = rand() % MAX_NUM_ELEMENTS;
    num_elems2 = rand() % MAX_NUM_ELEMENTS;

    /*Store random values in the arrays*/
    for (i = 0; i < num_elems1; ++i) {
        array1[i] = rand() % MAX_VALUE;
    }

    for (i = 0; i < num_elems2; ++i) {
        array2[i] = rand() % MAX_VALUE;
    }

    /*Sort the arrays*/
    sort_array(array1, num_elems1);
    sort_array(array2, num_elems2);

    /*Construct the lists based on the elements in the array
    The list will contain the elements in ascending order*/
    list1 = construct_list(num_elems1, array1);
    list2 = construct_list(num_elems2, array2);

    printf("Input1 : ");
    print_list(list1);

    printf("Input2 : ");
    print_list(list2);

    /*Merge the lists*/
    merged_list = merge_lists(list1, list2);

    printf("Output : ");
    print_list(merged_list);

    /*Verify the lists*/
    verify_list(merged_list);

    delete_list(merged_list);

    printf("__________________________________________\n");

    return 0;
}


int main()
{
    int num_loops;

    for (num_loops = 0; num_loops < MAX_NUM_LOOPS; ++num_loops) {
        test_merge_sort();
    }

    printf("Test passed\n");

    return 0;
}

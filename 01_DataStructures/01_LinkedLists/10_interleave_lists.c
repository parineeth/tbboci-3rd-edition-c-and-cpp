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
Return value: head of the result interleaved linked list
*/
struct node* interleave_lists( struct node *n1, struct node *n2)
{
    struct node *result,  *temp1, *temp2;

    if (!n1) {
        return n2; /*If linked list1 is empty, return n2 */
    }
    
    if (!n2) {
        return n1; /*If linked list2 is empty, return n1*/
    }
    
    /*Process the two linked lists*/
    result = n1;
    while (n1 != NULL && n2 != NULL) {
        temp1 = n1->next;
        temp2 = n2->next;

        /*Place node of second linked list next to the node 
        of the first linked list*/
        if (n1->next)
            n2->next = n1->next;
        n1->next = n2;

        n1 = temp1;
        n2 = temp2;
    }
    return result;
}


struct node* construct_list(int num_elements, int values[])
{
    int i;
    struct node* head = NULL, *new_node;

    /*Construct list based on elements in the array 
    values[0] will be the last element in the list*/
    for (i = 0; i < num_elements; ++i) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->data = values[num_elements - 1 - i];
        new_node->next = head;
        head = new_node;
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


void print_list(struct node *head)
{
    struct node *cur_node = head;

    while (cur_node) {
        printf("%d ", cur_node->data);
        cur_node = cur_node->next;
    }
    printf("\n");
}



int test_interleave()
{
    int array1[MAX_NUM_ELEMENTS];
    int array2[MAX_NUM_ELEMENTS];

    int i;

    int num_elems1, num_elems2;

    struct node *list1, *list2, *result_list, *cur_node;

    num_elems1 = rand() % MAX_NUM_ELEMENTS;
    num_elems2 = rand() % MAX_NUM_ELEMENTS;

    /*If num_elems1 = 5, array1 will contain 1, 2, 3, 4, 5 */
    for (i = 0; i < num_elems1; ++i) {
        array1[i] = i + 1;
    }

    /*If num_elems2 = 5, array2 will contain 101, 102, 103, 104, 105*/
    for (i = 0; i < num_elems2; ++i) {
        array2[i] = 101 + i;
    }

    /*Use the arrays to construct the two lists
    If num_elems1 = 5, list1 will contain 1->2->3->4->5
    If num_elems2 = 5. list2 will contain 101->102->103->104->105*/
    list1 = construct_list(num_elems1, array1);
    list2 = construct_list(num_elems2, array2);

    printf("Input 1: ");
    print_list(list1);

    printf("Input 2: ");
    print_list(list2);

    /*Interleave the lists*/
    result_list = interleave_lists(list1, list2);

    /*Verify the result*/
    i = 0;
    cur_node = result_list;
    while (cur_node) {
        /*If index is even, then the element should be less than 100*/
        if (i % 2 == 0 && i < 2 * num_elems1) {
            if (cur_node->data >= 100)
                handle_error();
        }

        /*If index is odd, then the element should be more than 100*/
        if (i % 2 == 1 && i < 2 * num_elems2) {
            if (cur_node->data < 100)
                handle_error();
        }
        ++i;
        cur_node = cur_node->next;
    }

    if (i != (num_elems1 + num_elems2))
        handle_error();


    printf("Output : ");
    print_list(result_list);

    printf("__________________________________________________\n");

    delete_list(result_list);

    return 0;
}


int main()
{
    int num_loops;

    for (num_loops = 0; num_loops < MAX_NUM_LOOPS; ++num_loops) {

            test_interleave();
    }

    printf("Test passed\n");

    return 0;
}

/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


#define MAX_NUM_ELEMENTS_IN_LIST (4)
#define MAX_NUM_TESTS (100)

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


struct node
{
    int data;
    struct node *next;
};



struct node* reverse_linked_list(struct node *head)
{
    struct node *current_node = head;
    struct node *previous_node = NULL;
    struct node *temp_node;

    while (current_node) {
        /*Store the next node in a temporary variable*/
        temp_node = current_node->next;

        /*Reverse the link so that current node points to the previous node*/
        current_node->next = previous_node;

        /*Update the previous node to the current node */
        previous_node = current_node;

        /*Proceed to the next node in the original list*/
        current_node = temp_node;
    }

    /*
    Once the list has been reversed, previous_node will be
    pointing to the new head. So return it
    */
    return previous_node;
}




/*n1, n2: head of the first and second linked list
count1, count2: num elements in first and second linked list
Return value: head of new linked list having the result of multiplication*/
struct node* multiply_lists(struct node *n1, struct node *n2, int count1, 
            int count2)
{
    struct node *p1, *p2, *h1, *h2;
    struct node *cur_res_node, *result_head, *result_start_node;
    int i, product, sum, carry;
    
    /*Reverse the two input linked lists*/
    h1 = reverse_linked_list(n1);
    h2 = reverse_linked_list(n2);

    /*Pre-create the result linked list*/
    i = 0;
    result_head = NULL;
    while (i < count1 + count2 ) {
        cur_res_node = (struct node*) calloc(1, sizeof (struct node*));
        cur_res_node->next = result_head;
        result_head = cur_res_node;
        ++i;
    }

    /*Perform the multiplication*/
    result_start_node = result_head;
    p1 = h1;
    while (p1 != NULL) {
        cur_res_node = result_start_node;
        p2 = h2;
        carry = 0;
        while (p2 != NULL) {

            product = p1->data * p2->data;
            sum = product + cur_res_node->data + carry;
            cur_res_node->data = sum % 10;
            carry = sum / 10;

            p2 = p2->next;
            cur_res_node = cur_res_node->next;
        }

        cur_res_node->data = carry;

        p1 = p1->next;
        result_start_node = result_start_node->next;
    }
    /*Reverse back the two input linked lists*/
    reverse_linked_list(h1);
    reverse_linked_list(h2);

    /*Reverse the result linked list*/
    result_head = reverse_linked_list(result_head);
    return result_head;
}




struct node* construct_list(int num_elements)
{
    int i;
    struct node* head = NULL, *new_node;
    int value = num_elements;

    for (i = 0; i < num_elements; ++i) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->data = rand()%10;
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


void print_list(struct node *head)
{
    struct node *cur_node = head;

    while (cur_node) {
        printf("%d ", cur_node->data);
        cur_node = cur_node->next;
    }

}

int convert_list_to_value(struct node *head)
{
    struct node *cur_node = head;
    int result = 0;

    while (cur_node) {
        result = result*10 + cur_node->data;
        cur_node = cur_node->next;
    }

    return result;
}

int main()
{
    struct node *head1, *head2, *result;
    int num_elems1, num_elems2, iter ;
    int val1, val2, val3;

    /*Try out several tests where the inputs are randomly generated*/
    for (iter = 0; iter < MAX_NUM_TESTS; ++iter) {

        /*Generate a random list with a random number of elements*/
        num_elems1 = rand() % MAX_NUM_ELEMENTS_IN_LIST;
        head1 = construct_list(num_elems1);

        /*Generate a random list with a random number of elements*/
        num_elems2 = rand() % MAX_NUM_ELEMENTS_IN_LIST;
        head2 = construct_list(num_elems2);

        /*Perform the multiplication*/
        result = multiply_lists(head1, head2, num_elems1, num_elems2);

        /*Obtain the integer value of the two input lists and the result list*/
        val1 = convert_list_to_value(head1);

        val2 = convert_list_to_value(head2);

        val3 = convert_list_to_value(result);

        printf("%d * %d = %d\n\n", val1, val2, val3);

        /*Verify the result*/
        if (val3 != (val1 * val2)) {
            handle_error();
        }


        delete_list(head1);
        delete_list(head2);
        delete_list(result);
    }

    printf("Test passed\n");
    return 0;
}

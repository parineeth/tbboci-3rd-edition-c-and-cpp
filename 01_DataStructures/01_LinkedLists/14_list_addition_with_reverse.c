/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>



#define MAX_NUM_ELEMENTS_IN_LIST (10)
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




/*
n1: head of the first linked list 
n2: head of the second linked list
Return value: head of new linked list having the result of addition of 
    the two linked lists
*/
struct node* add_lists(struct node *n1, struct node *n2)
{
    struct node *p1, *p2, *h1, *h2;
    struct node *new_node, *result_node;
    int sum, carry;

    /*Reverse the two input linked lists*/
    h1 = p1 = reverse_linked_list(n1);
    h2 = p2 = reverse_linked_list(n2);

    /*Add the nodes of the two linked lists*/
    sum = 0;
    carry = 0;
    result_node = NULL;
    while (p1 != NULL && p2 != NULL) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->next = result_node;
        result_node = new_node;

        sum = p1->data + p2->data + carry;
        new_node->data = sum % 10;
        carry = sum / 10;

        p1 = p1->next;
        p2 = p2->next;
    }

    /*If one of the two input linked lists still has nodes to be processed
    then make p1 point to the leftover input linked list*/
    if (p2 != NULL)
        p1 = p2;

    /*Process the remaining input linked list*/
    while (p1) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->next = result_node;
        result_node = new_node;

        sum = p1->data + carry;
        new_node->data = sum % 10;
        carry = sum / 10;
        p1 = p1->next;
    }
    /*If carry is non-zero, then store the carry in the result linked list*/
    if (carry) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->next = result_node;
        result_node = new_node;
        new_node->data = carry;
    }

    /*Reverse back the two input linked lists*/
    reverse_linked_list(h1);
    reverse_linked_list(h2);

    /*The result  node already points to MS node.  
    So no need to reverse result linked list*/
    return result_node;
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

        /*Perform the addition*/
        result = add_lists(head1, head2);

        /*Obtain the integer value of the two input lists and the result list*/
        val1 = convert_list_to_value(head1);

        val2 = convert_list_to_value(head2);

        val3 = convert_list_to_value(result);

        printf("%d + %d = %d\n\n", val1, val2, val3);

        /*Verify the result*/
        if (val3 != (val1 + val2)) {
            handle_error();
        }


        delete_list(head1);
        delete_list(head2);
        delete_list(result);
    }

    printf("Test passed\n");
    return 0;
}

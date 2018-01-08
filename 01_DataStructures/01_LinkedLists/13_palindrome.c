/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_ELEMENTS_IN_LIST (10)

struct node
{
    char data;
    struct node *next;
};

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


/*
head - the first element in the list to be reversed
Return value - new head to the reversed link list
*/
struct node* reverse_linked_list(struct node *head)
{
    struct node *cur_node = head;
    struct node *prev_node = NULL;
    struct node *temp_node;

    while (cur_node) {
        /*Store the next node in a temporary variable*/
        temp_node = cur_node->next;

        /*Reverse the link so that current node points to the previous node*/
        cur_node->next = prev_node;

        /*Update the previous node to the current node */
        prev_node = cur_node;

        /*Proceed to the next node in the original list*/
        cur_node = temp_node;
    }

    /*
    Once the list has been reversed, prev_node will be
    pointing to the new head. So return it
    */
    return prev_node;
}



/* 
head: first node of linked list.
Returns: 1 if linked list is a palindrome, 0 otherwise
*/
int is_list_palindrome(struct node *head)
{
    struct node *p, *q, *r, *temp;
    int i, length, is_palindrome;

    if (!head)
        return 0;

    /*Advance p by two nodes and q by one node in each loop.
    So when p reaches the end of linked list, q will point to middle of 
    the linked list*/
    p = q = head;
    length = 0;
    while (p != NULL) {
        ++length;
        p = p->next;
        if (p) {
            ++length;
            p = p->next;
        }

        if (p) {
            q = q->next;
        }
    }

    /*Reverse the second half of the linked list*/
    temp = r = reverse_linked_list(q->next);
    p = head;

    /*Compare first half with reverse of second half*/
    is_palindrome = 1;
    for (i = 0; i < length / 2; ++i) {
        if (p->data != r->data) {
            is_palindrome = 0;
            break;
        }
        p = p->next;
        r = r->next;
    }

    /*Reverse the second half of linked list to get back original 
    linked list*/
    reverse_linked_list(temp);
 
    return is_palindrome;
}






struct node* construct_list(int num_elements, const char *str)
{
    int i;
    struct node* head = NULL, *new_node;

    if (str == NULL)
        return NULL;

    for (i = 0; i < num_elements; ++i) {
        new_node = (struct node*) calloc(1, sizeof(struct node));
        new_node->data = str[num_elements - 1 - i];
        new_node->next = head;
        head = new_node;
    }

    return head;
}

void print_list(struct node *head)
{
    struct node *cur_node = head;

    while (cur_node) {
        printf("%c", cur_node->data);
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


void test(const char *str, int expected_result)
{
    struct node *head;
    int result;

    /*Construct the list based on the given string*/
    head = construct_list(strlen(str), str); 

    /*Check if list is palindrome*/
    result = is_list_palindrome(head);

    print_list(head);
    if (result)
        printf(" ----> is palindrome \n");
    else
        printf(" ----> is not palindrome \n");

    /*Verify the result*/
    if (result != expected_result)
        handle_error();

    delete_list(head);

    printf("______________________________________\n");
}


int main()
{
    test("a", 1);
    test("abba", 1);
    test("level", 1);
    test("Hello", 0); 

    printf("Test passed\n");
    return 0;
}

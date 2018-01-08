/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdlib.h>
#include <iostream>
#include <stack>
#include <exception>

using namespace std;

#define MAX_NUM_STACK_ELEMS (100)
#define MAX_VALUE   (10)

#define STATUS_OK (0)


void handle_error(void)
{
    cout << "Test failed\n";
    exit(1);
}





/*
main_stack: the main stack
min_stack: the additional stack for getting the minimum element
data_to_add: data to be added to the stack
*/
void add_element(stack<int>& main_stack, stack<int>& min_stack, int data_to_add)
{
    /*Push the node being inserted onto the main stack*/
    main_stack.push(data_to_add);

    /*
    If the min_stack is empty or the data being inserted is <=
    to the top of the min_stack, then add the data to the min_stack
    */
    if (min_stack.empty() || data_to_add <= min_stack.top()) {
        min_stack.push(data_to_add);
    }
}






/*
main_stack: the main stack
min_stack: the additional stack for getting the minimum element
Return value: data at the top of the main stack, -1 if the main stack is empty
*/
int remove_element(stack<int>& main_stack, stack<int>& min_stack)
{
    int popped_element, min_val;

    /*If main stack is empty we can't remove element*/
    if (main_stack.empty())
        throw exception();

    /*Remove the topmost element from the main stack*/
    popped_element = main_stack.top();
    main_stack.pop();

    /*Peek at the minimum value, which is stored at the top of the min_stack*/
    min_val = min_stack.top();

    /*
    If value popped from the main stack matches the value at the top 
    of min_stack, then remove the topmost element from the min_stack
    */
    if (popped_element == min_val)
        min_stack.pop();

    return popped_element;
}




int find_smallest(int number_array[], int max_index)
{
    int i = 0;
    int smallest = 0xFFFFFFF;

    for (i = 0; i <= max_index; ++i) {
        if (smallest > number_array[i]) {
            smallest = number_array[i];
        }
    }

    return smallest;
}


void test_stack()
{
    struct stack<int> main_stack, min_stack;
    int min_val;
    int num_elems, j;
    int number_array[MAX_NUM_STACK_ELEMS];
    int smallest_element;



    /*Test for different sizes of the stacks*/
    for (num_elems = 0; num_elems <= MAX_NUM_STACK_ELEMS; ++num_elems) {

        for (j = 0; j < num_elems; ++j) {
            /*Generate a random value and store in number_array*/
            number_array[j] = rand() % MAX_VALUE;

            /*Add the value to the main_stack and min_stack*/           
            add_element(main_stack, min_stack,  number_array[j]);

            /*Peek the minimum value from the min_stack*/
            min_val= min_stack.top();

            /*Verify if the minimum value given by min_stack is correct*/
            smallest_element = find_smallest(number_array, j);
            if (min_val != smallest_element) {
                handle_error();
            }
        }

        for (j = 0; j < num_elems; ++j) {
            /*Peek the minimum value from the min_stack*/
            min_val = min_stack.top();

            /*Verify if the minimum value given by min_stack is correct*/
            smallest_element = find_smallest(number_array, num_elems - 1 - j);
            if (min_val  != smallest_element) {
                handle_error();
            }

            /*Remove an element from the stack*/
            remove_element(main_stack, min_stack);
        }

        /*Verify that both min_stack and main_stack are empty*/
        if (!min_stack.empty() || !main_stack.empty())
            handle_error();

        /*Trying to remove an element from empty stack should throw an exception*/
        bool caught_exception = false;
        try {
            remove_element(main_stack, min_stack);
        } catch (exception e) {
            caught_exception = true;
        }

        if (!caught_exception)
            handle_error();
    }

    cout << "Test passed \n";

}




int main()
{
    test_stack();

    return 0;
}

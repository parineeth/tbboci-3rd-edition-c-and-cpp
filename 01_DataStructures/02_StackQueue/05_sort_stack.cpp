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


#define MAX_NUM_STACK_ELEMS (10)

#define MAX_VALUE (20)

void handle_error(void)
{
    cout << "Test failed\n";
    exit(1);
}



/*
Input elements are stored in original_stack. At the end of the operation, 
original_stack will be empty and sorted stack will have elements in sorted order
*/
void stack_sort(stack<int>& original_stack, stack<int>& sorted_stack) {
    int e1, e2;

    while (!original_stack.empty()) {
        e1 = original_stack.top();
        original_stack.pop();
        
        /*If sorted stack is empty OR e1 <= top element of  
        sorted stack, then push e1 onto the sorted stack */
        if (sorted_stack.empty()) {
            sorted_stack.push(e1);
            continue;
        } 
    
        e2 = sorted_stack.top();
        if (e1 <= e2) {
            sorted_stack.push(e1);
            continue;
        }
        
        /*While e1 > top element of sorted stack, remove the top 
        element of sorted stack and push it onto the original stack. 
        */
        while (!sorted_stack.empty()) {
            e2 = sorted_stack.top();
            if (e1 > e2) {
                sorted_stack.pop();
                original_stack.push(e2);
            } 
            else {
                break;
            }
        }
        sorted_stack.push(e1); /*Push e1 onto the sorted stack */
    }
}
 



void test_stack()
{
    struct stack<int> original_stack, sorted_stack;
    int num_elems, j, popped_value;
    int number_array[MAX_NUM_STACK_ELEMS];
    int prev_data;


    /*Test for different sizes of the stack*/
    for (num_elems = 0; num_elems <= MAX_NUM_STACK_ELEMS; ++num_elems) {

        for (j = 0; j < num_elems; ++j) {
            number_array[j] = rand() % MAX_VALUE;
            original_stack.push(number_array[j]);
        }

        /*Sort the stack. The sorted results will be in sorted_stack*/
        stack_sort(original_stack, sorted_stack);

        cout << "Sorted stack contents are : \n";
        prev_data = -1;
        for (j = 0; j < num_elems; ++j) {
            /*Pop an element from the sorted stack*/            
            popped_value = sorted_stack.top();
            sorted_stack.pop();
            cout << popped_value << endl;

            /*Verify if the data in stack is in ascending order*/
            if (prev_data > popped_value) {
                handle_error();
            }

            prev_data = popped_value;
        }
        cout << "\n_________________________________________________\n";

    }

    cout << "Test passed \n";

}



int main()
{
    test_stack();
    return 0;
}

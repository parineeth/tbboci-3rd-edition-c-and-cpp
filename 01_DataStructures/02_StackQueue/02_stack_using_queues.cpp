/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdlib.h>
#include <iostream>
#include <queue>
#include <exception>

using namespace std;


template <class T> class StackUsingQueues 
{
    private:
    queue<T> *q1;
    queue<T> *q2;

    public:
    StackUsingQueues() { 
        q1 = new queue<T>();
        q2 = new queue<T>();
    }

    ~StackUsingQueues() {
        delete q1;
        delete q2;
    }

    
    bool empty() {
        /*Stack is empty only if both queues are empty*/
        if (q1->empty() && q2->empty())
            return true;

        return false;
    }


    void push(T new_element) {
        /*Add element to the end of queue q1*/
        q1->push(new_element);
    }


    T pop() {
        /*If stack is empty, then throw an exception*/
        if (empty())
            throw exception();

        T e;
        /*Remove all elements from q1 and add it to q2 except the last item*/
        while (q1->size() > 1) {
            e = q1->front();
            q1->pop();
            q2->push(e);
        }

        /*Remove the last element in q1. It will contain the top of stack*/
        e = q1->front();
        q1->pop();

        /*Swap the queues q1 and q2*/
        queue<T> *temp = q1;
        q1 = q2;
        q2 = temp;

        return e; /*Return the top of the stack*/
    }

};





int MAX_NUM_ELEMS = 10;

void handle_error() 
{
    cout << "Test failed";
    exit(1);
}

void test() 
{
    StackUsingQueues<int> s ;
    int num_elems, j, expected_val;
    int output;

    /*Test for different number of elements in the stack*/
    for (num_elems = 0; num_elems <= MAX_NUM_ELEMS; ++num_elems) {

        /*Add all the elements to the stack*/
        for (j = 0; j < num_elems; ++j) {
            s.push(j);
        }

        cout << "Stack size = " << num_elems << ", Elements are : " << endl;

        /*Remove one element at a time from the stack and print it*/
        for (j = 0; j < num_elems; ++j) {
            output = s.pop();

            expected_val = num_elems - 1 - j;
            if (output != expected_val) {
                handle_error();
            }
            cout << output << endl;
        }

        /*Stack is now empty. Trying to remove an element now raises an exception*/
        bool caught_exception = false;
        try {
            s.pop();
        } catch (exception e) {
            caught_exception = true; 
        }
    
        if (!caught_exception)
            handle_error();


        cout << endl;
        cout << "__________________________________________" << endl;   
        
    }

}

int main() 
{
    test();
    cout << "Test passed " << endl;
    return 0;
}














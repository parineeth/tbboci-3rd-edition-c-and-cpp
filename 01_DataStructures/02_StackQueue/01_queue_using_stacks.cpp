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


template <class T> class QueueUsingStacks 
{
    private:
    stack<T> s1;
    stack<T> s2;

    public:
    QueueUsingStacks() {

    }

    void add(T new_element) {
        /*Add elements only to stack s1*/
        s1.push(new_element);
    }

    T remove() {
        T e;
        if(s2.empty()) {
            /*We remove elements only from stack s2. So
            if s2 is empty, then pop all the elements from s1 and  
            push them into s2.*/
            while(!s1.empty()) {
                e = s1.top();
                s1.pop();
                s2.push(e);
            }
        }

        if (s2.empty())
            throw exception();
        
        /*If s2 is not empty, then remove the element from top of s2.
        This element corresponds to the head of the queue*/
        e = s2.top();
        s2.pop();
        return e;
    }

    bool empty() {
        /*Queue is empty only if both stacks are empty*/
        if (s1.empty() && s2.empty())
            return true;
        return false;
    }
    
};





int MAX_NUM_QUEUE_ELEMS = 10;

void handle_error() 
{
    cout << "Test failed";
    exit(1);
}

void test() 
{
    QueueUsingStacks<int> q ;
    int num_elems, j, expected_val;
    int output;

    /*Test for different number of elements in the queue*/
    for (num_elems = 0; num_elems <= MAX_NUM_QUEUE_ELEMS; ++num_elems) {

        /*Add all the elements to the queue*/
        for (j = 0; j < num_elems; ++j) {
            q.add(j);
        }

        cout << "Queue size = " << num_elems << ", Elements are : ";

        /*Remove one element at a time from the queue and print it*/
        for (j = 0; j < num_elems; ++j) {
            output = q.remove();

            expected_val = j;
            if (output != expected_val) {
                handle_error();
            }
            cout << output << " ";
        }

        /*Queue is now empty. Trying to remove an element now raises an exception*/
        bool caught_exception = false;
        try {
            q.remove();
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














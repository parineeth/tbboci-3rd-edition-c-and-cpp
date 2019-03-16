/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

/*This is an older version of the Circular Queue implementation.
There is no bug in this implementation. However there is a more simpler
implementation possible. Please refer to 06_circular_queue.cpp
for the simpler implementation*/

#include <stdlib.h>
#include <iostream>
#include <exception>

using namespace std;

#define MAX_NUM_QUEUE_ELEMS (10)

void handle_error(void)
{
    cout << "Test failed\n";
    exit(1);
}






template <class T> class queue
{
    private:
    int head; /*index of the first element in queue. -1 if queue is empty*/
    int tail; /*index of last element in queue. -1 if queue is empty*/
    int count; /*Number of elements currently present in the queue*/
    int max_size; /*Maximum number of elements that can be stored in the queue*/
    T *buffer; /*buffer for storing elements */

    public:

    queue():head(-1), tail(-1), count(0), max_size(1) {
        buffer = new T[max_size];
    }

    ~queue() {
        delete [] buffer;
    }

    int add(int new_element) {
        if (count == max_size) {
            /*If the queue is full, then resize the queue*/
            T *new_buffer = new T[max_size * 2];
            int old_pos = head;
            int new_pos = 0;

            /*Copy from the old queue buffer to the new buffer*/
            while (new_pos < count) {
                new_buffer[new_pos] = buffer[old_pos];
                ++new_pos;
                old_pos = (old_pos + 1) % max_size;
            } 

            delete [] buffer;
        
            buffer = new_buffer;
            head = 0;
            tail = count - 1;
            max_size = max_size * 2;
        }

        /*Advance the tail and insert the element at the tail of the queue*/
        tail = (tail + 1) % max_size;
        buffer[tail] = new_element;

        if (count == 0)
            head = tail;

        count++;
    
        /*Return the result code indicating success*/
        return 0;
    }

    T remove() {
        T removed_element;

        /*Can't remove an item from an empty queue*/
        if (count <= 0)
            throw exception();

        removed_element = buffer[head];

        if (head == tail) {
            /*There was only 1 item in the queue and that item has 
            been removed. So reinitialize head and tail to -1*/
            head = -1;
            tail = -1;
        } else {
            /*Advance the head to the next location*/
            head = (head + 1) % max_size; 
        }

        count--;

        return removed_element;
    }

    void print_queue() {
        int i, pos;
    
        cout << "Queue: ";
        pos = head;
        for (i = 0; i < count; ++i) {
            cout << buffer[pos] << " ";
            pos = (pos + 1) % max_size;
        }

        cout << "\n___________________________________________________\n";
    }

};












void test()
{
    class queue<int> q;
    int num_elems, i, result;


    /*Test for different number of elements in the circular queue*/
    for (num_elems = 0; num_elems <= MAX_NUM_QUEUE_ELEMS; ++num_elems) {

        /*Add elements to the queue*/
        for (i = 0; i < num_elems; ++i) {
            q.add(i);
            cout << "Inserting element " << i  << "\n";
            q.print_queue();
        }

        /*Remove all elements from the queue*/
        for (i = 0; i < num_elems; ++i) {
            result = q.remove();

            cout << "Removing element " << result << " from queue\n";
            q.print_queue();

            if (result != i) {
                handle_error();
            }
        }

        bool caught_exception = false;
        /*The queue is now empty. So trying to remove an element should return an error*/
        try {
            q.remove();
        } catch(exception e) {
            caught_exception = true;
        }

        if (!caught_exception) {
            handle_error();
        }
    }


}


int main()
{
    test();
    cout << "Test passed \n";

    return 0;
}

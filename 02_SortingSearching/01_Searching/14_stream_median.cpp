/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <stdlib.h>

using namespace std;

#define MAX_NUM_TESTS (10)
#define MAX_NUM_ELEMS (10)
#define MAX_VALUE     (100)


void handle_error(void)
{
    cout << "Test failed\n";
    exit(1);
}

/*
min_heap: priority queue for storing the larger half of numbers in the stream
max_heap: priority queue for storing the smaller half of numbers in the stream
cur_value: value of the current item in the stream 
Return value: Median of the stream 
*/
int get_median(priority_queue<int, vector<int>, greater<int> >& min_heap,
        priority_queue<int, vector<int>, less<int> >& max_heap,
        int cur_value)
{
    /*If min_heap is empty, add the current value to min_heap.
    If min_heap is non-empty, the top of min_heap will contain the smallest
    among the larger half of numbers in the stream. So if current value is 
    larger than the top of min_heap, then add it to min_heap otherwise add 
    it to max_heap
    */
    if (min_heap.empty()) 
        min_heap.push(cur_value);
    else if (cur_value >= min_heap.top())
        min_heap.push(cur_value);
    else
        max_heap.push(cur_value);


    /*If min_heap has more than 1 element than the max_heap, move the top 
    of min_heap into the max_heap and vice versa. */
    if (min_heap.size() > max_heap.size() + 1) {
        max_heap.push(min_heap.top());
        min_heap.pop();
    } else if (max_heap.size() > min_heap.size() + 1) {
        min_heap.push(max_heap.top());
        max_heap.pop();
    }

    int median;

    /*If both heaps are of the same size, then the median will be the 
    average of the top element in the two heaps. Otherwise the median is 
    the top of the heap with more elements
    */
    if (min_heap.size() == max_heap.size()) {
        median = (min_heap.top() + max_heap.top()) / 2;
    } else if (min_heap.size() > max_heap.size()) {
        median = min_heap.top();
    } else {
        median = max_heap.top();
    }

    return median;
}

void print_array(int a[], int length) 
{
    int i;
    
    for (i = 0; i < length; ++i) {
        cout << a[i] << " ";
    }
    
    cout << endl;
}


int cmp_function(const void *p1, const void *p2)
{
    int *x = (int*)p1;
    int *y = (int*)p2;

    if (*x < *y)
        return -1;
    else if (*x == *y)
        return 0;
    else 
        return 1;
}


void sort(int b[], int length)
{
    /*Sort the elements in ascending order*/
    qsort(b, length, sizeof(int), cmp_function);
}


int sort_and_get_median(int a[], int length)
{
    int i, median, middle_pos;
    int b[MAX_NUM_ELEMS];

    /*Copy the values of a into b as we don't want to change the contents of a*/
    for (i = 0; i < length; ++i) {
        b[i] = a[i];
    }

    sort(b, length);

    cout << "Sorted : " ;
    print_array(b, length);

    middle_pos = length / 2;

    if (length % 2 == 0) {
        median = (b[middle_pos - 1] + b[middle_pos]) / 2;
    } else {
        median = b[middle_pos];
    }

    return median;
}


void generate_array(int a[], int length)
{
    int i;
    
    for (i = 0; i < length; ++i) {
        a[i] = rand() % MAX_VALUE;
    }
}


void test()
{
    int a[MAX_NUM_ELEMS];
    int i, length;
    priority_queue<int, vector<int>, greater<int> > min_heap;
    priority_queue<int, vector<int>, less<int> > max_heap;
    int median, expected_result;
    

    /*Randomly pick the number of elements*/
    length = 1 + rand() % MAX_NUM_ELEMS;

    /*Generate numbers in the array */
    generate_array(a, length);


    for (i = 0; i < length; ++i) {
        /*Go on adding one element at a time and finding the median*/
        cout << "Stream : ";
        print_array(a, i+1);

        /*Find the median using the efficient technique*/
        median = get_median(min_heap, max_heap, a[i]);

        /*Find the median using sorting*/
        expected_result = sort_and_get_median(a, i+1);

        cout << "Median = " << median << endl;

        if (median != expected_result)
            handle_error();

        cout << "_________________________________________________\n";
        
    }

    
    
}


int main()
{
    int i;

    for (i = 0; i < MAX_NUM_TESTS; ++i) {
        test();
    }

    cout << "Test passed\n";
    return 0;
    
}



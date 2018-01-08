/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdlib.h>
#include <iostream>
#include <deque>

using namespace std;


#define MAX_NUM_STACK_ELEMS (100)
#define MAX_VALUE   (10)

void handle_error(void)
{
    cout << "Test failed\n";
    exit(1);
}


void print_array(int a[], int n)
{   
    int i;

    for (i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}


void compare(int result[], int expected[], int n)
{
    int i;
    for (i = 0; i < n; ++i) {
        if (result[i] != expected[i])
            handle_error();
    }
}



/*
a: array for which we have to find the maximum in every window of size k
n: number of elements in the array
k: size of the window
dq: double ended queue that stores array indices
max: array that contains the result (maximum in every window of size k)
*/
void find_window_max(int a[], int n, int k, deque<int>& dq, int max[])
{
    int i, pos;

    pos = 0;
    for (i = 0; i < n ; ++i) {
        /*Remove the elements outside the current window from 
        front of dequeue*/
        while (!dq.empty() && (dq.front() + k <= i))
            dq.pop_front();

        /*Remove all elements that are smaller than or equal to current 
        element from the rear of the dequeue */
        while (!dq.empty() && a[i] >= a[dq.back()] )
            dq.pop_back();

        /*Push the index of current element into the end of the dequeue*/
        dq.push_back(i);

        if (i >= k-1) {
            /*Front of dequeue has index of maximum element 
            for the current window*/
            max[pos] = a[dq.front()];
            ++pos;
        }
    }
}



void test_01()
{
    int a[12] = {2, -1, 4, 3, 2, 6, 0, 7, 8, 10, 3, 2};
    int result[12];
    int expected1[] = {2, -1, 4, 3, 2, 6, 0, 7, 8, 10, 3, 2};
    int expected2[] = {2, 4, 4, 3, 6, 6, 7, 8, 10, 10, 3};
    int expected3[] = {4, 4, 4, 6, 6, 7, 8, 10, 10, 10};
    deque<int> dq;
    int n, k, result_size;

    cout << "Input                  : ";
    print_array(a, 12);

    n = 12;
    for (k = 1; k <= 3; ++k) {
        find_window_max(a, n, k, dq, result);

        result_size = n - k + 1;

        cout << "Max in window of size " << k << ": "; 
        print_array(result, result_size);

        if (k == 1)
            compare(result, expected1, result_size);
        else if (k == 2)
            compare(result, expected2, result_size);
        else if (k == 3)
            compare(result, expected3, result_size); 
    }


}


int main()
{
    test_01();

    cout << "Test passed\n";
    return 0;
}

/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdlib.h>
#include <iostream>
#include <exception>
#include <vector>


using namespace std;



void handle_error(void)
{
    cout<<("Test failed\n");
    exit(1);
}

/* Helper function that performs binary search on an array of unknown length
a: vector which should be searched
x: element which we are trying to find
low: start position of region in array for searching
high: end position of region in array for searching 
*/
int binary_search(vector<int>& a, int x, int low, int high)
{
    int value, mid;

    while (low <= high) {
        try {
            mid = (low + high) / 2;

            /*Use a.at(mid) instead of a[mid] since at 
            function throws an exception if mid crosses the bounds*/
            value = a.at(mid);

            if (value == x)
                return mid;
            else if (value > x)
                high = mid - 1;
            else 
                low = mid + 1;
        } 
        catch(exception& e) {
            /*mid has crossed the boundary of the array. So reduce 
            the search region to (low, mid - 1)*/
            high = mid - 1;
        }
            
    }

    return -1;
}


/* Main function for performing search on array whose length is not known
a: input vector
x: item to be searched
Returns: if x is found, position of x is returned, otherwise -1 is returned
*/
int search(vector<int>& a, int x)
{
    int value, low, high;

    /*Perform exponential search to first find upper bound. Start with
    high = 0 and then increase high to 1, 2, 4, 8, 16 and so on*/
    low = high = 0;
    while (1) {
        try {
            /*Use a.at(high) instead of a[high] since at 
            function throws an exception if high crosses bounds*/
            value = a.at(high);

            if (value == x) 
                return high; /*We found the element x*/
            else if (value > x) 
                break;/*We found the range (low, high) to search*/
                        
            low = high + 1;

            if (high == 0)
                high = 1;
            else
                high = high * 2;
        }
        catch (exception& e) {
            /*We have crossed the boundary of the array. So we have 
            found the upper bound for high. */
            break;
        }
    } 
    
    /*Perform binary search in range(low, high). Note that high may still be
    outside the array bounds*/
    return binary_search(a, x, low, high);
}


void test(int length, int x, int expected_result)
{
    vector<int> a;
    int i, result;
    

    for (i = 0; i < length; ++i) {
        a.push_back(i);
    }
    
    result = search(a, x);

    if (length)
        cout<<"Location of "<< x << " in vector [0 to " << length - 1 << "] is " << result << "\n";
    else
        cout<<"Location of "<< x << " in empty vector is " << result << "\n";

    if (result != expected_result)
        handle_error();
}


int main()
{
    test(20, 0, 0);
    test(20, 15, 15); 
    test(20, 19, 19);
        
    test(20, 100, -1);
    test(20, -1, -1);

    test(0, 0, -1);

    cout<<"Test passed\n" << endl << flush;
    return 0;
}


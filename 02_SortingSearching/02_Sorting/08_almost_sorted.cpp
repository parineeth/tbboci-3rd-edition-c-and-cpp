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

int min(int a, int b)
{
    return (a < b) ? a : b;
}


/*
a: almost sorted array that should be fully sorted
length: number of elements in the array
k: max distance that any element should be moved so that array becomes sorted
*/
void sort_almost_sorted_array(int a[], int length, int k)
{
    priority_queue <int, vector<int>, greater<int> > min_heap;

    int read_pos = 0, write_pos = 0;

    /*Fill in the first k values into the min_heap. If length is less than k
    then we have to fill in only length number of elements */
    for (read_pos = 0; read_pos < min(k, length); ++read_pos) {
        min_heap.push(a[read_pos]);
    }

    /*Add the element a[read_pos] to the heap and then pop out a value.  
    Value popped from heap will contain the next smallest value. Add the  
    value popped from the heap back into the array at the write position*/
    while (read_pos < length) {
        min_heap.push(a[read_pos]);
        a[write_pos] = min_heap.top();
        min_heap.pop();

        read_pos++;
        write_pos++;
    }

    /*Pop out the remaining elements in the heap and store them back 
    into the array*/
    while (!min_heap.empty()) {
        a[write_pos] = min_heap.top();
        min_heap.pop();

        ++write_pos;
    }
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


void sort(int a[], int length)
{
    /*Sort the elements in ascending order*/
    qsort(a, length, sizeof(int), cmp_function);
}




void generate_array(int a[], int length, int k)
{
    int i, index1, index2;
    int max_num_regions, region_nr;
    int temp, num_swaps;

    /*We have to generate values in the array, so that it is almost sorted
    The maximum distance that any element should be moved so that array becomes
    sorted is k.*/
    
    for (i = 0; i < length; ++i) {
        a[i] = rand() % MAX_VALUE;
    }

    /*First completely sort the array*/
    sort(a, length);

    /*Divide the array into regions of the size k*/
    max_num_regions = (length + k - 1) / k;

    for (region_nr = 0; region_nr < max_num_regions; ++region_nr) {
        /*Within each region of the array, perform k random swaps*/
        for (num_swaps = 0; num_swaps < k; ++num_swaps) {
            index1 = (region_nr * k) + rand() % k;
            index2 = (region_nr * k) + rand() % k;
    
            if (index1 < length && index2 < length) {
                temp = a[index1];
                a[index1] = a[index2];
                a[index2] = temp;
            }
        }
    }
}


void test()
{
    int length, k;
    int a[MAX_NUM_ELEMS];
    int b[MAX_NUM_ELEMS];
    int i;
    
    length = 1 + rand() % MAX_NUM_ELEMS;

    k = 1 + rand() % length;

    generate_array(a, length, k);

    cout << "K = " << k << endl;
    cout << "Input  : ";
    print_array(a, length);

    /*Copy values of a into b*/
    for (i = 0; i < length; ++i)
        b[i] = a[i];


    /*Sort the almost sorted array using the efficient technique*/
    sort_almost_sorted_array(a, length, k);

    cout << "Output : ";
    print_array(a, length);


    /*Perform normal sort on b*/
    sort(b, length);

    /*a and b should match*/
    for ( i = 0; i < length; ++i) {
        if (a[i] != b[i])
            handle_error();
    }

    cout << "_________________________________________________\n";
    
    
    
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



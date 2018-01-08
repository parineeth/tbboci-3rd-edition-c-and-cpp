/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NUM_TESTS (10)
#define MAX_NUM_ELEMS (10)
#define MAX_VALUE     (100)
#define MAX_INT       (999999)

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


void print_array(int a[], int length) 
{
    int i;
    
    for (i = 0; i < length; ++i) {
        printf("%d, ", a[i]);
    }
    
    printf("\n");
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



/*
a: sorted array containing elements in non-decreasing order
length: number of elements in the array
k: we are searching for the number immediately above k
Returns: the number immediately greater than k in the array if it exists,
        MAX_INT otherwise
*/
int find_next_higher(int a[], int length, int k)
{
    int low, high, mid, result;

    low = 0; 
    high = length - 1;

    result = MAX_INT;
    while (low <= high) {
        mid = (low + high) / 2;

        if (a[mid] > k) {
            result = a[mid]; /*update the result and continue*/
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    } 

    return result;
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
    int i, length, k, pos;
    int result, expected_result;

    /*Randomly decide the number of elements*/
    length = 1 + rand() % MAX_NUM_ELEMS;

    /*Generate an array having random elements*/
    generate_array(a, length);

    /*Sort the array in ascending order*/
    qsort(a, length, sizeof(int), cmp_function);

    printf ("Input : ");
    print_array(a, length);

    /*choose a random element k in the array*/
    pos = rand() % length;
    k = a[pos];

    /*Find the next higher element after k using binary search*/
    result = find_next_higher(a, length, k);

    printf("Next element greater than %d is %d\n", k, result);

    /*Find the next higher element after k using linear search*/
    expected_result = MAX_INT;
    for (i = pos + 1; i < length; ++i) {
        if (a[i] > k) {
            expected_result = a[i];
            break;
        }       
    }

    /*The linear search and binary search results should match*/
    if (result != expected_result)
        handle_error();
    
    printf("________________________________________________\n");

}


int main() 
{
    int i;

    for (i = 0; i < MAX_NUM_TESTS; ++i) {
        test();
    }

    printf("Test passed \n");
    return 0;
}

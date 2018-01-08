/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define MAX_NUM_ELEMENTS (10)
#define MAX_NUM_TESTS (10)


void handle_error()
{
    printf("Error occured\n");
    exit(1);
}



/*
a: array that has been sorted and rotated. There should NOT be any duplicates
n: number of elements in the array. Should be > 0
Return value: maximum element in the array
*/
int find_max(int a[], int n)
{
    int start, end, mid;

    assert(n > 0);
    start = 0;
    end = n - 1;

    while (a[start] > a[end]) {
        mid = (start + end) / 2;

        if (mid < n - 1 && a[mid] > a[mid + 1])
            return a[mid];

        if (a[mid] > a[end]) {
            start = mid;    /*max is in the region (mid, end)*/
        } else {
            end = mid - 1; /*max is in the region (start, mid - 1)*/
        }
    }

    return a[end];
}




void print_array(int a[], int n)
{
    int i;

    for (i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }

    printf("\n");
}

void generate_sorted_rotated_array(int a[], int n)
{
    int i, num_rotations, rotation_iter, temp;

    /*Generate the first random value*/
    a[0] = rand() % 10;
    if (n == 1)
        return;

    /*Generate the remaining random values in increasing sorted order without duplication*/
    for (i = 1; i < n; ++i) {
         a[i] = a[i - 1] + 1 + (rand() % 10);
    }

    /*Randomly decide the number of rotations*/
    num_rotations = rand() % n;

    /*Perform the rotations*/
    for (rotation_iter = 0; rotation_iter < num_rotations; ++rotation_iter) {
        temp = a[n-1];
        for (i = n - 1; i >= 1; --i) {
            a[i] = a[i - 1];
        }
        a[0] = temp;
    }

}


void test_01()
{
    int a[MAX_NUM_ELEMENTS];
    int i, n, test_result, actual_result;

    /*randomly decide the number of elements*/
    n = 1 + (rand() % MAX_NUM_ELEMENTS);

    /*Generate the sorted rotated array*/
    generate_sorted_rotated_array(a, n);

    printf("Input : ");
    print_array(a, n);

    /*Find the max using linear search*/
    test_result = -1;
    for (i = 0; i < n; ++i) {
        if (a[i] > test_result) {
            test_result = a[i];
        }
    }

    /*Find the max using binary search*/
    actual_result = find_max(a, n);

    printf("The maximum element is %d\n", actual_result);

    /*Compare the results of linear and binary search*/
    if (test_result != actual_result)
        handle_error();

    printf("_______________________________________________\n");
}



int main()
{
    int test_nr;

    for (test_nr = 0; test_nr < MAX_NUM_TESTS; ++test_nr) {
        test_01();
    }

    printf("Test passed \n");
    return 0;
}

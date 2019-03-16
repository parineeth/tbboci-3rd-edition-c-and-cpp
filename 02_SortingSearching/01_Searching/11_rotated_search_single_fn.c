/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NUM_ELEMENTS (10)
#define MAX_NUM_ITERATIONS (100)

void handle_error()
{
    printf("Error occured\n");
    exit(1);
}




/*
a: array that has been sorted and rotated. there should not be any duplicates
n: number of elements in the array, n > 0
x: element to be searched in the array
Return value: location of the element in array if found, -1 if not found
*/
int find_element(int a[], int n, int x)
{
    int start = 0, end = n - 1, mid;

    while (start <= end) {
        mid = (start+end)/2;

        if (x == a[mid]) {
            return mid;
        }

        /*Check which portion of the array has elements in sorted order*/
        if (a[start] <= a[mid]) {
            /*
            The lower portion (start, mid) is still sorted even after
            rotations. So use this portion for taking decisions
            */
            if (a[start] <= x && x < a[mid]) 
                end = mid - 1; /*search in region (start, mid-1)*/
            else
                start = mid + 1; /*search in region (mid+1, end)*/
        } else {
            /*
            The upper portion (mid, end) is sorted even after 
            rotations. So use this portion for taking decisions
            */
            if (a[mid] < x && x <= a[end]) 
                start = mid + 1; /*search in region (mid+1, end)*/
            else
                end = mid - 1; /*search in region (start, mid-1)*/
        }
    }

    return -1;
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
    int x, n, actual_result, index;

    /*randomly decide the number of elements*/
    n = 1 + (rand() % MAX_NUM_ELEMENTS);

    /*Generate the sorted rotated array*/
    generate_sorted_rotated_array(a, n);

    printf("Input : ");
    print_array(a, n);

    for (index = 0; index < n; ++index) {
        /*Pick the element at the index*/
        x = a[index];

        /*Search the element using binary search*/
        actual_result = find_element(a, n, x);

        printf("Location of %d is %d\n", x, actual_result);

        /*Verify the result*/
        if (actual_result != index)
            handle_error();
    }

    printf("_________________________________________\n");
}




int main()
{
    int test_nr;

    for (test_nr = 0; test_nr < MAX_NUM_ITERATIONS; ++test_nr) {
        test_01();
    }


    printf("Test passed \n");
    return 0;
}

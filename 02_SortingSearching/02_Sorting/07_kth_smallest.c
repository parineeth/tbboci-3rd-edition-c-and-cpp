/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


#define MAX_NUM_TESTS (100)
#define MAX_NUM_ELEMS (10)
#define MAX_VALUE     (100)
#define MAX_INT       (1000000)

void handle_error()
{
    printf("Test failed \n");
    exit(1);
}


void print_array(int a[], int length) 
{
    int i;
    
    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }
    
    printf("\n");
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* Helper function for finding the kth smallest element
* This function, picks a pivot and arranges all numbers smaller than pivot to
* the left of the pivot and all numbers greater than pivot to the right of pivot
* a: array on which the partition operation should be performed
* left: index of the starting element of the partition in the array
* right: index of the ending element of the partition in the array
* Return value: index of the pivot element of the partition
*/
int partition(int a[], int left, int right)
{
    int i, j, pivot;
    int num_elements = right - left + 1;
    int rand_pos = left + (rand() % num_elements);

    /*pick a random element and swap it with the last element*/
    swap(&a[rand_pos], &a[right]);
    
    /*The last element is treated as the pivot*/
    pivot = a[right];

    i = left;
    for (j = left; j <= right - 1; ++j) {
        if (a[j] <= pivot) {
            /*If i is not equal to j, then a[i] has a value
            greater than pivot and a[j] has a value less than
            pivot. So swap a[i] and a[j]*/
            if (i != j)
                swap(&a[i], &a[j]);
            ++i;
        } 
    }

    /*Swap a[i] and the pivot that is at a[right]*/
    swap(&a[i], &a[right]);

    return i; /*the pivot is now at i. So return i*/
}


/*Finds the kth smallest element in an array
a: array in which the kth smallest element should be found
length: number of elements in the array
k: value of k (can range from 0 to length - 1)
Returns: the kth smallest element
*/
int find_kth_smallest(int a[], int length, int k)
{
    int left = 0;
    int right = length - 1;

    while (k >= left && k <= right) {
        int pivot_pos = partition(a, left, right);
        
        if (pivot_pos == k)
            return a[pivot_pos];
        else if (pivot_pos < k) {
            left = pivot_pos + 1;
        } else {
            right = pivot_pos - 1;
        }
    }

    return MAX_INT; /*incorrect k value was specified*/
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
    qsort(a, length, sizeof(int), cmp_function);
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
    int k, length;
    int result, expected_result;


    /*Randomly decide the number of elements in the array*/
    length = 1 + rand() % MAX_NUM_ELEMS;
    k = rand() % length;

    /*Fill the array with random values*/
    generate_array(a, length);

    print_array(a, length);

    /*Find the result using an efficient technique*/
    result = find_kth_smallest(a, length, k);

    printf("K = %d, Kth smallest is %d\n", k, result);
    
    /*Find the expected result using sorting*/
    sort(a, length);
    expected_result = a[k];


    /*The two results should match*/
    if (result != expected_result ) {
        handle_error();
    }


    printf("________________________________________________\n");

}


int main() 
{
    int i;

    for (i = 0; i < MAX_NUM_TESTS; ++i) {
        test();
    }

    printf("Test passed\n");
    return 0;
}

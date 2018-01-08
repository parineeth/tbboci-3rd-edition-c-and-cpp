/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_ELEMENTS (10)
#define MAX_VALUE (10)
#define MAX_NUM_ITERATIONS (10)

void handle_error()
{
    printf("Error occured \n");
    exit(1);
}


/*
a: input array that has to be sorted. 
length: number of elements in the array
pivot_value: after sorting, all elements smaller than pivot will lie to the 
left of the pivot and all values that are greater than pivot will lie to the 
right of the pivot. If there are many pivot values, then they will occur 
together in the middle 
*/
void dutch_sort(int a[], int length, int pivot_value)
{
    int cur_pos, left_pos, right_pos;
    int temp;

    cur_pos = 0;
    left_pos = 0;
    right_pos = length - 1;

    while (cur_pos <= right_pos) {
        if (a[cur_pos] < pivot_value) {
            /*swap a[left_pos], a[cur_pos]*/
            temp = a[left_pos]; 
            a[left_pos] = a[cur_pos];
            a[cur_pos] = temp;
            
            ++left_pos; /*Advance the left fill location*/
            ++cur_pos;  /*Process the next element*/

        } else if (a[cur_pos] > pivot_value) {
            /*swap a[cur_pos],  a[right_pos];*/
            temp = a[cur_pos];
            a[cur_pos] = a[right_pos];
            a[right_pos] = temp;

            /*Advance the right fill location. Since we have newly 
            brought in an element from right_pos to cur_pos, we have 
            to process the new element. So don't advance cur_pos*/
            --right_pos; 

        } else {
            ++cur_pos; /*Process the next element*/
        }
    }
}

void print_array(int a[], int length) 
{
    int i;

    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }

    printf("\n");
}


void test(int a[], int length, int pivot_value)
{
    int i;

    printf("Pivot value = %d\n", pivot_value);

    printf("Before : ");
    print_array(a, length);

    /*Perform the sort*/
    dutch_sort(a, length, pivot_value);

    /*Verify the result of dutch sort */
    i = 0;
    /*All elements less than pivot should occur first*/
    while (i < length && a[i] < pivot_value)
        ++i;

    /*If there are one or more pivot values, they should come next*/
    while (i < length && a[i] == pivot_value)
        ++i;

    /*All elements greater than the pivot value should occur at the end*/
    while (i < length && a[i] > pivot_value)
        ++i;

    if (i != length)
        handle_error();

    printf("After  : ");
    print_array(a, length); 

    printf("_______________________________________________\n");
} 





int main()
{
    int a[MAX_NUM_ELEMENTS];
    int i, iter, length, pivot_value;

    /*Run several number of tests*/
    for (iter = 0; iter < MAX_NUM_ITERATIONS; ++iter) {

        /*Pick the number of elements in the array randomly*/
        length = 1 + (rand() % MAX_NUM_ELEMENTS);

        /*Randomly generate the elements in the array*/
        for (i = 0; i < length; ++i) {
            a[i] = rand() % MAX_VALUE;
        }
        
        /*Pick a random pivot*/
        i = rand() % length;
        pivot_value = a[i];
        
        test(a, length, pivot_value);
    }

    printf("Test passed\n");
    return 0;
}

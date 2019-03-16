/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_TESTS (10)
#define MAX_NUM_ELEMS (10)
#define MAX_ELEMENT_VALUE (100)

#define MIN_INT_VALUE (-1 * 0x7FFFFFFF)

void handle_error()
{
    printf("Error occured \n");
    exit(1);
}


int max(int a, int b)
{
    return (a > b ? a : b);
}



/* 
a: is the array of numbers for which the MCS should be found,
length: number of elements. Should >= 1
mcs_start_pos: the starting array index of the MCS is returned here
mcs_end_pos: the ending array index of the MCS is returned here 
Return value: Maximum continuous sum of the elements 
*/
int kadane_mcs(int a[], int length, int *mcs_start_pos, int *mcs_end_pos) {
    int i, max_local, max_global;
    int cur_start_pos;

    *mcs_start_pos = *mcs_end_pos = 0;
    cur_start_pos = 0; /*store the start position of the current window*/

    max_local = max_global = a[0];

    /*Traverse from the second element onwards*/
    for (i = 1; i < length; ++i) {
        max_local = max(a[i], a[i] + max_local);
        if (max_local == a[i])
            cur_start_pos = i; /*start a new window here*/

        /*Find the global maximum*/
        if (max_local > max_global) {
            max_global = max_local;
            *mcs_start_pos = cur_start_pos;
            *mcs_end_pos = i;
        }
    }

    return max_global;
}


int find_brute_force_mcs(int a[], int length)
{
    int cur_sum;
    int mcs = MIN_INT_VALUE;
    int start_elem, i;

    for (start_elem = 0; start_elem < length; ++start_elem) {
        cur_sum = 0;
        for (i = start_elem; i < length; ++i) {
            cur_sum += a[i];

            if (mcs < cur_sum) 
                mcs = cur_sum;
        }
    }


    return mcs;
}


void print_array(int a[], int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}


int main()
{
    int a[MAX_NUM_ELEMS];
    int test_nr, num_elems, i, algo_mcs, brute_force_mcs;
    int mcs_start_pos, mcs_end_pos, verify_sum;

    for (test_nr = 0; test_nr < MAX_NUM_TESTS; ++test_nr) {
        /*Pick a random number of elements*/
        num_elems = 1 + rand() % MAX_NUM_ELEMS;

        /*Generate random values into the array. */
        for (i = 0; i < num_elems; ++i) {
            a[i] = rand() % MAX_ELEMENT_VALUE;

            /*Some elements will be negative*/
            if (rand() % 2 == 0)
                a[i] = -1 * a[i];
        }

        printf("Input : ");
        print_array(a, num_elems);

        /*Find the maximum continuous sum*/
        algo_mcs = kadane_mcs(a, num_elems, &mcs_start_pos, &mcs_end_pos);

        printf("Max Continuous Sum = %d, MCS start position = %d, MCS end position = %d\n", 
            algo_mcs, mcs_start_pos, mcs_end_pos);

        verify_sum = 0;
        for (i = mcs_start_pos; i <= mcs_end_pos; ++i) {
            verify_sum += a[i];
        } 
        
        if (verify_sum != algo_mcs)
            handle_error(); 

        /*Find the maximum continuous sum using brute force*/
        brute_force_mcs = find_brute_force_mcs(a, num_elems);

        /*The two results should match*/
        if (algo_mcs != brute_force_mcs) {
            handle_error();
        }

        printf("______________________________________________\n");
    }

    printf("Test passed\n");

    return 0;
}

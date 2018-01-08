/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NUM_ELEMENTS 10


/*
a: array in which we need to find the longest increasing sequence
n: number of elements in the array. Should be >= 1
lis: the longest increasing sequence is returned in this array
Return value: length of the longest increasing sequence
*/
int find_lis(int a[], int n, int lis[])
{
    /*seq_length stores length of LIS for each position of array a*/
    int *seq_length = (int*) calloc(n, sizeof(int));

    /*prev_ix stores the index of previous element in the LIS sequence*/
    int *prev_ix = (int*) calloc(n, sizeof(int));

    int i, j, lis_length, lis_end;

    /*Each element by itself forms a sequence of length 1*/
    for (i = 0; i < n; ++i)
        seq_length[i] = 1;

    /*Find the LIS for each position in array a*/
    for (i = 1; i < n; ++i) {
        for (j = 0; j < i; ++j) {
            if ( a[j] < a[i] && seq_length[i] < seq_length[j] + 1 ) {
                seq_length[i] = seq_length[j] + 1;
                prev_ix[i] = j;
            }
        }
    }

    /*The longest LIS amongst all positions of array a will be the LIS  
    for the whole array*/
    lis_length = 1;
    lis_end = 0;
    for (i = 1; i < n; ++i) {
        if (lis_length < seq_length[i]) {
            lis_length = seq_length[i];
            lis_end = i;
        }
    }

    /*Use the prev_ix array to reconstruct the LIS for the whole array
    lis_end has the index of the last element in the LIS for whole array*/
    j = lis_end;
    for (i = lis_length - 1; i >= 0; --i) {
        lis[i] = a[j];
        j = prev_ix[j];
    }
    
    free(seq_length);
    free(prev_ix);

    return lis_length;
}



void print_array(int array[], int n)
{
    int i;

    for (i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }

    printf("\n");
}


void test_01()
{
    int lis_length;
    int lis[MAX_NUM_ELEMENTS];
    int input[MAX_NUM_ELEMENTS] = {6, 3, 2, 4, 5};
    int num_elems = 5;

    printf("Input : ");
    print_array(input, num_elems);

    lis_length = find_lis(input, num_elems, lis);

    printf("LIS : ");
    print_array(lis, lis_length);

    printf("___________________________________________\n");
}


void test_02()
{
    int lis_length;
    int lis[MAX_NUM_ELEMENTS];
    int input[MAX_NUM_ELEMENTS] = {2, 4, 3,  1, 7 , 7, 9 };
    int num_elems = 7;

    printf("Input : ");
    print_array(input, num_elems);

    lis_length = find_lis(input, num_elems, lis);

    printf("LIS : ");
    print_array(lis, lis_length);

    printf("___________________________________________\n");
}



int main()
{
    test_01();

    test_02();

    printf("Test passed\n");

    return 0;
}

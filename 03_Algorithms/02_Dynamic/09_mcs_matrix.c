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
#define MAX_NUM_ROWS 5
#define MAX_NUM_COLS 5

#define MIN_INT (-1 * 0x7FFFFFFF)

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
Return value: Maximum continous sum of the elements 
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

/*
matrix: non-empty input matrix for which we have to find the maximum sum
n_rows: number of rows in the matrix
n_cols: number of columns in the matrix
Return value: the sum of elements in the max sum sub-matrix in the input matrix
*/
int find_max_sum_matrix(int matrix[][MAX_NUM_COLS], int n_rows, int n_cols)
{
    int left_col, right_col, i, cur_sum, max_sum, start, end;

    /*create a temporary 1-D array which stores the result of column additions*/
    int *a = (int*) malloc(n_rows * sizeof(int)); 
    
    max_sum = MIN_INT;
    for (left_col = 0; left_col < n_cols; ++left_col) {
        /*We have chosen a left column. Initialize the temp array to 0*/
        for (i = 0; i < n_rows; ++i)
            a[i] = 0;

        /*Iterate through the right side columns which are >= left column*/
        for (right_col = left_col; right_col < n_cols; ++right_col) {
            
            /*Add elements in the current right column to temp array*/
            for (i = 0; i < n_rows; ++i) 
                a[i] += matrix[i][right_col];

            /*Find the maximum continuous sum of the 1-D array using 
            kadane algo. The start and end indices returned by kadane  
            algo will correspond to the start row and end row of the 
            2-D matrix*/
            cur_sum = kadane_mcs(a, n_rows, &start, &end);

            if (cur_sum > max_sum) {
                max_sum = cur_sum;
                
                /*The maximum sum sub-matrix is bounded between 
                col1 = left_col, col2 = right_col, row1 = start 
                row2 = end*/
            }
        }
    }

    free(a);

    return max_sum;
}



int find_brute_force_mcs(int matrix[][MAX_NUM_COLS], int n_rows, int n_cols)
{
    int start_row, start_col, end_row, end_col, i, j, cur_sum;
    int mcs = MIN_INT;

    /*Fix the start_row, end_row, start_col and end_col of the sub-matrix*/
    for (start_row = 0; start_row < n_rows; ++start_row) {
        for (end_row = start_row; end_row < n_rows; ++end_row) {
            for (start_col = 0; start_col < n_cols; ++start_col) {
                for (end_col = start_col; end_col < n_cols; ++end_col) {

                    /*Find the sum in the current sub-matrix*/
                    cur_sum = 0;
                    for (i = start_row; i <= end_row; ++i) {
                        for (j = start_col; j <= end_col; ++j) {
                            cur_sum += matrix[i][j];
                        }
                    }

                    if (cur_sum > mcs)
                        mcs = cur_sum;
                }
            }
        }
    }

    return mcs;
}


void print_matrix(int matrix[][MAX_NUM_COLS], int n_rows, int n_cols)
{
    int i, j;
    for (i = 0; i < n_rows; ++i) {
        for (j = 0; j < n_cols; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void test()
{
    int matrix[MAX_NUM_ROWS][MAX_NUM_COLS];
    int n_rows, n_cols, i, j, algo_mcs, brute_force_mcs;


    /*Pick a random number of rows*/
    n_rows = 1 + rand() % MAX_NUM_ROWS;

    /*Pick a random number of rows*/
    n_cols = 1 + rand() % MAX_NUM_COLS;

    /*Generate random values into the matrix */
    for (i = 0; i < n_rows; ++i) {
        for (j = 0; j < n_cols; ++j) {
            matrix[i][j] = rand() % MAX_ELEMENT_VALUE;

            /*Some elements will be negative*/
            if (rand() % 2 == 0)
                matrix[i][j] = -1 * matrix[i][j];
        }
    }

    printf("Input : \n");
    print_matrix(matrix, n_rows, n_cols);

    /*Find the maximum continuous sum*/
    algo_mcs = find_max_sum_matrix(matrix, n_rows, n_cols);

    printf("Max Continuous Sum = %d \n", algo_mcs);

    /*Find the maximum continuous sum using brute force*/
    brute_force_mcs = find_brute_force_mcs(matrix, n_rows, n_cols);

    /*The two results should match*/
    if (algo_mcs != brute_force_mcs) {
        handle_error();
    }

    printf("______________________________________________\n");

}



int main()
{
    int i;
    for (i = 0; i < MAX_NUM_TESTS; ++i)
        test();

    printf("Test passed\n");
    return 0;
}

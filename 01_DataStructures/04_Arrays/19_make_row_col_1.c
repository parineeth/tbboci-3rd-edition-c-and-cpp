/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


#define MAX_NUM_ROWS    (5)
#define MAX_NUM_COLS    (5)


void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

void print_matrix(int m[][MAX_NUM_COLS], int num_rows, int num_cols)
{
    int i, j;

    for (i = 0; i < num_rows; ++i) {
        for (j = 0; j < num_cols; ++j) {
            printf("%3d ", m[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}

void compare_matrix(int m[][MAX_NUM_COLS], int expected_result[][MAX_NUM_COLS], int nrows, int ncols)
{
    int i, j;

    for (i = 0; i < nrows; ++i) {
        for (j = 0; j < ncols; ++j) {
            if (m[i][j] != expected_result[i][j])
                handle_error();
        }
    }

}


/*m: 2d matrix to be processed
num_rows: number of rows in the matrix
num_cols: number of columns in the matrix (equal to MAX_NUM_COLS)
*/
void process_matrix(int m[][MAX_NUM_COLS], int num_rows, int num_cols)
{
    int i, j, is_1_in_first_row = 0, is_1_in_first_col = 0;

    /*Check if any cell in the first row is set to 1*/
    for (i = 0; i < num_rows; ++i)
        if (m[i][0]) {
            is_1_in_first_row = 1;
            break;
        }

    /*Check if any cell in first column is set to 1*/
    for (j = 0; j < num_cols; ++j)
        if (m[0][j]) {
            is_1_in_first_col = 1;
            break;
        }

    /*Scan the matrix. If m[i][0] is equal to 1 then, set m[i][0] to 1
    and set m[0][j] to 1*/
    for (i = 1; i < num_rows; ++i)
        for (j = 1; j < num_cols; ++j)
            if (m[i][j]) {
                m[i][0] = 1;
                m[0][j] = 1;
            }

    /*Mark the cells as 1 as indicated by m[i][0] and m[0][j]*/
    for (i = 1; i < num_rows; ++i)
        for (j = 1; j < num_cols; ++j)
            if (m[i][0] || m[0][j])
                m[i][j] = 1;

    /*If there was a 1 initially in first column, set 1 in all the cells 
    of first column*/
    if (is_1_in_first_col)
        for (i = 0; i < num_rows; ++i)
            m[i][0] = 1;

    /*If there was a 1 initially in first row, set 1 in all the cells 
    of the first row*/
    if (is_1_in_first_row)
        for (j = 0; j < num_cols; ++j)
            m[0][j] = 1;
}


void test_01()
{
    int m[][MAX_NUM_COLS] = {   
            {1, 0, 0, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        };

    int expected_result[][MAX_NUM_COLS] = {     
            {1, 1, 1, 1, 1},
            {1, 0, 1, 1, 0},
            {1, 1, 1, 1, 1},
            {1, 0, 1, 1, 0},
            {1, 0, 1, 1, 0}
        };

    printf("Input: \n");
    print_matrix(m, MAX_NUM_ROWS, MAX_NUM_COLS);


    process_matrix(m, MAX_NUM_ROWS, MAX_NUM_COLS);

    printf("Output: \n");
    print_matrix(m, MAX_NUM_ROWS, MAX_NUM_COLS);

    compare_matrix(m, expected_result, MAX_NUM_ROWS, MAX_NUM_COLS);


}




int main()
{
    test_01();

    printf("Test passed\n");
    return 0;
}

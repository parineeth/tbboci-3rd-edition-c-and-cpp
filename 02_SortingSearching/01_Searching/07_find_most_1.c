/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



#define NUM_COLS (6)

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


int find_first(int a[], int n, int x)
{
    int start, end, mid;

    start = 0;
    end = n - 1;

    while (start <= end) {
        mid = (start + end) / 2;

        if (a[mid] == x) {
            if (mid == 0 || a[mid - 1] != x)
                return mid;
            else
                end = mid - 1;

        } else if (a[mid] > x) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    return -1;
}


/*
a: array where each row is sorted and has only 0's and 1's
nrows: number of rows in the array
ncols: number of columns in the array (ncols is equal to NUM_COLS)
Returns: row number that has most ones, if no row has 1's then return -1
*/
int find_row_with_most_ones(int a[][NUM_COLS], int nrows, int ncols)
{
    int i, first_one_index;
    int cur_num_ones, max_num_ones;
    int max_row;

    max_row = -1;
    max_num_ones = 0;

    for (i = 0; i < nrows; ++i) {
        /*Find the position of the first 1 in the row*/
        first_one_index = find_first(a[i], ncols, 1);

        /*Compute number of 1's in row based on position of the first 1*/
        if (first_one_index == -1)
            cur_num_ones = 0; /*there are no 1's in the row*/
        else
            cur_num_ones = ncols - first_one_index;

        if (cur_num_ones > max_num_ones) {
            max_num_ones = cur_num_ones;
            max_row = i;
        }
    }

    return max_row;
}


void print_matrix(int m[][NUM_COLS], int num_rows, int num_cols)
{
    int i, j;

    for (i = 0; i < num_rows; ++i) {
        for (j = 0; j < num_cols; ++j) {
            printf("%3d ", m[i][j]);
        }
        printf("\n");
    }
}


void test_01()
{
    int result;
    int a[5][6] = {{1, 1, 1, 1, 1, 1},
                  {0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 1},
                  {0, 1, 1, 1, 1, 1},
                  {0, 0, 0, 0, 1, 1}
             };
    
    print_matrix(a, 5, 6);  

    result = find_row_with_most_ones(a, 5, 6);
    
    printf("\nRow with most ones = %d\n", result);

    if (result != 0)
        handle_error();

    printf("________________________________________________\n");

}


void test_02()
{
    int result;
    int a[5][6] = {{0, 0, 0, 0, 0, 1},
                  {0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 1},
                  {0, 1, 1, 1, 1, 1},
                  {0, 0, 0, 0, 1, 1}
             };

    print_matrix(a, 5, 6);  

    result = find_row_with_most_ones(a, 5, 6);

    printf("\nRow with most ones = %d\n", result);

    if (result != 3)
        handle_error();

    
    printf("________________________________________________\n");
}


int main()
{

    test_01();
    test_02();

    printf("Test passed\n");

    return 0;
}

/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define NOT_ALLOWED     (-1)
#define MAX_NUM_COLS    (5)
#define MAX_NUM_ROWS    (5)

void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

void print_matrix(int m[][MAX_NUM_COLS], int nrows, int ncols)
{
    int i, j;

    for (i = 0; i < nrows; ++i) {
        for (j = 0; j < ncols; ++j) {
            printf("%3d ", m[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}




/*
m: matrix that has to be navigated
cur_row: row of the current cell
cur_col: column of the current cell
num_paths: the total number of paths possible is returned here
*/
void navigate_maze(int m[][MAX_NUM_COLS], int cur_row, int cur_col, 
            int *num_paths)
{
    if (cur_row < 0 || cur_col < 0)
        return;

    if (m[cur_row][cur_col] == -1)
        return; /*We can't traverse this cell, so simply return*/

    if (cur_row == 0 && cur_col == 0) {
        /*We have reached the destination*/
        (*num_paths)++;
        return;
    }

    /*Try continuing the path by going to the cell in previous row*/
    navigate_maze(m, cur_row - 1, cur_col, num_paths);

    /*Try continuing the path by going to the cell in previous col*/
    navigate_maze(m, cur_row, cur_col - 1, num_paths);

    /*Try continuing the path by going to the diagonally above cell*/
    navigate_maze(m, cur_row - 1, cur_col - 1, num_paths);
}



int  GoldenNumberOfPaths(int m, int n)
{
   // If either given row number is first or given column number is first
   if (m == 1 || n == 1)
        return 1;

   return  GoldenNumberOfPaths(m-1, n) + GoldenNumberOfPaths(m, n-1)
           + GoldenNumberOfPaths(m-1,n-1);
}



void test_01()
{
    int num_paths, golden_num_paths;
    int m[MAX_NUM_COLS][MAX_NUM_COLS] = {   {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0}
                    };

    printf("Input: \n");
    print_matrix(m, MAX_NUM_ROWS, MAX_NUM_COLS);

    num_paths = 0;
    navigate_maze(m, MAX_NUM_ROWS - 1, MAX_NUM_COLS - 1, &num_paths);

    printf("Number of paths = %d\n", num_paths);

    golden_num_paths = GoldenNumberOfPaths(MAX_NUM_ROWS, MAX_NUM_COLS);

    printf("Golden number of paths = %d\n", golden_num_paths);

    if (num_paths != golden_num_paths)
        handle_error();
}




int main()
{
    test_01();

    printf("Test passed\n");
    return 0;
}

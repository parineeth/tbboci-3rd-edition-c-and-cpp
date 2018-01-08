/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_ROWS (5)
#define MAX_NUM_COLS (5)


#define INT_MAX (100000)

void handle_error()
{
    printf("Error occured \n");
    exit(1);
}


int min(int a, int b, int c)
{
    int smallest = a;
    
    if (b < smallest)
        smallest = b;

    if (c < smallest)
        smallest = c;

    return smallest; 
}

/*
a: non-empty 2D matrix in which we have to find the minimum cost path 
num_rows, num_cols: Number of rows and number of columns in the matrix
Return value: cost of the minimum path from (0, 0) to (num_rows-1, num_cols-1)
*/
int find_min_path(int a[][MAX_NUM_COLS], int num_rows, int num_cols)
{
    int i, j;
    int cost[MAX_NUM_ROWS][MAX_NUM_COLS];

    cost[0][0] = a[0][0];

    for (i = 1; i < num_rows; ++i) 
        cost[i][0] = cost[i-1][0] + a[i][0];

    for (j = 1; j < num_cols; ++j) 
        cost[0][j] = cost[0][j-1] + a[0][j];

    for (i = 1; i < num_rows; ++i) {
        for (j = 1; j < num_cols; ++j) {
            cost[i][j] = a[i][j] +
                min(cost[i-1][j], cost[i][j-1], cost[i-1][j-1]);
        }
    }
    
    return cost[num_rows - 1][num_cols - 1];
}


int min_path_r(int a[][MAX_NUM_COLS], int cur_row, int cur_col)
{
    if (cur_row < 0 || cur_col < 0)
        return INT_MAX;

    if (cur_row == 0 && cur_col == 0)
        return a[0][0];

    return a[cur_row][cur_col] + min(min_path_r(a, cur_row - 1, cur_col),
                      min_path_r(a, cur_row, cur_col - 1),
                      min_path_r(a, cur_row - 1, cur_col - 1));

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
}


void test()
{
    int a[][MAX_NUM_COLS] = {{5, 3, 1},
            {2, 6, 5},
            {9, 3, 1}};

    int result, expected_result;

    print_matrix(a, 3, 3);

    /*Find minimum path cost using dynamic programming*/
    result = find_min_path(a, 3, 3);

    /*Find minimum path cost using recursion*/
    expected_result = min_path_r(a, 2, 2);

    printf("Minimum cost of path = %d\n", result);

    /*The two results should match*/
    if (result != expected_result)
        handle_error();
    
}


int main()
{
    test();

    printf("Test passed\n");
    return 0;
}


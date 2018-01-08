/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_COLS (5)

/*
m: 2d matrix to be rotated by 90 degrees in clockwise direction
n: number of rows or cols in the matrix. n is equal to MAX_NUM_COLS
*/
void rotate_square_matrix_90(int m[][MAX_NUM_COLS], int n)
{
    int i, j, temp;
    int max_i, max_j ;

    /*max_i and max_j have the boundaries of the first quadrant*/
    max_i = (n/2) - 1;
    max_j = ((n+1)/2) - 1;

    for (i = 0; i <= max_i; ++i) {
        for (j = 0; j <= max_j; ++j) {

            /*Perform  a four way swap*/
            temp = m[i][j];

            m[i][j] = m[n - j - 1][i];

            m[n - j - 1][i] = m[n - i - 1][n - j - 1];

            m[n - i - 1][n - j - 1] = m[j][n - i - 1];

            m[j][n - i - 1] = temp;
        }
    }
}


void swap_row(int m[][MAX_NUM_COLS], int n)
{
    int i, j, temp;

    for (i = 0; i < n/2; ++i) {
        for (j = 0; j < n; ++j) {
            temp = m[i][j];
            m[i][j] = m[n-1-i][j];
            m[n-1-i][j] = temp;
        }
    }
}

void swap_column(int m[][MAX_NUM_COLS], int n)
{
    int i, j, temp;

    for (i = 0; i < n/2; ++i) {
        for (j = 0; j < n; ++j) {
            temp = m[i][j];
            m[i][j] = m[i][n-1-j];
            m[i][n-i-j] = temp;
        }
    }
}

void matrix_transpose(int m[][MAX_NUM_COLS], int n)
{
    int i, j, temp;

    for (i = 0; i < n ; ++i) {
        for (j = 0; j < i; ++j) {
            temp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = temp;
        }
    }
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



void test_01()
{
    int m[MAX_NUM_COLS][MAX_NUM_COLS] = {   {1, 2, 3, 4, 5},
                        {6, 7, 8, 9, 10},
                        {11, 12, 13, 14, 15},
                        {16, 17, 18, 19, 20},
                        {21, 22, 23, 24, 25}
                    };

    rotate_square_matrix_90(m, MAX_NUM_COLS);

    print_matrix(m, MAX_NUM_COLS, MAX_NUM_COLS);

}





int main()
{
    test_01();
    
    printf("Test passed\n");
    return 0;
}

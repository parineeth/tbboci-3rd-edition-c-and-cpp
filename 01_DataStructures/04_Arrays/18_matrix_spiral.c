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




/*
m: 2d matrix that should be printed spirally
num_rows: number of rows in the matrix
num_cols: number of columns in the matrix (num_cols is equal to MAX_NUM_COLS)
*/
void print_spiral(int m[][MAX_NUM_COLS], int num_rows, int num_cols)
{
    int r1 = 0, r2 = num_rows - 1;
    int c1 = 0, c2 = num_cols - 1;
    int cur_row, cur_col;

    while (r1 <= r2 && c1 <= c2) {
        /*Print row r1*/
        cur_row = r1;
        for (cur_col = c1; cur_col <= c2; ++cur_col) {
            printf("%d ", m[cur_row][cur_col]);
        }
        ++r1; /*Advance r1 to next row*/

        /*Print column c2*/
        cur_col = c2;
        for (cur_row = r1; cur_row <= r2; ++cur_row) {
            printf("%d ", m[cur_row][cur_col]);
        }
        --c2; /*Advance c2 to previous column*/

        if (r1 != r2) {
            /*Print row r2*/
            cur_row = r2;
            for (cur_col = c2; cur_col >= c1; --cur_col) {
                printf("%d ", m[cur_row][cur_col]);
            }
            --r2;   /*Advance r2 to previous row*/
        }

        if (c1 != c2) {
            /*Print column c1*/
            cur_col = c1;
            for (cur_row = r2; cur_row >= r1; --cur_row) {
                printf("%d ", m[cur_row][cur_col]);
            }
            ++c1; /*Advance c1 to next column*/
        }
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

    print_spiral(m, MAX_NUM_COLS, MAX_NUM_COLS);

}





int main()
{
    test_01();
    
    printf("Test passed\n");
    return 0;
}

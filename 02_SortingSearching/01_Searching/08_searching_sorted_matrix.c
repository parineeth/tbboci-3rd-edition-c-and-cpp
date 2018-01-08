/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_COLS (4)

void handle_error()
{
    printf("Error occured\n");
    exit(1);
}





/*
m: matrix to be searched
NUM_COLS: number of columns in the matrix
num_rows: number of rows in the matrix
x: element to search
Return value: 1 if element is present, 0 otherwise
*/
int search_matrix(int m[][NUM_COLS],  int num_rows, int x)
{
    int i, j;
    int is_found;

    i = 0;
    j = NUM_COLS - 1;
    is_found = 0;
    while (i < num_rows && j >= 0) {
        if (m[i][j] == x) {
            is_found = 1;
            break;
        } else if (m[i][j] < x) {
            ++i;    /*go to the row below*/
        } else {
            --j;    /*go to the previous column*/
        }
    }

    return is_found;
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

void print_result(int result, int x)
{
    if (result)
        printf("Found %d \n", x);
    else 
        printf("Could NOT Find %d \n", x);
}

void test(int m[][NUM_COLS], int x, int expected_result)
{
    int result = search_matrix(m, 4, x);
    
    print_result(result, x);

    if (result != expected_result)
        handle_error();
}

int main()
{
    int m[4][4] = { {10, 20, 30, 40},
                    {15, 25, 35, 45},
                    {27, 29, 37, 48},
                    {32, 33, 39, 50}
                  };

    print_matrix(m, 4, 4);

    test(m, 40, 1);
    test(m, 10, 1);
    test(m, 50, 1);
    test(m, 25, 1);
    test(m, 37, 1);
    test(m, 28, 0);

    printf("Test passed\n");

    return 0;
}

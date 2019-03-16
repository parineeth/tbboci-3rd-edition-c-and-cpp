#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_TESTS 100

#define MAX_NUM_ROWS 5
#define MAX_NUM_COLS 5


void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

void print_matrix(int m[][MAX_NUM_COLS], int n_rows, int n_cols)
{
    int i, j;
    for (i = 0; i < n_rows; ++i) {
        for (j = 0; j < n_cols; ++j) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
Helper function that indicates if we can enter the cell or not
*/
int can_enter_cell(int matrix[][MAX_NUM_COLS], int is_visited[][MAX_NUM_COLS], 
        int cur_row, int cur_col, int n_rows, int n_cols)
{
    /*If we are outside the bounds of the matrix or
    if the cell is already visited or if the value in cell is 0
    then we shouldn't enter the cell */
    if (cur_row < 0 || cur_row >= n_rows 
        || cur_col < 0 || cur_col >= n_cols
        || is_visited[cur_row][cur_col] 
        || matrix[cur_row][cur_col] == 0) {
        return 0;
    }

    return 1;
}


/* Helper function to count the number of islands of 1's
matrix: 2d matrix consisting of 0's and 1's
is_visited: if cell (i, j) has been visited, is_visited[i][j] is set to 1
cur_row: row of the current cell being processed
cur_col: column of the current cell being processed
n_rows: number of rows in the matrix
n_cols: number of columns in the matrix 
*/
void expand_search(int matrix[][MAX_NUM_COLS], int is_visited[][MAX_NUM_COLS], 
    int cur_row, int cur_col, int n_rows, int n_cols)
{
    int i, j;

    is_visited[cur_row][cur_col] = 1;

    /*For the current cell, find out if we can continue the island of 1's
    with its neighbors. Each cell has 8 neighbors. The rows
    of neighbors will vary from cur_row - 1 to cur_row + 1
    The columns of the neighbors will vary from cur_col - 1
    to cur_col + 1*/
    for (i = -1; i <= 1; ++i) {
        for (j = -1; j <= 1; ++j) {
            int is_safe_cell = can_enter_cell(matrix, is_visited,  
                    cur_row+i, cur_col+j, n_rows, n_cols);

            if (is_safe_cell) {
                expand_search(matrix, is_visited, cur_row+i, 
                        cur_col+j, n_rows, n_cols);
            }
        }
    }
}

/* Main function to find the number of islands of 1's
matrix: 2d matrix consisting of 0's and 1's. Should not be empty
n_rows: number of rows in the matrix. Should be >= 1
n_cols: number of columns in the matrix. Should be >= 1 
*/
int find_islands(int matrix[][MAX_NUM_COLS], int n_rows, int n_cols)
{
    int is_visited[MAX_NUM_ROWS][MAX_NUM_COLS];
    int i, j, count;

    /*Initially all cells are not yet visited*/
    for (i = 0; i < n_rows; ++i)
        for (j = 0; j < n_cols; ++j) 
            is_visited[i][j] = 0;

    /*Search all the cells in matrix that are not yet visited*/
    count = 0;
    for (i = 0; i < n_rows; ++i) {
        for (j = 0; j < n_cols; ++j) {
            if (matrix[i][j] && !is_visited[i][j]) {
                /*We have found an island. Now expand the island 
                in all directions*/
                expand_search(matrix, is_visited, i, j, 
                        n_rows, n_cols);
                ++count;
            }
        }
    }
    return count;
}


void test_01()
{
    int matrix[MAX_NUM_ROWS][MAX_NUM_COLS] = { 
                    {1, 1, 1, 0, 0},
                    {0, 1, 0, 0, 1},
                    {0, 0, 0, 1, 0},
                    {0, 0, 0, 0, 0},
                    {0, 1, 0, 1, 0}
                };
    int n_rows = 5, n_cols = 5;
    int result;
    int expected_result = 4;

    print_matrix(matrix, n_rows, n_cols);

    result = find_islands(matrix, n_rows, n_cols);

    printf("Number of islands = %d\n", result);

    if (result != expected_result)
        handle_error();

    printf("______________________________________\n");
}



void test_02()
{
    int matrix[MAX_NUM_ROWS][MAX_NUM_COLS] = { 
                    {1, 1, 1, 0, 0},
                    {0, 1, 1, 0, 0},
                    {1, 0, 1, 0, 0},
                    {1, 0, 1, 0, 0},
                    {0, 1, 1, 1, 0}
                };
    int n_rows = 5, n_cols = 5;
    int result;
    int expected_result = 1;

    print_matrix(matrix, n_rows, n_cols);

    result = find_islands(matrix, n_rows, n_cols);

    printf("Number of islands = %d\n", result);

    if (result != expected_result)
        handle_error();

    printf("______________________________________\n");
}



int main()
{
    test_01();
    test_02();

    printf("Test passed\n");
    return 0;
}

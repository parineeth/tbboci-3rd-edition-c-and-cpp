#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 9
#define NUM_COLS 9

void handle_error()
{
    printf("Error occured \n");
    exit(1);
}


void verify_grid(int grid[][NUM_COLS])
{
    int row_nr, col_nr, sum;

    /*The sum of the numbers in a row should be 
    1 + 2 + 3 + 4+ 5 + 6 + 7 + 8 + 9 = 45*/
    for (row_nr = 0; row_nr < NUM_ROWS; ++row_nr) {
        sum = 0;
        for (col_nr = 0; col_nr < NUM_COLS; ++col_nr) 
            sum += grid[row_nr][col_nr];

        if (sum != 45)
            handle_error();
    }


    /*The sum of the numbers in a column should be 
    1 + 2 + 3 + 4+ 5 + 6 + 7 + 8 + 9 = 45*/
    for (col_nr = 0; col_nr < NUM_COLS; ++col_nr) {
        sum = 0;
        for (row_nr = 0; row_nr < NUM_ROWS; ++row_nr) 
            sum += grid[row_nr][col_nr];

        if (sum != 45)
            handle_error();
    }
    
    /*We should also check if the sum in every 3*3 box is 45*/
}


void print_grid(int grid[][NUM_COLS], int verify)
{
    int i, j;

    for (i = 0; i < NUM_ROWS; ++i) {
        for (j = 0; j < NUM_COLS; ++j) {
            printf("%4d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");

    if (verify)
        verify_grid(grid);
}




/* Helper function which checks if it is possible to place a number in a cell
grid: the 2d sudoku matrix
row_nr: row number of the cell we are checking
col_nr: column number of the cell we are checking
num: the number which we want to place in the cell
Returns: 1 if we can place num in the cell, 0 otherwise
*/
int can_fill_cell(int grid[][NUM_COLS], int row_nr, int col_nr, int num)
{
    int i, j;
    int region_start_row, region_start_col;

    /*Ensure that the number is not present in any row of requested column*/
    for (i = 0; i < NUM_ROWS; ++i)
        if (grid[i][col_nr] == num)
            return 0;

    /*Ensure that the number is not present in any column of requested row*/
    for (j = 0; j < NUM_COLS; ++j)
        if (grid[row_nr][j] == num)
            return 0;

    /*Ensure that the number is not present in the 3*3 box it belongs to*/
    region_start_row = (row_nr / 3) * 3;
    region_start_col = (col_nr / 3) * 3;

    for (i = region_start_row; i < region_start_row + 3; ++i)
        for (j = region_start_col; j < region_start_col + 3; ++j)
            if (grid[i][j] == num)
                return 0;

    return 1;
}

/*Main function for solving the sudoku puzzle
grid: the 2d sudoku matrix
row_nr: row number of the current cell being processed
col_nr: column number of the current cell being processed
*/
void solve_sudoku(int grid[][NUM_COLS], int row_nr, int col_nr)
{
    int next_row, next_col, num;

    if (row_nr >= NUM_ROWS) {
        /*We have found a solution. print the grid and
        terminate the recursion*/
        print_grid(grid, 1);
        return;
    }

    /*Pre-compute the row and column of the next cell*/
    next_row = row_nr;
    next_col = col_nr + 1;
    if (next_col >= NUM_COLS) {
        next_col = 0;
        next_row = row_nr + 1;
    }

    if (grid[row_nr][col_nr] == -1) {
        /*The puzzle writer has not assigned a number to this cell.
        So try assigning numbers 1-9 to the cell*/
        for (num = 1; num <= 9; ++num) {
            if (can_fill_cell(grid, row_nr, col_nr, num)) {
                grid[row_nr][col_nr] = num;
                solve_sudoku(grid, next_row, next_col);
            }
        }
        /*Once we are done trying all numbers from 1-9, assign the cell
        back to -1 to indicate puzzle writer has not assigned a number 
        to the cell*/
        grid[row_nr][col_nr] = -1;

    } else {
        /*The puzzle writer has already assigned a value to the cell. 
        So proceed to the next cell*/
        solve_sudoku(grid, next_row, next_col);
    }
}


int main()
{
    int grid[NUM_ROWS][NUM_COLS];
    int i, j;

    /*Initialize all cells with -1*/
    for (i = 0; i < NUM_ROWS; ++i)
        for (j = 0; j < NUM_COLS; ++j)
            grid[i][j] = -1;

    /*Fill in the cells specified by the puzzle writer*/
    grid[0][0] = 5;
    grid[0][1] = 3;
    grid[0][4] = 7;

    grid[1][0] = 6;
    grid[1][3] = 1;
    grid[1][4] = 9;
    grid[1][5] = 5;

    grid[2][1] = 9;
    grid[2][2] = 8;
    grid[2][7] = 6;

    grid[3][0] = 8;
    grid[3][4] = 6;
    grid[3][8] = 3;

    grid[4][0] = 4;
    grid[4][3] = 8;
    grid[4][5] = 3;
    grid[4][8] = 1;

    grid[5][0] = 7;
    grid[5][4] = 2;
    grid[5][8] = 6;

    grid[6][1] = 6;
    grid[6][6] = 2;
    grid[6][7] = 8;

    grid[7][3] = 4;
    grid[7][4] = 1;
    grid[7][5] = 9;
    grid[7][8] = 5;

    grid[8][4] = 8;
    grid[8][7] = 7;
    grid[8][8] = 9;

    printf("Input: \n");
    print_grid(grid, 0); /*passing 0 so that we don't verify the grid*/

    printf("Output: \n");
    solve_sudoku(grid, 0, 0);

    printf("Test passed\n");
    return 0;

}


#include <stdio.h>
#include <stdlib.h>

#define MAX_N   10

/*
Helper function which checks if it is possible to place queen in cur_row 
at position col_for_row[cur_row]
cur_row: Row in which the current queen should be placed
col_for_row: col_for_row[i] gives column in which queen of the ith row is placed
Return value: 1 if queen can be placed at col_for_row[cur_row], 0 otherwise
*/
int check_placement(int cur_row, int col_for_row[])
{
    int i, row_diff, col_diff;

    /*Check if the queens placed in the rows before the current row conflict 
    with the queen placed in current row*/
    for (i = 0; i < cur_row; ++i) {
        /*Check if two queens are present in the same column*/
        if (col_for_row[i] == col_for_row[cur_row])
            return 0;

        /*Check if two queens are in the same diagonal*/
        col_diff = abs(col_for_row[cur_row] - col_for_row[i]);
        row_diff = cur_row - i;
        if (row_diff == col_diff)
            return 0;       
         
    }

    return 1;
}

/*
Main function for arranging the queens
cur_row: current row in which the queen should be placed
N: the number of cells in 1 row of the chess board
col_for_row: col_for_row[i] is used for storing the column of the ith row queen 
*/
void arrange_queens(int cur_row, int N, int col_for_row[])
{
    int i;

    if (cur_row == N) {
        /*We have found a successful arrangement. So print it*/
        for (i = 0; i < N; ++i) {
            printf("(Row = %d, Col = %d) \n", i, col_for_row[i]); 
        }
        printf("__________________________\n");

        return; /*Terminate the recursion*/
    }

    /*Try out different columns in the current row*/
    for (i = 0; i < N; ++i) {
        col_for_row[cur_row] = i;
        if (check_placement(cur_row, col_for_row)) {
            /*The placement of queens looks good so far. 
            Go to the next row*/
            arrange_queens(cur_row + 1, N, col_for_row);
        }
    } 

}


int main() 
{
    int col_for_rows[MAX_N];
    int N = 4; /*Number of cells in one row of the chess board*/

    printf("N = %d\n", N);

    arrange_queens(0, N, col_for_rows);

    printf("Test passed\n");
    return 0;
}

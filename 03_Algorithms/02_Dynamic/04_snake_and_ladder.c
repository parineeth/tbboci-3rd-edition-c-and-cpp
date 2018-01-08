/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POSITIONS_ON_BOARD  (100)

void handle_error()
{
    printf("Error occured \n");
    exit(1);
}



/*is_snake: if there is a snake at position 20, then is_snake[20] is set to 1
ladder: if there is a ladder from position 30 to 44, then ladder[44] = 30.
    if there is no ladder at location 90 then ladder[90] = -1
predecessor: this array has the previous board position from where we came to 
    current position with least number of dice throws. If predecessor[100]   
    = 95, then we reached 100 from 95. It is computed and returned. 
Return value: least number of throws to reach the final position on the board
*/
int find_least_throws(int is_snake[], int ladder[], int predecessor[])
{
    /*for a particular position pos on the board, least_throws[pos] will store
    the least number of dice throws required to reach the position*/
    int least_throws[MAX_POSITIONS_ON_BOARD + 1];
    int min_throws, i;
    int pos, prev_pos, ladder_start_pos;

    /*Positions from 1 to 6 can be reached from a single dice throw*/
    for (pos = 1; pos <= 6; pos++) {
        least_throws[pos] = 1;
        predecessor[pos] = 0;
    }

    for (pos = 7; pos <= MAX_POSITIONS_ON_BOARD; ++pos) {
        min_throws = MAX_POSITIONS_ON_BOARD;

        /*Find how many dice throws are needed to reach pos from any of 
        the 6 previous cells*/
        for (i = 1; i <= 6; ++i) {
            prev_pos = pos - i;

            if (is_snake[prev_pos])
                continue;

            /*Pick the minimum throws needed from the 6 previous cells*/
            if (least_throws[prev_pos] + 1 < min_throws) {
                min_throws = least_throws[prev_pos] + 1;
                predecessor[pos] = prev_pos;
            }
        }

        /*Suppose we are at pos = 14 and ladder[14] = 4, then there is a ladder
        from 4 to 14. So number of dice throws needed to reach 14 = number of 
        dice throws needed to reach position 4*/
        ladder_start_pos = ladder[pos];
        if (ladder_start_pos != -1) {
            if (least_throws[ladder_start_pos] < min_throws) {
                min_throws = least_throws[ladder_start_pos];
                predecessor[pos] = ladder_start_pos;
            }
        }

        least_throws[pos] = min_throws;
    }
    return least_throws[MAX_POSITIONS_ON_BOARD];
}



int main()
{
    int is_snake[MAX_POSITIONS_ON_BOARD + 1], ladder[MAX_POSITIONS_ON_BOARD + 1];
    int predecessor[MAX_POSITIONS_ON_BOARD + 1];
    int i, min_throws;

    for (i = 0; i <= MAX_POSITIONS_ON_BOARD; ++i) {
        is_snake[i] = 0;
        ladder[i] = -1;
        predecessor[i] = 0;
    }

    /*if there is a snake at position 20 on board, the is_snake[20] is set to 1*/
    is_snake[17] = 1;
    is_snake[54] = 1;
    is_snake[62] = 1;
    is_snake[64] = 1;
    is_snake[87] = 1;
    is_snake[93] = 1;
    is_snake[95] = 1;
    is_snake[99] = 1;

    /*if there is a ladder from position 30 to 44, then ladder[44] = 30.
    if there no ladder at location 90 then ladder[90] = -1*/
    ladder[14] = 4;
    ladder[31] = 9;
    ladder[38] = 20;
    ladder[84] = 28;
    ladder[59] = 40;
    ladder[67] = 51;
    ladder[81] = 63;
    ladder[91] = 71;

    min_throws = find_least_throws(is_snake, ladder, predecessor);

    printf("Least number of throws = %d\n", min_throws);

    if (min_throws != 7)
        handle_error();

    printf("The positions on the board corresponding to dice throws in reverse order are: \n");

    i = MAX_POSITIONS_ON_BOARD;
    printf("%d\n", i);
    while (i > 0) {
        printf("%d\n", predecessor[i]);
        i = predecessor[i];
    }

    printf("Test passed\n");
    return 0;
}

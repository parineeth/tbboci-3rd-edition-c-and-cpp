/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

/*Keep the number of coin flips >= 1000 so that we have sufficient number of flips*/
#define MAX_COIN_FLIPS  (1000)


void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}

/*
Return value: returns 0 with a probability of 0.7 and 1 with a probability of 0.3
*/
int toss_unfair_coin()
{
    int rand_num = rand() % 10;

    if (rand_num <= 6) {
        /*If we get a number from 0 to 6, return 0.
        So likelihood of getting 0 is 0.7 */
        return 0;
    } else {
        /*If we get a number from 7 to 9, return 1
        So likelihood of getting 1 is 0.3*/
        return 1;
    }
        
}

/*Returns 0 with a probability of 0.5 and 1 with a probability of 0.5 */
int toss_fair_coin() {
    while (1) {
        int x = toss_unfair_coin();
        int y = toss_unfair_coin();
        if (x == 0 && y == 1)
            return 0; 
        else if (x == 1 && y == 0) 
            return 1;
    }
}




int main() 
{
    int i, outcome, num_heads, num_tails, diff;

    num_heads = num_tails = 0;
    for (i = 0; i < MAX_COIN_FLIPS; ++i) {
        outcome = toss_fair_coin();

        if (outcome == 0) 
            num_heads++;
        else if (outcome == 1)
            num_tails++;
        else 
            handle_error();
    }

    printf("Number of heads = %d, Number of tails = %d \n", num_heads, num_tails);

    diff = abs(num_heads - num_tails) / 2;

    /*The difference between number of heads and number of tails should not be more than
    5% of the total number of coin flips*/
    if (diff > (5 * MAX_COIN_FLIPS / 100)) 
        handle_error();

    printf("Test passed\n");
    return 0;
}


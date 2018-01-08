/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


#define MAX_NUM_TRIALS  (50)


void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}

/*
Return value: returns 0 with a probability of 0.5 and 1 with a probability of 0.5
*/
int binary_rand()
{
    int rand_num = rand() % 2;

    return rand_num;    
}

/*Returns number x where a <= x <= b and x is uniformly distributed*/
int get_random_num(int a, int b) {
    int i, rand_num;
    int num_outcomes = b - a + 1;

    while (1) {
        rand_num = 0;
        i = 0;
        while ( (1 << i) < num_outcomes) {
            /*Append the random binary digit to the end*/
            rand_num = (rand_num << 1) | binary_rand();
            ++i;
        }

        if (rand_num < num_outcomes)
            break;
        /*If rand_num >= num_outcomes, we try again*/
    } 
    return rand_num + a; 
}



void test(int a, int b) 
{
    int i, outcome;

    printf("Generating random numbers from %d to %d \n", a, b);

    for (i = 0; i < MAX_NUM_TRIALS; ++i) {
        outcome = get_random_num(a, b);

        printf("%d\n", outcome);

        if (outcome < a || outcome > b) 
            handle_error();
    }

    printf("____________________________________\n");
}


int main() 
{
    test(0, 0);
    test(0, 1);
    test(1, 10);
    test(100, 500); 

    

    printf("Test passed\n");
    return 0;
}


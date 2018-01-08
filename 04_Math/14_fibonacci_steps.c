/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N_STEPS     (20)


void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


/*
n: number of steps. n >= 1
Returns: the number of ways to climb the steps
*/
int climb_steps(int n) 
{
    int i, x, y;

    /*Directly return the value for the first two fibonacci numbers*/
    if (n <= 2)
        return n;
    
    x = 1;
    y = 2;
    for (i = 3; i <=n; ++i) {
        int temp = x + y;
        x = y;
        y = temp;
    } 
        
    return y;
}

/*
n: number of steps. n >= 1
Returns: the number of ways to climb the steps using recursion
*/
int climb_steps_r(int n)
{
    if (n <= 2)
        return n;

    return climb_steps_r(n-1) + climb_steps_r(n-2);
}



int main() 
{
    int i, a, b;

    
    for (i = 1; i <= MAX_N_STEPS; ++i) {
        /*Find the number of ways to climb steps non-recursively*/
        a = climb_steps(i);

        /*Find the number of ways to climb steps recursively*/
        b = climb_steps_r(i);

        if (a != b)
            handle_error();

        printf("Number of steps = %d, Number of ways to climb = %d\n", i, a);
    }


    printf("Test passed\n");
    return 0;
}


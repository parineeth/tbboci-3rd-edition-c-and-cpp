/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


void handle_error()
{
    printf("Error occured \n");
    exit(1);
}


/*x, y: two integers, x > 0, y >= 0
Return value: x multiplied with itself y times*/
int power(int x, int y) {
    int result = 1;
    while (y) {
        /*look at the least significant bit of y*/
        if ((y & 1) == 1)  
            result = result * x;
        y = y >> 1;/*shift out the least significant bit of y*/
        x = x * x;
    }
    return result;
}



int brute_force_power(int x, int y)
{
    int result = 1, i;

    for (i = 0; i < y; ++i) {
        result = result * x;
    }

    return result;
}


int main()
{
    int optimal_result, brute_force_result;
    int x, y, max_y;

    for (x = 2; x <= 10; ++x) {

        /*Based on the value of x determine the maximum y value so that
        x ^ y  does not overflow*/
        if (x == 2) {
            max_y = 30;
        }
        else if (x == 3) {
            max_y = 18;
        }
        else if (x == 4) {
            max_y = 15;
        }
        else if (x == 5) {
            max_y = 12;
        }
        else if (x == 6) {
            max_y = 11;
        }
        else if (x == 7) {
            max_y = 10;
        }
        else if (x == 8) {
            max_y = 10;
        }
        else if (x == 9) {
            max_y = 9;
        }
        else  {
            max_y = 8;
        }

        for (y = 0; y <= max_y; ++y) {
            optimal_result = power(x, y);

            printf("%d ^ %d = %d\n", x, y, optimal_result);

            brute_force_result = brute_force_power(x, y);

            if (optimal_result != brute_force_result) {
                handle_error();
            }
        }
    }

    printf("Test passed \n");
    return 0;
}

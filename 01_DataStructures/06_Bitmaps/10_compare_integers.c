/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}

/*Returns the maximum of x and y without using if-else and comparison*/
int find_max(int x, int y) {
    int difference = x - y;
    int sign_bit =  (difference >> 31) & 0x1;
    /*
    Sign bit can be 0 or 1
    If sign bit is 0, max = x - (0 * difference) = x
    If sign bit is 1, max = x - (1 * (x-y)) = x - x + y = y 
    */
    int max = x  - (sign_bit * difference);
    return max;
}



void test(int x, int y) 
{
    int result = find_max(x, y);
    int expected_result;

    printf("maximum of (%d, %d) = %d\n", x, y, result);

    expected_result = x > y ? x : y;

    if (result != expected_result)
        handle_error();

}


int main()
{
    test(-10, -20);
    test(-10, 20);
    test(10, -20);
    test(10, 20);
    test(0, 10);
    test(0, -20);

    printf("Test passed \n");

    return 0;
}

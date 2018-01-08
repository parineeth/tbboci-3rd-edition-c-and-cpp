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


/*
x, y: two integers, can be negative. x may be bigger, equal or smaller than y
Return value: x - y
*/
int subtract(int x, int y) 
{
    int borrow;

    while (y != 0) {
        /*compute the borrow bits for all the bits in x and y*/
        borrow = (~x) & y;

        /*compute the difference bits for all the bits in x and y*/
        x = x ^ y;

        /*If a borrow is needed at current bit position, we would have 
        marked a 1 in current bit position. But the borrow needs to be  
        subtracted from the next bit position. So left shift the borrow
        bits by 1 and then subtract the borrow in the next iteration
        */
        y = borrow << 1;
    }
    return x;
}


void test(int x, int y)
{
    int result = subtract(x, y);

    printf("%d - %d = %d \n", x, y, result);

    /*Verify the result*/
    if (result != (x - y))
        handle_error();
}


int main()
{
    test(20, 13);

    test(20, 20);

    test(78, 100);

    test(50, -7);

    test(-8, 17);

    test(-8, -17);

    test(-25, -25);
    

    printf("Test passed\n");

    return 0;
}


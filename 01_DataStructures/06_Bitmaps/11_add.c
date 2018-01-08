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
Return value: x + y
*/
int add(int x, int y) 
{
    int carry;

    while (y != 0) {
        /*compute the carry bits for all the bits in x and y*/
        carry = x & y;

        /*compute the sum bits for all the bits in x and y*/
        x = x ^ y;

        /*If a carry is present at current bit position, we would have 
        marked a 1 in current bit position. But the carry needs to be 
        added from the next bit position. So left shift the carry bits 
        by 1 and then add the carry in the next iteration
        */
        y = carry << 1;
    }
    return x;
}


void test(int x, int y)
{
    int result = add(x, y);

    printf("%d + %d = %d \n", x, y, result);

    /*Verify the result*/
    if (result != (x + y))
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


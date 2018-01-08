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
a, b: Two integers. a may be greater than, equal to or less than b
Return value: Greatest common divisor
*/
int gcd(int a, int b)
{
    if (b == 0)
        return a;

    /*Find the GCD of b and the remainder of a/b*/
    return gcd(b, a%b);
}


void test(int a, int b, int expected_result)
{
    int result = gcd(a, b);

    printf("gcd(%d, %d) = %d \n", a, b, result);

    /*Verify the result*/
    if (result != expected_result)
        handle_error();
}


int main()
{
    /*GCD of 2 and 5 is 1*/
    test(2, 5, 1);

    test(3, 9, 3);

    test(9, 9, 9);

    test(12, 20, 4);

    test(20, 12, 4);

    printf("Test passed\n");

    return 0;
}


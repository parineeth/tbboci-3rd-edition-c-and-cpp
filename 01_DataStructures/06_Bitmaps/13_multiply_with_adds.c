/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE (10)
#define MAX_NUM_TESTS (100)

void handle_error()
{
    printf("Error occured \n");
    exit(1);
}


/*x, y: two integers >= 0
Return value: x multiplied with y */
int multiply(int x, int y) {
    int result;

    result = 0;
    while (y) {
        /*if the least significant bit of y is 1, then add x to result*/
        if ((y & 1) == 1) {
            result += x;
        }
        y = y >> 1;/*shift out the least significant bit of y*/
        x = x << 1; /*Double the value of x*/
    }
    return result;
}




void test()
{
    int result;
    int x, y;

    x = rand() % MAX_VALUE;
    y = rand() % MAX_VALUE;

    result = multiply(x, y);

    printf("%d * %d = %d\n", x, y, result);

    if (result != (x * y) ) {
        handle_error();
    }

}


int main()
{
    int test_nr;

    for (test_nr = 0; test_nr < MAX_NUM_TESTS; ++test_nr) {
        test();
    }
    
    printf("Test passed \n");
    return 0;
}

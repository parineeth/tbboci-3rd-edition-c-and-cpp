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



int rand5()
{
    int result = 1 + rand() % 5;

    return result;
}


int rand7() {
    int result;
    while(1) {
        result = (rand5() - 1) + (5 * (rand5() - 1) );
        if (result <= 20)
            break;
    }
    result = 1 + (result % 7);
    return result;
}


int main()
{
    int i, result;

    for (i = 0; i < 100; ++i) {
        result = rand7();
        printf("Random value is %d\n", result);
        if (result < 1 || result > 7)
            handle_error();
    }

    printf("Test passed\n");

    return 0;
}

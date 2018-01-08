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



/*
x: input integer
Return value: parity bit, 1 if there are odd number of 1's, 0 otherwise
*/
unsigned int compute_parity(unsigned int x) 
{
    /*for each bit set to 1 in x, toggle the parity bit*/
    unsigned int parity = 0;
    while (x != 0) {
        parity = parity ^ 1;
        x = x & (x - 1);
    }

    return parity;
}


void test(unsigned int x, unsigned int expected_result) 
{
    unsigned int result = compute_parity(x);

    printf("Parity bit for 0x%x = %d\n", x, result);

    if (result != expected_result)
        handle_error();
}


int main() 
{
    test(0xB, 1);
    test(0xA, 0);

    printf("Test passed\n");
    return 0;
}
  

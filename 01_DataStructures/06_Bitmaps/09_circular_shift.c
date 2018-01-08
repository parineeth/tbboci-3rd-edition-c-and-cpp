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
input: input value which has to be circularly shifted left
n: number of positions to shift
Return value: result after circularly left shifting input
*/
unsigned int circular_left_shift(unsigned int input, int n)
{
    unsigned int size = sizeof(unsigned int) * 8;
    unsigned int result;
    
    n = n % size;
    result = input << n | input >> (size - n);
    return result;
}


/*
input: input value which has to be circularly shifted right
n: number of positions to shift
Return value: result after circularly right shifting input
*/
unsigned int circular_right_shift(unsigned int input, int n)
{
    unsigned int size = sizeof(int) * 8;
    unsigned int result;

    n = n % size;
    result = input >> n | input << (size - n);
    return result;
}




int main()
{
    unsigned int result;

    result = circular_right_shift(0x1, 1);
    if (result != 0x80000000)
        handle_error();

    
    result = circular_right_shift(0xFEDCBA98, 32);
    if (result != 0xFEDCBA98)
        handle_error();

    result = circular_right_shift(0xFEDCBA98, 16);
    if (result != 0xBA98FEDC)
        handle_error();


    
    result = circular_left_shift(0x1, 0x80000000);
    if (result != 1)
        handle_error();

    
    result = circular_left_shift(0xFEDCBA98, 32);
    if (result != 0xFEDCBA98)
        handle_error();

    result = circular_left_shift(0xFEDCBA98, 16);
    if (result != 0xBA98FEDC)
        handle_error();



    printf("Test passed \n");

    return 0;
}

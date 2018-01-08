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



/*writes the bit_value (0/1) into position pos in x and returns the result*/
unsigned int write_bit(unsigned int x, int bit_value, int pos) 
{
    unsigned int mask = 1 << pos;
    if (bit_value)
        x = x | mask;
    else
        x = x & ~mask;

    return x;
}

/*
x: integer in which the bits should be swapped
pos1: position of first bit to be swapped
pos2: position of the second bit to be swapped
*/
unsigned int swap_bits(unsigned int x, int pos1, int pos2) 
{
    /*get the bits at position pos1 and pos2*/
    int bit1 = (x >> pos1) & 1;
    int bit2 = (x >> pos2) & 1;

    /*swap the bits if the bits are different*/
    if (bit1 != bit2) {
        x = write_bit(x, bit1, pos2);
        x = write_bit(x, bit2, pos1);
    }

    return x;
}


void test(unsigned int x, int pos1, int pos2, unsigned int expected_result) 
{
    unsigned int result = swap_bits(x, pos1, pos2);

    printf("Swapping bit %d and bit %d on 0x%x = 0x%x\n", pos1, pos2, x, result);

    if (result != expected_result)
        handle_error();
}



int main() 
{
    test(0xB, 1, 2, 0xD);
    test(0xB, 1, 0, 0xB);

    printf("Test passed\n");
    return 0;
}



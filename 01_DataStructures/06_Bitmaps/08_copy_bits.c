/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

/*
dest: destination integer into which the bits have to be copied
src: source integer from which the bits have to be copied 
end_pos: Most Significant bit position upto where the bits should be copied
start_pos: Least Significant bit position from where the bits should be copied
    end_pos should be >= start_pos
Return value: result integer after copying bits from source to destination
*/
unsigned int copy_bits(unsigned int dest, unsigned int src, 
            unsigned int end_pos, unsigned int start_pos)
{
    unsigned int num_bits_to_copy = end_pos - start_pos + 1;
    unsigned int num_bits_in_int = sizeof(unsigned int) * 8;
    unsigned int zeroes_mask;
    unsigned int ones_mask = ~((unsigned int) 0); /*all ones*/

    /*Use the bit-wise right shift operator to remove the excess 1's 
    in the mask*/
    ones_mask = ones_mask >> (num_bits_in_int - num_bits_to_copy);

    /*Left shift the 1's to the starting position. ones_mask will contain 1's
    from start_pos to end_pos*/
    ones_mask = ones_mask << start_pos;

    /*zeroes_mask will contain 0's from start_pos to end_pos*/
    zeroes_mask = ~ones_mask;

    /*clear the bits in destination from start_pos to end_pos*/
    dest = dest & zeroes_mask;

    /*retain the bits in source from start_pos to end_pos and clear the 
    remaining bits*/
    src = src & ones_mask;
    
    /*copy the source bits into the destination*/
    dest = dest | src;
    
    return dest;
}



int main()
{
    unsigned int a, b, result;

    /*Copy bits of b into a from position 7 to position 4*/
    a = 0xABCDEF;
    b = 0xBBBBAB;
    result = copy_bits(a, b, 7, 4);
    if (result != 0xABCDAF)
        handle_error();


    printf("Test passed\n");

    return 0;
}

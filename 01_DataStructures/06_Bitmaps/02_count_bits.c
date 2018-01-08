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



unsigned int count_num_bits_set(unsigned int n)
{
    unsigned int count = 0;
    
    while (n) {
        n &= n - 1;
        count++;
    }

    return count;
}




int main()
{
    unsigned int num_bits_set;

    num_bits_set = count_num_bits_set(0);

    if (num_bits_set != 0)
        handle_error();

    num_bits_set = count_num_bits_set(0xffffffff);

    if (num_bits_set != 32)
        handle_error();


    num_bits_set = count_num_bits_set(0x70ff00f);

    if (num_bits_set != 15)
        handle_error();

    printf("Test passed\n");

    return 0;
}

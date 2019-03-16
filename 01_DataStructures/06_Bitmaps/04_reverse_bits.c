/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_TESTS (1000)


int get_rand_byte()
{
    return rand() % 256;    
}



void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

/*
input_value: the integer that has to be reversed
reverse_table: lookup table that has the reversed values for every byte.
    Example - reverse_table[0x1] = 0x80, since reverse of 00000001 is 1000000
Return value: integer that is the reverse of the input integer
*/
unsigned int reverse_integer(unsigned int input_value, 
                unsigned char reverse_table[])
{
    unsigned int result = 0;
    int i = 0;
    int num_bytes = sizeof(int);

    for (i = 0; i < num_bytes; ++i) {
        /*Get the least significant byte from the input*/
        int cur_byte_value = input_value & 0xFF;

        /*Left shift the result by 8 and append the reverse of the 
        least significant byte of input*/
        result = (result << 8) | reverse_table[cur_byte_value];

        /*Right shift out the least significant byte from the input*/
        input_value = input_value >> 8;
    }
    return result;
}

unsigned int normal_reverse_integer(unsigned int input)
{
    unsigned int size_in_bits = sizeof(int) * 8;
    unsigned int result;
    unsigned int i;
    int j;

    result = 0;
    j = size_in_bits - 1;
    for (i = 0; i < size_in_bits; ++i) {
        if (input & (1u << i) ) {
            result = result| (1u << j);
        }
        --j;
    }

    return result;
}


unsigned char normal_reverse_char(unsigned char input)
{
    unsigned int size_in_bits = sizeof(char) * 8 ;
    unsigned char result;
    unsigned int i;
    int j;

    result = 0;
    j = size_in_bits - 1;
    for (i = 0; i < size_in_bits; ++i) {
        if (input & (1u << i) ) {
            result = result| (1u << j);
        }
        --j;
    }

    return result;
}


int main()
{
    unsigned int i, test_nr, normal_result, lookup_result;
    unsigned int rand_num;
    unsigned char lookup_table[256];

    for (i = 0; i <= 255; ++i) {
        lookup_table[i] = normal_reverse_char((unsigned char)i);
    }
    
    for (test_nr = 0; test_nr < MAX_NUM_TESTS; ++test_nr) {
        rand_num =  (get_rand_byte() << 24) | get_rand_byte() << 16 | get_rand_byte() << 8 | get_rand_byte();
        
        normal_result = normal_reverse_integer(rand_num);

        lookup_result = reverse_integer(rand_num, lookup_table);

        if (normal_result != lookup_result) 
            handle_error();
    }

    rand_num = 0;
    if (rand_num != reverse_integer(rand_num, lookup_table))
        handle_error();

    rand_num = 0xffffffff;
    if (rand_num != reverse_integer(rand_num, lookup_table))
        handle_error();


    printf("Test passed\n");

    return 0;
}

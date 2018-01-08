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

/*sets the bit at position pos to 1 in the bitmap*/
void set_bit(unsigned char bitmap[], int pos)
{
    int byte_pos = pos / 8;
    int bit_pos = pos % 8;

    bitmap[byte_pos] |= 1u << bit_pos;  
}

/*Returns the bit at position pos in the bitmap*/
int get_bit(unsigned char bitmap[], int pos)
{
    int byte_pos = pos / 8;
    int bit_pos = pos % 8;

    if (bitmap[byte_pos] & (1u << bit_pos) )
        return 1;
    else 
        return 0;
} 

/*
n: Upto what number the primes should be generated
*/
void generate_primes(int n)
{
    int i, j;
    int total_num_bytes = 1 + (n / 8);

    /*is_multiple_bmp will be initialized with zeroes since we have not yet 
    identified the multiples*/
    unsigned char *is_multiple_bmp = (unsigned char*) calloc(1, 
                                total_num_bytes);

    /*We don't consider 0 and 1 as prime. Start from 2*/
    for (i = 2; i <= n; ++i) {
        if (get_bit(is_multiple_bmp, i)) 
            continue; /*i is a multiple, so it can't be prime*/
        
        printf("%d is prime\n", i);

        /*Mark all multiples of i (2i, 3i, 4i, etc) starting from 2*i */
        for (j = 2*i; j <= n; j += i) {
            set_bit(is_multiple_bmp, j);
        } 
    }

    free(is_multiple_bmp);
}


int main()
{
    generate_primes(100);

    printf("Test passed \n");

    return 0;
}



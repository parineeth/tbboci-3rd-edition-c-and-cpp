/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define DIVISION_BY_ZERO_ERROR (-1)

#define MAX_NUMERATOR (100)
#define MAX_DENOMINATOR (20)



void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

/*
a, b: a is an integer >= 0. b is an integer > 0
quotient_p: quotient of a / b will be returned here
remainder_p: remainder of a / b will be returned here
Return value: 0 on success, non-zero value on error (such as division by zero)
*/
int integer_division(int a, int b, int *quotient_p, int *remainder_p) {
    int quotient, remainder;
    char next_bit;
    int i, max_bit_pos = (sizeof(int) * 8) - 1;

    if (b == 0)
        return DIVISION_BY_ZERO_ERROR; /*we can also throw an exception*/
    
    quotient = remainder = 0;
    for (i = max_bit_pos; i >= 0; --i) {
        remainder = remainder << 1;  /*double the remainder*/

        /*Find the value of the next bit in the dividend a. 
        In first iteration, we find value of the Most Significant Bit*/
        next_bit = 0;
        if (a & (1u << i)) {
            next_bit = 1;
        }

        /*Copy the value of the next bit into the least significant 
        bit of remainder*/  
        if (next_bit)
            remainder = remainder | 1;

        /* If the remainder is now greater than the divisor b, 
        then subtract the divisor b from the remainder and 
        set the appropriate quotient bit*/
        if (remainder >= b) {
            remainder = remainder - b;
            quotient = quotient | (1u << i);
        }
    }
    *quotient_p = quotient;
    *remainder_p = remainder;
    return 0;
}





int main()
{
    int a, b, quotient, remainder;
    int expected_quotient, expected_remainder;

    for (a = 0; a < MAX_NUMERATOR; ++a) {
        for (b = 1; b < MAX_DENOMINATOR; ++b) {
            integer_division(a, b, &quotient, &remainder);

            printf("(%d / %d) => quotient = %d, remainder = %d \n", a, b, quotient, remainder);

            expected_quotient = a / b;
            expected_remainder = a % b;

            if (quotient != expected_quotient)
                handle_error();

            if (remainder != expected_remainder) 
                handle_error();
        }
    }

    printf("Test passed \n");

    return 0;
}

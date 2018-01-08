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

int max(int a, int b)
{
    return (a > b ? a : b);
}

int min(int a, int b)
{
    return (a < b ? a : b);
}

void print_array(unsigned int a[], int length) 
{
    int i;
    
    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }
    
    printf("\n");
}

/*
a: input array where 2 elements occur odd number of times and the remaining
    occur even number of times
n: number of elements in a
result: the two numbers that occur odd number of times will be returned here
*/
void find_odd_occurences(unsigned int a[], int n, unsigned int result[]) 
{
    unsigned int all_xor, mask;
    int i;

    all_xor = 0;
    for (i = 0; i < n; ++i) {
        all_xor = all_xor ^ a[i];
    }

    /*Find the first bit in the XOR result that is set to 1. The two odd 
    occuring numbers will differ at this bit position. So if difference 
    is at bit position 3, then mask will be ...00001000
    */ 
    mask = all_xor & ~(all_xor - 1);

    /*Separate out values in list a such that, values that have a 1 at the
    different bit will be XORed with result[0] and values that have a 0 
    at the different bit will be XORed with result[1] 
    */
    result[0] = result[1] = 0;
    for (i = 0; i < n; ++i) {
        if (a[i] & mask)
            result[0] = result[0] ^ a[i];
        else
            result[1] = result[1] ^ a[i];
    }

    /*result[0] and result[1] will now contain the two numbers that 
    occur odd number of times*/
}


void test(unsigned int a[], int n, unsigned int expected_result1, unsigned int expected_result2) 
{
    unsigned int result[2];
    print_array(a, n);

    find_odd_occurences(a, n, result);

    printf("The odd occuring elements are %d and %d\n", result[0], result[1]);

    if (min(result[0], result[1]) != min(expected_result1, expected_result2))
        handle_error();

    if (max(result[0], result[1]) != max(expected_result1, expected_result2))
        handle_error();

    printf("_____________________________________________\n");
}


int main()
{
    unsigned int a[] = {1, 2, 3, 2, 4, 3};
    test(a, 6, 1, 4);

    printf("Test passed\n");
    return 0;
}

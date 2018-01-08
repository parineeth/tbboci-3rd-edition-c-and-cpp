/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NUM_TESTS (100)
#define MAX_NUM_ELEMS (10)
#define MAX_VALUE     (2)

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


void print_array(int a[], int length) 
{
    int i;
    
    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }
    
    printf("\n");
}


/*
a: input array in which the zeroes should be moved to one end
length: number of elements in array a 
*/
void move_zeroes(int a[], int length)
{
    int left, right;

    left = 0;
    right = length - 1;

    while (left < right) {
        /*Locate the first zero from the left*/
        while (left < length && a[left] != 0)
            left++;

        /*Locate first non-zero from the right*/
        while (right >= 0 && a[right] == 0)
            right--;

        if (left < right) {
            /*Swap a[left] and a[right]*/
            int temp = a[left];
            a[left] = a[right];
            a[right] = temp;
        }
    }
}


void generate_array(int a[], int length)
{
    int i;
    
    for (i = 0; i < length; ++i) {
        a[i] = rand() % MAX_VALUE;
    }
}


void verify(int a[], int length) 
{
    int i;
    int found_zero;

    found_zero = 0;
    for (i = 0; i < length; ++i) {
        if (a[i] == 0) {
            found_zero = 1;
        }
        else {
            /*We have found a non-zero. Since all zeroes are at the end,
            we should not have found a zero till now*/
            if (found_zero)
                handle_error();
        }
    }
}



void test()
{
    int a[MAX_NUM_ELEMS];   
    int length;

    /*Randomly decide the number of elements*/
    length = 1 + rand() % MAX_NUM_ELEMS;

    /*Fill the array with random values*/
    generate_array(a, length);

    printf ("Original array : ");
    print_array(a, length);


    /*Move zeroes to the right */
    move_zeroes(a, length);

    printf ("After moving 0 : ");
    print_array(a, length);

    verify(a, length);


    printf("________________________________________________\n");

}


int main() 
{
    int i;

    for (i = 0; i < MAX_NUM_TESTS; ++i) {
        test();
    }

    printf("Test passed\n");
    return 0;
}

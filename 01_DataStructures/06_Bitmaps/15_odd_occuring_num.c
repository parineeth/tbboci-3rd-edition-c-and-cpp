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

void print_array(int a[], int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/*
a: array consisting of numbers, where one element occurs odd number of times
     while remaining elements occur even number of times 
n: number of elements in the array
Return value: element that occurs odd number of times
*/
int find_odd_occurence(int a[], int n)
{
    int i, result;

    /*XOR all the elements*/
    result = 0;
    for (i = 0; i < n; ++i) {
        result = result ^ a[i];
    }

    return result;
}

void test()
{
    int a[] = {1, 8, 4, 8, 2, 1, 4};
    int length = 7; /*Number of elements in the array*/
    int result, expected_result;

    printf("Input : ");
    print_array(a, length);

    result = find_odd_occurence(a, length);

    printf("Element that occurs odd number of times = %d\n", result);

    expected_result = 2;
    if (result != expected_result)
        handle_error();
}



int main()
{
    test();

    printf("Test passed \n");
    return 0;
}

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
a: array of unique numbers. A number can have a value between 1 to n.
n: maximum value that can be stored in array. array has n-1 elements
Return value: missing element in the array
*/
int find_missing(int a[], int n)
{
    int i, total_sum, expected_sum;
    int missing_num;

    /*Since 1 element is missing, there are only n-1 elements in the array*/
    total_sum = 0;
    for (i = 0; i < n - 1; ++i) { 
        total_sum += a[i];
    }

    expected_sum = n * (n+1) / 2;

    missing_num = expected_sum - total_sum;

    return missing_num;
}

void test()
{
    int a[] = {1, 2, 3, 4, 6, 7, 8, 9, 10};
    int length = 9; /*Number of elements in the array*/
    int result, expected_result;

    printf("Input : ");
    print_array(a, length);

    result = find_missing(a, length+1);

    printf("Missing element = %d\n", result);

    expected_result = 5;
    if (result != expected_result)
        handle_error();
}



int main()
{
    test();

    printf("Test passed \n");
    return 0;
}

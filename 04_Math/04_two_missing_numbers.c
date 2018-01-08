/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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
values: array of unique numbers. A number can have a value between 1 to n
n: maximum value in the array is n. array has n-2 elements
result: the missing elements in the array are returned here
*/
void find_missing(int values[], int n, int result[])
{
    int i, actual_normal_sum, expected_normal_sum;
    int actual_square_sum, expected_square_sum;
    int a_plus_b, a_minus_b, two_a_b, a_square_plus_b_square;
    int a, b;

    /*Since 2 elements are missing, there are only n-2 elements in array*/
    actual_normal_sum = 0;
    actual_square_sum = 0;
    for (i = 0; i < n - 2; ++i) { 
        actual_normal_sum += values[i];
        actual_square_sum += values[i] * values[i];
    }

    expected_normal_sum = n * (n+1) / 2;
    expected_square_sum = n * (n+1) * (2*n + 1) / 6;

    a_plus_b = expected_normal_sum - actual_normal_sum;
    a_square_plus_b_square = (expected_square_sum - actual_square_sum);
    two_a_b =  ((a_plus_b * a_plus_b) - a_square_plus_b_square);
    a_minus_b = (int) sqrt(a_square_plus_b_square - two_a_b);

    a = (a_plus_b + a_minus_b) / 2;
    b = (a_plus_b - a);
     
    result[0] = a;
    result[1] = b;
}

void test()
{
    int values[] = {1, 3, 4, 6, 7, 8, 9, 10};
    int length = 8; /*Number of elements in the array*/
    int result[2];

    printf("Input : ");
    print_array(values, length);

    find_missing(values, length+2, result);

    printf("Missing elements are = %d, %d \n", result[0], result[1]);

    if ( (result[0] == 2 && result[1] == 5) ||
        (result[0] == 5 && result[1] == 2) ) {
        /*Do nothing*/
    } else {
        handle_error();
    }
}



int main()
{
    test();

    printf("Test passed \n");
    return 0;
}

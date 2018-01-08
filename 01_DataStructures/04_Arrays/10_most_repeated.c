/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT (-100000)

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
a: array consisting of numbers. A number can have a value between 0 to k-1
n: number of elements in the array
k: k should be <= num elements in array
*/
int find_most_repeated(int a[], int n, int k)
{
    int i, index, most_repeated, max_value;
    
    /*For each number found in the array, go to the index corresponding 
    to the number and add k to the value at the index. */
    for (i = 0; i < n; ++i) {
        /*By the time we come to location i, we might have already added
        k to the value at this location one or more times. So take 
        a[i] % k to get the original value
        */
        index = a[i] % k;
        a[index] += k;
    }

    most_repeated = -1;
    max_value = MIN_INT;

    for (i = 0; i < n; ++i) {

        if (a[i] > max_value) {
            /*Note that index i will give the most repeated number*/
            most_repeated = i;
            max_value = a[i];
        }

        /*Get back the original value in the array*/
        a[i] = a[i] % k;
    }

    return most_repeated;
}

void test()
{
    int a[] = {2, 4, 0, 5, 2, 1, 9, 6, 8, 9, 2, 7};
    int n = 12; /*Number of elements in the array*/
    int k = 10; /*The value of all numbers in the array are less than k and k <= n*/    
    int result, expected_result;

    result = find_most_repeated(a, n, k);

    printf("Input : ");
    print_array(a, n);

    printf("Most repeated element = %d\n", result);

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

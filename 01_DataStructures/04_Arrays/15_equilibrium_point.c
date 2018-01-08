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

/*
a: input array whose equilibrium point has to be found.
n: number of elements in array a
Return value: index of the equilibrium point if it exists, -1 otherwise
*/
int find_equilibrium_point(int a[], int n)
{
    int left_sum, right_sum, i;

    /*Compute the sum of all elements and store in right_sum*/
    right_sum = 0;
    for (i = 0; i < n; ++i) {
        right_sum += a[i];
    }

    /*Go on computing sum of all elements from the left to right 
    and compare with right sum */
    left_sum = 0;
    for (i = 0; i < n; ++i) {
        /*Subtract a[i] from right_sum to find out sum of the 
        elements to the right of i*/
        right_sum -= a[i];

        if (left_sum == right_sum) {
            return i; /*We have found the equilibrium point*/
        }
        left_sum += a[i];
    }

    return -1;
}


void print_array(int a[], int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}


int main()
{
    int a[] = {-50, 100, 80, 30, -60, 10, 70};
    int result;

    printf("Input : ");
    print_array(a, 7);

    result = find_equilibrium_point(a, 7);

    printf("Equilibrium point index = %d\n", result);

    if (result != 2)
        handle_error();

    printf("Test passed\n");

    return 0;

}



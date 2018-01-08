/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_ITEMS (10)
#define MAX_VALUE (100)

#define INVALID_NUMBER (-1)


void handle_error()
{
    printf("Error occured \n");
    exit(1);
}

void print_array(int array[], int n)
{
    int i;

    for (i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }

    printf("\n");
}




/*
a: array in which each element should be replaced with next greatest
n: number of elements in the array. n >= 1
*/
void replace_with_next_greatest(int a[], int n)
{
    int i, next_greatest, temp;

    next_greatest = a[n-1];
    a[n-1] = INVALID_NUMBER;  

    /*Process the array from backwards*/
    for (i = n-2; i >= 0; --i) {
        temp = a[i];

        a[i] = next_greatest;

        if (temp > next_greatest)
            next_greatest = temp;
    }
}


void test_01()
{
    int n; 
    int a[MAX_NUM_ITEMS];
    int b[MAX_NUM_ITEMS];
    int i, j, max;

    /*Choose a random number of elements*/
    n = 1 + rand() % MAX_NUM_ITEMS;

    /*Generate n random values and store them in arrays a and b*/
    for (i = 0; i < n; ++i) {
        a[i] = rand() % MAX_VALUE;
        b[i] = a[i];
    }

    printf("Input: ");
    print_array(a, n);

    /*Replace with next greatest using the efficient algorithm. The result will be in array a*/
    replace_with_next_greatest(a, n);

    /*Replace with next greatest using brute force approach. The result will be in array b*/
    for (i = 0; i < n - 1; ++i) {
        max = 0;
        for (j = i + 1; j < n; ++j) {
            if (b[j] > max)
                max = b[j];
        }
        b[i] = max;
    }
    b[n - 1] = -1;

    printf("Output: ");
    print_array(a, n);

    /*Compare the efficient algortihm result with the brute force approach*/
    for (i = 0; i < n; ++i) {
        if (a[i] != b[i])
            handle_error();
    }
}



int main()
{
    int i;

    for (i = 0; i < 10; ++i) {
        test_01();
        printf("\n__________________________________\n\n");
    }


    printf("Test passed\n");
    return 0;
}

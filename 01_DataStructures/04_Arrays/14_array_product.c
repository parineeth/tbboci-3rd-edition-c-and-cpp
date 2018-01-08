/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_TESTS 100
#define MAX_VALUE 9
#define MAX_NUM_ELEMS 9

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


/*
a: input array 
length: number of elements in the array
result: result[i] will contain product of all elements of array a except a[i]
*/
void compute_product(int a[], int length, int result[])
{
    int i, product;
    
    /*Compute the product of elements of array a in forward direction.
    Store product of a[0] to a[i-1] in result[i]*/
    product = 1;
    for (i = 0; i < length; ++i) {
        result[i] = product;
        product = a[i] * product; 
    }

    /*Next compute the product of elements of array a in reverse direction
    So we now compute product of a[n-1] to a[i+1] and multiply it with 
    value in result[i]. In this way result[i] will contain product of
    a[0]...a[i-1]*a[i+1]....a[n-1]*/
    product = 1;
    for (i = length - 1; i >= 0; --i) {
        result[i] = result[i] * product;
        product = a[i] * product; 
    }
}

void print_array(int a[], int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}


void verify_result(int a[], int length, int result[])
{
    int i, j, expected_result;

    for (i = 0; i < length; ++i) {
        expected_result = 1;
        for (j = 0; j < length; ++j) {
            if (i != j) 
                expected_result = expected_result * a[j];           
        }

        if (expected_result != result[i])
            handle_error();
    }
}


void test()
{
    int i, length;
    int a[MAX_NUM_ELEMS], result[MAX_NUM_ELEMS];

    length = 1 + (rand() % MAX_NUM_ELEMS);

    for (i = 0; i < length; ++i) {
        a[i] = 1 + (rand() % MAX_VALUE);
    } 

    printf("Input  : ");
    print_array(a, length);

    compute_product(a, length, result);

    printf("Output : ");
    print_array(result, length);

    verify_result(a, length, result);

    printf("_________________________________________\n");
}


int main()
{
    int i;

    for (i = 0; i < MAX_NUM_TESTS; ++i)
        test();

    printf("Test passed \n");

    return 0;
}



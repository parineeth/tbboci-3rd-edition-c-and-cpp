/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NUM_TESTS (10)
#define MAX_NUM_ELEMS (10)
#define MAX_VALUE     (10)
#define MAX_INT       (1000000)
#define MIN_INT       (-100000)

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


int max(int a, int b)
{
    return (a > b ? a : b);
}

/*
a:input array 
length: number of elements in array a
Returns: the maximum product of 3 elements in the array 
*/
int find_max_product(int a[], int length)
{
    int i;
    int max_value[3];
    int min_value[2];

    assert (length >= 3);
    
    max_value[0] = max_value[1] = max_value[2] = MIN_INT;
    min_value[0] = min_value[1] = MAX_INT;

    for (i = 0; i < length; ++i) {
        /*Check if a[i] is among the 3 largest values*/
        if (a[i] > max_value[0]) {
            max_value[2] = max_value[1];
            max_value[1] = max_value[0];
            max_value[0] = a[i];
        } else if (a[i] > max_value[1]) {
            max_value[2] = max_value[1];
            max_value[1] = a[i];
        } else if (a[i] > max_value[2]) {
            max_value[2] = a[i];
        }

        /*Check if a[i] is among the 2 smallest values*/
        if (a[i] < min_value[0]) {
            min_value[1] = min_value[0];
            min_value[0] = a[i];
        } else if (a[i] < min_value[1]) {
            min_value[1] = a[i];
        }
    }

    return max(max_value[0] * max_value[1] * max_value[2],
            min_value[0] * min_value[1] * max_value[0]);
}


/*
a:input array 
length: number of elements in array a
Returns: the maximum product of 3 elements in the array 
*/
int brute_force_max_product(int a[], int length)
{
    int i, j, k ;
    int max_product = MIN_INT;

    for (i = 0; i < length - 2; ++i) {
        for (j = i+1; j < length - 1; ++j) {
            for (k = j+1; k < length; ++k) {
                int cur_product = a[i] * a[j] * a[k];

                if (cur_product > max_product)
                    max_product = cur_product;
            }
        }
    }

    return max_product;
}





void generate_array(int a[], int length)
{
    int i;
    
    for (i = 0; i < length; ++i) {
        a[i] = rand() % MAX_VALUE;

        if (rand() % 2 == 0) {
            a[i] = a[i] * -1;
        }
    }
}



void test()
{
    int a[MAX_NUM_ELEMS];   
    int length;
    int result, brute_force_result;


    /*Randomly decide the number of elements in the array*/
    length = rand() % MAX_NUM_ELEMS;

    if (length < 3)
        length = 3;


    /*Fill the array with random values*/
    generate_array(a, length);

    print_array(a, length);

    /*Find the result using the efficient technique*/
    result = find_max_product(a, length);
    
    printf("Max product = %d \n", result);


    /*Find the result using brute force*/
    brute_force_result = brute_force_max_product(a, length);


    /*The two results should match*/
    if (result != brute_force_result)
        handle_error();


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

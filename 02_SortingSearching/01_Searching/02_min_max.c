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

int min(int a, int b)
{
    return (a < b ? a : b); 
}

/*a:input array 
length: number of elements in array a
min_value: the minimum value is returned here
max_value: the maximum value is returned here*/
void find_min_max(int a[], int length, int *min_value, int *max_value) {
    int i = 0;
    *max_value = MIN_INT;
    *min_value = MAX_INT;
    if (length % 2 == 1) {
        /*If there are odd number of elements, then initialize 
        max_value and min_value with a[0]*/
        *max_value = *min_value = a[0];
        i = 1;
    }

    for (; i < length; i += 2) {
        if (a[i] > a[i+1]) {
            if (a[i] > *max_value) 
                *max_value = a[i];
            if (a[i+1] < *min_value)
                *min_value = a[i+1];
        } else {
            if (a[i] < *min_value)
                *min_value = a[i];
            if (a[i+1] > *max_value)
                *max_value = a[i+1];
        }
    }
}


int cmp_function(const void *p1, const void *p2)
{
    int *x = (int*)p1;
    int *y = (int*)p2;

    if (*x < *y)
        return -1;
    else if (*x == *y)
        return 0;
    else 
        return 1;
}

void sort(int a[], int length)
{
    qsort(a, length, sizeof(int), cmp_function);
}

/*
a:input array 
length: number of elements in array a
min_value: the minimum value is returned here
max_value: the maximum value is returned here
*/
void sorting_min_max(int a[], int length, int *min_value, int *max_value)
{
    sort(a, length);

    if (length > 0)
        *min_value = a[0];

    if (length > 0) 
        *max_value = a[length - 1];
}





void generate_array(int a[], int length)
{
    int i;
    
    for (i = 0; i < length; ++i) {
        a[i] = rand() % MAX_VALUE;
    }
}



void test()
{
    int a[MAX_NUM_ELEMS];   
    int length;
    int result_min, result_max, expected_min, expected_max;


    /*Randomly decide the number of elements in the array*/
    length = 1 + rand() % MAX_NUM_ELEMS;


    /*Fill the array with random values*/
    generate_array(a, length);

    print_array(a, length);

    /*Find the result using an efficient technique*/
    find_min_max(a, length, &result_min, &result_max);
    
    printf("Min = %d, Max = %d \n", result_min, result_max);


    /*Find the result using sorting*/
    sorting_min_max(a, length, &expected_min, &expected_max);


    /*The two results should match*/
    if (result_min != expected_min || result_max != expected_max ) {
        handle_error();
    }


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

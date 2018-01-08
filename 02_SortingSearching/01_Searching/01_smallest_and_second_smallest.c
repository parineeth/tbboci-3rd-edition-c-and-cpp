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




/*
a:input array 
length: number of elements in array a
min_value: the two smallest values will be returned here
*/
void find_two_smallest(int a[], int length, int min_value[])
{
    int i;

    min_value[0] = min_value[1] = MAX_INT;

    for (i = 0; i < length; ++i) {
        if (a[i] < min_value[0]) {
            min_value[1] = min_value[0];
            min_value[0] = a[i];
        } else if (a[i] < min_value[1]) {
            min_value[1] = a[i];
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
expected_result: the two smallest values will be returned here 
*/
void sorting_two_smallest(int a[], int length, int expected_result[])
{
    expected_result[0] = expected_result[1] = MAX_INT;

    sort(a, length);

    if (length > 0)
        expected_result[0] = a[0];

    if (length > 1) 
        expected_result[1] = a[1];
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
    int result[2], expected_result[2];


    /*Randomly decide the number of elements in the array*/
    length = 1 + rand() % MAX_NUM_ELEMS;
    if (length < 2)
        length = 2;


    /*Fill the array with random values*/
    generate_array(a, length);

    print_array(a, length);

    /*Find the result using an efficient technique*/
    find_two_smallest(a, length, result);
    
    printf("Two Smallest are = %d, %d \n", result[0], result[1]);


    /*Find the result using sorting*/
    sorting_two_smallest(a, length, expected_result);


    /*The two results should match*/
    if ( (result[0] == expected_result[0] && result[1] == expected_result[1]) 
        || (result[1] == expected_result[0] && result[0] == expected_result[1]) ) {
        /*The results match. Do nothing*/
    } else {
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

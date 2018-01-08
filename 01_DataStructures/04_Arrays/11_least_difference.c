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
#define MAX_VALUE     (100)
#define MAX_INT       (1000000)

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
Returns: the least absolute difference between any two elements in the array 
*/
int find_least_difference(int a[], int length)
{
    int i;
    int least_difference;

    assert (length > 1);

    /*Sort the array in non-decreasing order*/
    sort(a, length);

    least_difference = a[1] - a[0];
    for (i = 1; i < length - 1; ++i) {
        if (a[i+1] - a[i] < least_difference)
            least_difference = a[i+1] - a[i];
    }

    return least_difference;
}


/*
a:input array 
length: number of elements in array a
Returns: the least absolute difference between any two elements in the array 
*/
int brute_force_least_difference(int a[], int length)
{
    int i, j;
    int least_difference = MAX_INT;

    for (i = 0; i < length - 1; ++i) {
        for (j = i+1; j < length; ++j) {
            if (abs(a[i] - a[j]) < least_difference)
                least_difference = abs(a[i] - a[j]);
        }
    }

    return least_difference;
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
    int result, brute_force_result;


    /*Randomly decide the number of elements in the array*/
    length = 1 + rand() % MAX_NUM_ELEMS;

    if (length < 2)
        length = 2;


    /*Fill the array with random values*/
    generate_array(a, length);

    print_array(a, length);

    /*Find the least difference using brute force*/
    brute_force_result = brute_force_least_difference(a, length);


    /*Find the least difference using the efficient technique*/
    result = find_least_difference(a, length);
    
    printf("Least difference = %d \n", result);


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

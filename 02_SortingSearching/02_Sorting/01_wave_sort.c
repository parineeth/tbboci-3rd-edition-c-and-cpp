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

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


void print_array(int a[], int length) 
{
    int i;
    
    for (i = 0; i < length; ++i) {
        printf("%d, ", a[i]);
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

/*
a: array that has to be sorted so that the values in it alternatively increase
    and decrease. The elements should be unique
length: number of elements in the array. should be >= 1
*/
void wave_sort(int a[], int length)
{
    int i, temp;

    /*Sort the elements in ascending order*/
    qsort(a, length, sizeof(int), cmp_function);

    /*Swap the neighboring elements*/
    for (i = 1; i < length - 1; i += 2) {
        temp = a[i];
        a[i] = a[i+1];
        a[i+1] = temp;
    }
}

/*Generate an array without duplicates*/
void generate_array(int a[], int length)
{
    int i, j, temp, found;
    
    for (i = 0; i < length; ++i) {
        while (1) {
            /*Generate a random number*/
            temp = rand() % MAX_VALUE;

            /*Search if the random number is already present*/
            found = 0;
            for (j = 0; j < i; ++j) {
                if (a[j] == temp) {
                    found = 1;
                    break;
                } 
            }

            /*If the random number is already present, then try again*/
            if (found)
                continue;
            else
                break;
        }

        a[i] = temp;
    }

    
}


void test()
{
    int a[MAX_NUM_ELEMS];
    int i, length;
    int is_prev_increasing, is_cur_increasing;

    /*Randomly pick the number of elements*/
    length = 1 + rand() % MAX_NUM_ELEMS;

    /*Generate numbers in the array without any duplicates*/
    generate_array(a, length);

    printf ("Input : ");
    print_array(a, length);

    /*Perform the wave sort*/
    wave_sort(a, length);

    printf ("Output: ");
    print_array(a, length);

    
    if (length > 1) {
        is_prev_increasing = 0;
        if (a[0] < a[1])
            is_prev_increasing = 1;
    }
            
    /*Verify if the elements are alternately increasing and decreasing*/
    for (i = 1; i < length - 1; ++i) {
        is_cur_increasing = 0;
        if (a[i] < a[i+1])
            is_cur_increasing = 1;

        if (is_prev_increasing == is_cur_increasing)
            handle_error();

        is_prev_increasing = is_cur_increasing;
    }



    printf("_________________________________________________\n");
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







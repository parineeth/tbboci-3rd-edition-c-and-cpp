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
a: non-empty array from which duplicates should be removed. 
    this array will be modified in-place
length: number of elements in array a 
Returns: number of elements in array a after removing duplicates 
*/
int remove_duplicates(int a[], int length)
{
    int i, fill_pos;

    /*Sort the array*/
    sort(a, length);

    fill_pos = 1;
    for (i = 1; i < length; ++i) {
        if (a[i] != a[i - 1]) {
            a[fill_pos] = a[i];
            fill_pos++;
        }
    }

    return fill_pos;
}






void generate_array(int a[], int length)
{
    int i;
    
    for (i = 0; i < length; ++i) {
        a[i] = rand() % MAX_VALUE;
    }
}


void verify(int a[], int length) 
{
    int i, j;

    for (i = 0; i < length; ++i) {
        for (j = i+1; j < length; ++j) {
            if (a[i] == a[j]) {
                /*We found a duplicate*/
                handle_error();
            }
        }
    }
}



void test()
{
    int a[MAX_NUM_ELEMS];   
    int length1, length2;

    /*Randomly decide the number of elements*/
    length1 = 1 + rand() % MAX_NUM_ELEMS;

    /*Fill the array with random values*/
    generate_array(a, length1);

    printf ("Original array : ");
    print_array(a, length1);


    /*Remove the duplicates */
    length2 = remove_duplicates(a, length1);

    printf ("After removing duplicates : ");
    print_array(a, length2);

    verify(a, length2);


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

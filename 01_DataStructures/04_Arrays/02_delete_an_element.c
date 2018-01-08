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


/*
a: input array from which all occurences of an element should be removed
length: number of elements in array a 
x: element to be removed
Return value: number of elements in a after removing x 
*/
int remove_element(int a[], int length, int x)
{
    int i, fill_pos;

    fill_pos = 0;
    for (i = 0; i < length; ++i) {
        if (a[i] != x) {
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


void verify(int a[], int length, int x) 
{
    int i;

    for (i = 0; i < length; ++i) {
        
        if (a[i] == x) {
            /*We found x which should have been deleted*/
            handle_error();
        }

    }
}



void test()
{
    int a[MAX_NUM_ELEMS];   
    int length1, length2;
    int rand_pos, x;

    /*Randomly decide the number of elements*/
    length1 = 1 + rand() % MAX_NUM_ELEMS;

    /*Fill the array with random values*/
    generate_array(a, length1);

    /*Pick an element in array to be deleted*/
    rand_pos = rand() % length1;
    x = a[rand_pos];

    printf("Element to remove: %d\n", x);

    printf ("Original array : ");
    print_array(a, length1);


    /*Remove the element x */
    length2 = remove_element(a, length1, x);

    printf ("After removing : ");
    print_array(a, length2);

    verify(a, length2, x);


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

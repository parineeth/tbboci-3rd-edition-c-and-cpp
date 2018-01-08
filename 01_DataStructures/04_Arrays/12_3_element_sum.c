/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>




#define MAX_NUM_TESTS 50
#define MAX_NUM_ELEMS 10
#define MAX_VALUE 10




void handle_error()
{
    printf("Error occured\n");
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

void print_result(int a, int b, int c, int S)
{
    int total = a + b + c;
    printf("%d + %d + %d = %d\n", a, b, c, total);
    if (total != S)
        handle_error();
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
a: input array 
length: number of elements in the array
S: the addition of any 3 elements in array should be equal to S
Return value: Number of 3 elements subsets where sum of 3 elements is equal to S
*/
int find_3_element_sum(int a[], int length, int S) 
{
    int i, low, high, count;

    /*Sort the array in non-decreasing order*/
    sort(a, length);

    count = 0;
    for (i = 0; i < length - 2; ++i) {
        /*Choose a[i]. Start picking the other two elements from 
        opposite ends. So start choosing from i+1 on one side and 
        length - 1 on the other side
        */
        low = i + 1;
        high = length - 1;

        while (low < high) {
            int total = a[i] + a[low] + a[high];
            if (total == S) {
                count++;
                /*print result indicating that a[i], a[low] and
                a[high] will sum to S*/
                print_result(a[i], a[low], a[high], S);
                ++low;
                --high;
            } else if (total > S) {
                --high; /*We need to pick a smaller element*/
            } else {
                ++low; /*We need to pick a larger element*/
            }
        }
    }

    return count;
}



void test()
{
    int a[MAX_NUM_ELEMS];
    int i;
    int length = 1 + rand() % MAX_NUM_ELEMS; /*randomly choose size of array*/
    int S = 0;

    for (i = 0; i < length; ++i) {
        /*Randomly choose the value of elements in the array*/
        a[i] = rand() % MAX_VALUE;

        /*Alternate elements will be negative*/
        if (i % 2 == 0) 
            a[i] = -1 * a[i];
    }

    printf("Input : ");
    print_array(a, length);

    find_3_element_sum(a, length, S);

    printf("________________________________________________\n");
}


int main() {
    int i;
    for (i = 0; i < MAX_NUM_TESTS; ++i) {
        test();
    }

    printf("Test passed\n");
    return 0; 
}


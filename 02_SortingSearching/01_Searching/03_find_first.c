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
#define MAX_VALUE   (10)

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}

/*
a: array being searched
n: number of elements in array
x: element being searched
Return value: first position of x in a, if x is absent -1 is returned
*/
int find_first(int a[], int n, int x)
{
    int start, end, mid;

    start = 0;
    end = n - 1;

    while (start <= end) {
        mid = (start + end) / 2;

        if (a[mid] == x) {
            if (mid == 0 || a[mid - 1] != x)
                 return mid;
            else
                 end = mid - 1;

        } else if (a[mid] > x) {
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    return -1;
}


/*Sort in ascending order using bubble sort*/
void sort_array(int a[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; ++i) {
        for (j = i + 1; j < n; ++j) {
            if (a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

int find_first_brute_force(int a[], int n, int x)
{
    int i;
    for (i = 0; i < n; ++i) {
        if (a[i] == x)
            return i;
    }
    return -1;
}

void print_array(int a[], int n)
{
    int i;

    for (i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }

    printf("\n");
}

void print_result(int result, int x)
{
    printf("The position of first occurence of %d is %d\n", x, result);
}

void test_01()
{
    int a[MAX_NUM_ELEMS];
    int i, n ; 
    int result, expected_result;
    int x; /*Item to be searched*/

    /*Number of elements in the array*/
    n = 1 + rand() % MAX_NUM_ELEMS;

    for (i = 0; i < n; ++i) {
        a[i] = rand() % MAX_VALUE;
    }

    sort_array(a, n);

    printf("Input : ");
    print_array(a, n);

    /*Search all elements that are present and verify the result */
    for (i = 0; i < n; ++i) {
        x = a[i];

        result = find_first(a, n, x);

        print_result(result, x);

        expected_result = find_first_brute_force(a, n, x);
        if (expected_result != result)
            handle_error();
    }



    /*Search for a non-existent item. Result should be -1*/
    x = MAX_VALUE + 1;
    result = find_first(a, n, x);
    print_result(result, x);
    if (result != -1) 
        handle_error();

    printf("_____________________________________________\n");
}


int main()
{
    int i;

    for (i = 0; i < MAX_NUM_TESTS; ++i)
        test_01();

    printf("Test passed\n");

    return 0;
}

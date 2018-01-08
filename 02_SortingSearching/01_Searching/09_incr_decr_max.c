/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT (-999999)

void handle_error()
{
    printf("Error occured\n");
    exit(1);
}

/*
a: array where elements first increase and then decrease
n: number of elements in the array, n > 0
Return value: maximum element in the array
*/
int find_max(int a[], int n)
{
    int start = 0, end = n-1, mid, max_element = MIN_INT;
    
    while (start <= end) {
        /*If only one element is left, then it is the max element*/
        if (start == end)   {
            max_element = a[start];
            break;
        }

        /*If two elements are left, find the maximum of the two*/
        if (start + 1 == end) {
            max_element = a[start];
            if (a[start+1] > max_element)
                max_element = a[start+1];
            break;
        }

        /*If there are more than two elements left, then inspect the
        middle element between start and end */
        mid = (start+end)/2;

        /*If middle element is greater than previous element and also 
        greater than the next element, then it is the maximum element*/
        if (a[mid - 1] < a[mid] && a[mid] > a[mid + 1]) {
            max_element = a[mid];
            break;
        }

        /*We have not yet been able to find the max. So modify the range 
        in which the search should proceed in the next iteration */
        if (a[mid - 1] < a[mid] && a[mid] < a[mid + 1]) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return max_element;
}


void print_array(int a[], int n)
{
    int i;

    for (i = 0; i < n; ++i) {
        printf("%d ", a[i]);
    }

    printf("\n");
}



void test_01()
{
    int a[] = {50, 40, 30, 20, 10};
    int n = 5;
    int result;

    print_array(a, n);
    result = find_max(a, n);

    printf("Maximum element = %d\n", result);

    if (result != 50)
        handle_error();

    printf("_________________________________________\n");
}

void test_02()
{
    int a[] = {30, 50, 40, 30, 20};
    int n = 5;
    int result;

    print_array(a, n);
    result = find_max(a, n);

    printf("Maximum element = %d\n", result);

    if (result != 50)
        handle_error();

    printf("_________________________________________\n");
}

void test_03()
{
    int a[] = {30, 40, 50, 20, 10};
    int n = 5;
    int result;

    print_array(a, n);
    result = find_max(a, n);

    printf("Maximum element = %d\n", result);

    if (result != 50)
        handle_error();

    printf("_________________________________________\n");
}

void test_04()
{
    int a[] = {10, 20, 30, 50, 10};
    int n = 5;
    int result;

    print_array(a, n);
    result = find_max(a, n);

    printf("Maximum element = %d\n", result);

    if (result != 50)
        handle_error();

    printf("_________________________________________\n");
}


void test_05()
{
    int a[] = {10, 20, 30, 40, 50};
    int n = 5;
    int result;

    print_array(a, n);
    result = find_max(a, n);

    printf("Maximum element = %d\n", result);

    if (result != 50)
        handle_error();

    printf("_________________________________________\n");
}




int main()
{
    test_01();

    test_02();

    test_03();

    test_04();

    test_05();

    printf("Test passed\n");

    return 0;
}

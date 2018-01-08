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
a: array of size m+n which has m elements at beginning and n spaces at end
b: array of size n with n elements
m: number of elements in array a
n: number of elements in array b
*/
void merge_arrays(int a[], int b[], int m, int n)
{
    int i, j, fill_pos;

    i = m - 1;
    j = n - 1;
    fill_pos = m + n - 1; /*Start filling from the rear of the array*/

    while (i >= 0 && j >= 0) {
        if (a[i] > b[j]) {
            a[fill_pos--] = a[i--];
        } else {
            a[fill_pos--] = b[j--];
        }
    }

    /*Fill up the remaining elements of array a if any*/
    while (i >= 0)
        a[fill_pos--] = a[i--];

    /*Fill up the remaining elements of array b if any*/
    while (j >= 0)
        a[fill_pos--] = b[j--];

}



void print_array(int m[], int num_elems)
{
    int i;
    int prev;

    for (i = 0; i < num_elems; ++i) {
        printf("%d ", m[i]);

        if (i > 0 && prev > m[i])
            handle_error();

        prev = m[i];
    }

    printf("\n");
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


void test_01()
{
    /*Generate two random values m and n*/
    int n = rand() % MAX_NUM_ELEMS;
    int m = rand () % MAX_NUM_ELEMS;

    /*Let a have size of (m+n) and b have a size of n*/
    int *a = (int*) calloc(m+n, sizeof(int));
    int *b = (int*) calloc(n, sizeof(int));

    int i;

    /*Generate m random values in a*/
    for (i = 0; i < m; ++i) {
        a[i] = rand() % MAX_VALUE;
    }

    /*Generate n random values in b*/
    for (i = 0; i < n; ++i) {
        b[i] = rand() % MAX_VALUE;
    }

    /*Sort the two arrays*/
    sort_array(a, m);
    sort_array(b, n);

    printf("Input1 : ");
    print_array(a, m);
    printf("Input2 : ");
    print_array(b, n);

    /*Merge the arrays*/
    merge_arrays(a, b, m, n);

    printf("Output : ");
    print_array(a, m +n);

    printf("____________________________________________\n");

    free(a);
    free(b);
}


int main()
{
    int i;

    for (i = 0; i < MAX_NUM_TESTS; ++i) {
        test_01();
    }

    printf("Test passed\n");
    return 0;
}

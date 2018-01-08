/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE (100)
#define MAX_INT (1000000)

void handle_error()
{
    printf("Test failed \n");
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


/*a: a[i] contains the maximum number of locations we can jump from position i
n: number of elements in the array. Should be >= 1
Return value: minimum number of jumps needed to reach the end of the array*/
int find_min_jumps(int a[], int n)
{
    int i, j, result;
    int *min_jumps = (int *) calloc(n, sizeof(int));

    for (i = 1; i < n; ++i) {
        min_jumps[i] = MAX_INT;
        /*Compute the minimum number of jumps to reach location i by looking
        at the previous locations 0 to i - 1*/
        for (j = 0; j < i; ++j) {
            if (j + a[j] >= i && min_jumps[j] + 1 < min_jumps[i]) {
                min_jumps[i] = min_jumps[j] + 1;
            }
        }
    }

    result = min_jumps[n-1];
    free(min_jumps);
    return result;
}





void test()
{
    int a[MAX_ARRAY_SIZE] = {2, 0, 2, 3, 1, 4, 2, 1, 2, 1};
    int n = 10;

    int result, expected_result;

    printf("Input: ");
    print_array(a, n);

    result = find_min_jumps(a, n);
    expected_result = 4;

    printf("Minimum jumps = %d\n", result);

    if (result != expected_result)
        handle_error();
    
    printf("\n");  
}








int main()
{
    test();

    printf("Test passed\n");
    return 0;
}

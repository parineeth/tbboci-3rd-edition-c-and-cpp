/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>

/*Helper function which reverses an array in region (low, high)
a: array which needs to be reversed
low: lower index of region to be reversed
high: higher index of region to be reversed
*/
void reverse_array(int a[], int low, int high)
{
    int temp;

    while (low < high) {
        temp = a[low];
        a[low] = a[high];
        a[high] = temp;
        low++;
        high--;
    }
}

/*Main function to rotate a 1 dimensional array
a: array which should be rotated. 
length: number of elements in the array. Should be > 0
num_rotations: how many times to rotate the array. Should be >= 0
*/
void rotate_array(int a[], int length, int num_rotations)
{
    /*Suppose an array has a length of 5, every time we rotate by 5 
    locations, we end up with the same array. So obtain num_rotations 
    value from 0 to length - 1*/
    num_rotations = num_rotations % length;

    if (num_rotations == 0)
        return;

    reverse_array(a, 0, length - 1);

    reverse_array(a, 0, num_rotations - 1);

    reverse_array(a, num_rotations, length - 1);
}


void handle_error()
{
    printf("Error occured \n");
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

void compare_arrays(int input[], int expected_result[], int length)
{
    int i;
    
    for (i = 0; i < length; ++i) {
        if (input[i] != expected_result[i]) 
            handle_error();
    }

}   


void perform_test(int input[], int length, int num_rotations, int expected_result[])
{
    printf("Num Rotations = %d\n", num_rotations);

    printf("Before Rotating: ");
    print_array(input, length);

    rotate_array(input, length, num_rotations);
    compare_arrays(input, expected_result, length);

    printf("After  Rotating: ");
    print_array(input, length); 

    printf("________________________________________\n");   
}


void test1() 
{
    int input[] = {10};
    int expected_result[] = {10};
    int length = 1, num_rotations = 1;

    perform_test(input, length, num_rotations, expected_result);
}


void test2() 
{
    int input[] = {10, 20, 30, 40, 50};
    int expected_result[] = {50, 10, 20, 30, 40};
    int length = 5, num_rotations = 1;

    perform_test(input, length, num_rotations, expected_result);
}


void test3() 
{
    int input[] = {10, 20, 30, 40, 50};
    int expected_result[] = {40, 50, 10, 20, 30};
    int length = 5, num_rotations = 2;

    perform_test(input, length, num_rotations, expected_result);    
}


void test4() 
{
    int input[] = {10, 20, 30, 40, 50};
    int expected_result[] = {20, 30, 40, 50, 10};
    int length = 5, num_rotations = 4;

    perform_test(input, length, num_rotations, expected_result);    
}

void test5() 
{
    int input[] = {10, 20, 30, 40, 50};
    int expected_result[] = {10, 20, 30, 40, 50};
    int length = 5, num_rotations = 5;

    perform_test(input, length, num_rotations, expected_result);        
}



int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();

    printf("Test passed\n");
    return 0;
}


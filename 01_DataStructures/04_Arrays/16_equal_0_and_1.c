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
#define MAX_VALUE     (2)
#define MIN_INT       (-1000000)

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
a:input array 
num_elements: number of elements in array a
start_index: start index of longest subarray of equal 0's and 1's is returned 
end_index: end index of longest subarray of equal 0's and 1's is returned 
Returns: the length of the longest subarray with equal 0's and 1's  
*/
int find_sub_array(int a[], int num_elements, int *start_index, int *end_index)
{
    int i, running_sum, max_length;
    int *first_ix_for_sum = (int*) malloc((2*num_elements + 1) * sizeof (int) );
    int normalized_sum;

    /*first_ix_for_sum will store the first seen index for a particular  
    normalized running sum. Initialize the sum table. MIN_INT should be < -1 
    normalized running sum = num_elements + running_sum*/
    for (i = 0; i < (2 * num_elements + 1); ++i)
        first_ix_for_sum[i] = MIN_INT;

    /*Before we start processing, we say that at index -1, running sum is 0
    The normalized running sum =  num_elements + running_sum = num_elements
    + 0 = num_elements. So first_ix_for_sum[num_elements] is set to -1*/
    first_ix_for_sum[num_elements] = -1;
    max_length = running_sum = 0;
    *start_index = *end_index = -1;
    for (i = 0; i < num_elements; ++i) {
        /*If we get a 1, increment the running sum. If we get a 0
        then decrement the running sum*/
        if (a[i])
            running_sum++;
        else
            running_sum--;

        /*If there are 10 elements, then running sum can vary from -10  
        to +10. Normalize the running sum into an index from 0 to 20*/
        normalized_sum = num_elements + running_sum;
        if (first_ix_for_sum[normalized_sum] == MIN_INT) {
            /*We are observing the normalized running sum 
            for the first time. Store the index in first_ix_for_sum*/
            first_ix_for_sum[normalized_sum] = i;
        } else {
            /*We have already observed the normalized running sum
            before. Suppose we have a normalized running sum of 3
            at index 10 and we again observe normalized running sum
            of 3 at index 18, then there are equal 0's and 1's 
            from index 11 to index 18*/
            int first_index = first_ix_for_sum[normalized_sum];
            if (i - first_index > max_length) {
                max_length = i - first_index;
                *start_index = first_index + 1;
                *end_index = i; 
            }
        }       
    }

    free(first_ix_for_sum); 
    return max_length;
}


/*
a:input array 
num_elements: number of elements in array a
Returns: length of longest subarray with equal 0's and 1's   
*/
int brute_force_sub_array(int a[], int num_elements)
{
    int i, j, length, max_length = 0;
    
    for (i = 0; i < num_elements - 1; ++i) {
        /*If we get a 1 we add 1 to running sum, if we get a 0, 
        we subtract -1*/
        int running_sum = (2 * a[i]) - 1;
        
        for (j = i+1; j < num_elements; ++j) {
            running_sum += (2 * a[j]) - 1;
            if (running_sum == 0) {
                length = j - i + 1;
                if (length > max_length) 
                    max_length = length;
            }
        }
    }

    return max_length;
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
    int start_index, end_index;

    /*Randomly decide the number of elements in the array*/
    length = 1 + rand() % MAX_NUM_ELEMS;

    if (length < 2)
        length = 2;


    /*Fill the array with random values*/
    generate_array(a, length);

    print_array(a, length);

    /*Find the length of longest sub-array with equal 0's and 1's 
    using the efficient technique*/
    result = find_sub_array(a, length, &start_index, &end_index);

    printf("Length of longest sub array with equal 0's and 1's  = %d, \n\t(start index = %d, end index = %d) \n", 
            result, start_index, end_index);

    /*Find the length of longest sub-array with equal 0's and 1's 
    using brute force*/
    brute_force_result = brute_force_sub_array(a, length);

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

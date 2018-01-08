/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"



void print_combination(int input[], char is_selected[], int length, int subset_size)
{
    int i, num_printed;

    printf("{");
    
    num_printed = 0;
    for(i = 0; i < length; ++i) {
        if (is_selected[i]) {
            printf("%d ", input[i]);
            ++num_printed;
            if (num_printed >= subset_size)
                break;
        }
    } 

    printf("}\n");
}


/*
input: input array containing the elements  
is_selected: if is_selected[i] = 1, then the ith element of 
    the input array is present in the current subset
pos: current position in the input 
length: total number of elements present in input
subset_size: total number elements that should be present in the final subset
cur_num_selections: currently how many elements have been selected
*/
void generate_combinations(int input[], char is_selected[], int pos, int length,
            int subset_size, int cur_num_selections)
{
    if (cur_num_selections == subset_size) {
        print_combination(input, is_selected, length, subset_size);
        return; /*Terminate the recursion*/
    }
    
    if (pos >= length) {
        return; /*Terminate the recursion*/
    }

    /*Exclude the item from the subset*/
    is_selected[pos] = 0;

    generate_combinations(input, is_selected, pos+1, length, subset_size,
                cur_num_selections);

    /*Include the item in the subset*/
    is_selected[pos] = 1;

    generate_combinations(input, is_selected, pos+1, length, subset_size,
                cur_num_selections + 1);
}







void test(int *input, int length, int subset_size)
{
    char *is_selected = (char*) malloc(length);

    printf("Number of elements in subset = %d\n", subset_size);

    generate_combinations(input, is_selected, 0,  length, 
                subset_size, 0);

    free(is_selected);

    printf("______________________________\n\n");
}


int main()
{
    int array1[] = {0, 1, 2, 3, 4};
    int length = 5;
    int subset_size;

    /*Compute 5C0 to 5C5*/
    for (subset_size = 0; subset_size < length + 1; ++subset_size) {
        test(array1, length, subset_size);
    }

    printf("Test passed\n");
    return 0;
}




/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"



/*Helper function for printing a subset
input: array containing the input elements 
selection: if bit i is 1 in selection, then element i is present in subset
length: number of elements in the array
*/
void print_subset(int input[], int selection, int length) {
    int i;
    printf("{");

    for (i = 0; i < length; ++i) {
        if (selection & (1u << i)) 
            printf("%d ", input[i]);
    }

    printf("}\n");  
}

/*Main function for generating the subsets
input: array containing the input elements
length: number of elements in the array
*/
void generate_subsets(int input[], int length) 
{
    int i = 0;
    int num_subsets = 1u << length;

    while (i < num_subsets) {
        print_subset(input, i, length);
        ++i;
    }
}

void test(int input[], int length) 
{
    generate_subsets(input, length);
    printf("______________________________\n\n");
}

/*Print subset if recursion is used*/
void print_subset_r(int input[], char is_selected[], int length)
{
    int i;

    printf("{");
    
    for(i = 0; i < length; ++i) {
        if (is_selected[i]) {
            printf("%d ", input[i]);
        }
    } 

    printf("}\n");
}



/*Generating power set recursively
input: array containing the elements for which we have to find the power set 
is_selected: array used for computation. If is_selected[i] = 1, then
the ith element of the array is present in the current subset
pos: current position in the input which is being processed
length: length of the original input
*/
void generate_subsets_r(int input[], char is_selected[], int pos, int length)
{
    /*Recursion termination condition*/
    if (pos >= length) {
        print_subset_r(input, is_selected, length);
        return ;
    }

    is_selected[pos] = 0;
    generate_subsets_r(input, is_selected, pos+1, length);

    is_selected[pos] = 1;
    generate_subsets_r(input, is_selected, pos+1, length);

}






void test_r(int *input, int length)
{
    char *is_selected = (char*) malloc(length+1);

    generate_subsets_r(input, is_selected, 0,  length);

    free(is_selected);

    printf("______________________________\n\n");
}





int main()
{
    int array1[] = {};
    int array2[] = {0};
    int array3[] = {0, 1, 2};
    int length;

    length = 0;
    test(array1, length);

    length = 1;
    test(array2, length);

    length = 3;
    test(array3, length);

    printf("Test passed\n");
    return 0;
}




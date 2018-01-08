/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


/*
strings: sorted array of strings in which some of the strings can be empty ("")
num_strings: number of strings present (including empty strings)
x: string to be searched
Returns: index of x in the array strings if found, -1 otherwise
*/
int search(char *strings[], int num_strings, char *x)
{
    int mid, result;
    int low = 0;
    int high = num_strings - 1;
    
    while (low <= high) {
        /*If we hit an empty string at position high, then keep decreasing
        high till we get a non-empty string*/
        while (low <= high && strcmp(strings[high], "") == 0) {
            --high;
        }

        /*If we have only empty strings between low and high, then return
        not found*/
        if (low > high)
            return -1;

        mid = (low + high) / 2;

        /*If we get an empty element at mid, then keep incrementing mid. 
        We are guaranteed to find a non-empty string since strings[high]
        is non-empty*/
        while (strcmp(strings[mid], "") == 0)
            mid = mid + 1; 

        /*Compare the mid element with the element being searched*/
        result = strcmp(strings[mid], x);

        if (result == 0) {
            return mid;
        } else if (result < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}




void test(char *strings[], int num_strings, char *x, int expected_result)
{
    int i, result;

    result = search(strings, num_strings, x);

    printf("Input: [");
    for (i = 0; i < num_strings; ++i) {
        printf("\"%s\", ", strings[i]);
    }
    printf("]\n");

    printf("Searching %s: Postion = %d\n", x, result);

    if (result != expected_result) {
        handle_error();
    }
    printf("______________________________________________\n");
} 



int main()
{
    char *strings[13] = {"", "apple", "", "", "ball", "cat", "", "dog", "", "", "", "egg", ""};

    test(strings, 13, "apple", 1); 

    test(strings, 13, "ball", 4);

    test(strings, 13, "cat", 5);

    test(strings, 13, "dog", 7);

    test(strings, 13, "egg", 11);


    test(strings, 13, "air", -1);

    test(strings, 13, "film", -1);

    printf("Test passed\n");
    return 0;
}

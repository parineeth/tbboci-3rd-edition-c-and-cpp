/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>


#define NUM_CHARACTERS 256

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}



/*Returns 1 if there is at least one permutation of string str1 which is a  
    palindrome, 0 otherwise*/
int is_permutation_palindrome(char str1[])
{
    int i = 0, num_odd_char;
    int count[NUM_CHARACTERS];

    for (i = 0; i < NUM_CHARACTERS; ++i)
        count[i] = 0;

    /*Find out how many times a character appears in the string*/
    i = 0;
    while(str1[i]) {
        count[(int)str1[i]]++;
        i++;
    }

    num_odd_char = 0;
    for (i = 0; i < NUM_CHARACTERS; ++i) {
        if (count[i] % 2 == 1)
            num_odd_char++;

        /*If there are 2 or more characters that appear odd number of 
        times then we can't form a palindrome with any permutation of 
        the string*/
        if (num_odd_char >= 2)
            return 0;
    }

    return 1;
}


void test(char str1[], int expected_result)
{
    int result;

    result = is_permutation_palindrome(str1);

    if (result)
        printf("Permutation of %s is a palindrome\n", str1);
    else
        printf("Permutation of %s is NOT a palindrome\n", str1);
    
    if (result != expected_result)
        handle_error();
}


int main()
{
    test("elelv", 1); /*palindrome is level*/
    test("ab", 0);

    printf("Test passed\n");
    return 0;
}

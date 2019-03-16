/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define NUM_CHARACTERS 256

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}




/*
str1, str2: the two non-NULL strings which we want to compare
Return value: 1 if the two strings are anagrams, 0 otherwise
*/
int are_strings_anagrams( char *str1, char *str2)
{
    int count1[NUM_CHARACTERS], count2[NUM_CHARACTERS];
    int is_anagram, i;

    /*Initialize the counts to zero */
    memset(count1, 0, sizeof(int) * NUM_CHARACTERS);
    memset(count2, 0, sizeof(int) * NUM_CHARACTERS);
    
    /*Compute the character counts for str1 and str2*/
    while (*str1) {
        count1[(int)*str1]++;
        str1++;
    }
    
    while (*str2) {
        count2[(int)*str2]++;
        str2++;
    }
    
    /*Compare the counts*/
    is_anagram = 1;
    for (i = 0; i < NUM_CHARACTERS; ++i) {
        if (count1[i] != count2[i]) {
            is_anagram = 0;
            break;
        }
    }
    return is_anagram;
}

 void test(char s1[], char s2[], int expected_result) {
    int result;

    result = are_strings_anagrams(s1, s2);

    printf("%s and %s are ", s1, s2);
    if (result)
        printf("anagrams\n");
    else
        printf("not anagrams\n");

    if (result != expected_result) {
        handle_error();
    }
    
}


int main()
{
    test("ABCDE", "CDBAE", 1);

    test("AAAAA", "BBBBB", 0);

    printf("Test passed \n");
    return 0;
}

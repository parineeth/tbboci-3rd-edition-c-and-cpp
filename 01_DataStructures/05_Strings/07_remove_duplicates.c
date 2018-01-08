/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_STRING_LENGTH 100
#define MAX_NUM_CHARACTERS 256

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}



/*str1: string from which duplicate characters should be removed*/
void remove_duplicates(char *str1) {
    int i, length, fill_pos;
    char c, was_char_observed[MAX_NUM_CHARACTERS];

    if (!str1)
        return;

    length = strlen(str1);
    if (length < 2)
        return;

    memset(was_char_observed, 0, MAX_NUM_CHARACTERS * sizeof(char));
    
    c = str1[0];
    was_char_observed[(int)c] = 1;
    fill_pos = 1;
    for (i = 1; i < length; ++i) {
        c = str1[i];
        
        /*Only if current character was not observed so far, add the 
        current character to fill position and advance fill position*/
        if (!was_char_observed[(int)c]) {
            str1[fill_pos] = c;
            fill_pos++;
        }
        was_char_observed[(int)c] = 1;
    }
    /*Insert the termination \0 at the end of str1*/
    str1[fill_pos] = 0;
}


void test(char str1[], char expected_result[])
{
    printf("%s ", str1);

    remove_duplicates(str1);

    printf("=>  %s\n", str1);

    if (strcmp(str1, expected_result) != 0)
        handle_error();

}









int main()
{
    char str1[MAX_STRING_LENGTH];

    str1[0] = 0;    
    test(str1, "");

    strcpy(str1, "a");
    test(str1, "a");

    strcpy(str1, "1aaaaaa2bbbaaaaa3cccccaaaabbb");
    test(str1, "1a2b3c");


    printf("Test passed\n");
    return 0;
}

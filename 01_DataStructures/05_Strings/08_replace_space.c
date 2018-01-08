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

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


/*str1: string in which space characters (' ') should be replaced with %20.
    There is sufficient free space at the end of the string to 
    accomodate the extra characters needed
*/
void replace_space(char *str1)
{
    int i, num_spaces, length, fill_pos;

    /*Count the number of spaces*/
    i = num_spaces = 0;
    while (str1[i]) {
        if (str1[i] == ' ')
            num_spaces++;
        ++i;
    }
    length = i;

    fill_pos = length + (2 * num_spaces);
    str1[fill_pos] = 0; /*Insert the string termination character*/
    fill_pos--; /*fill_pos is now at original length + (2*num_spaces) - 1*/

    /*Keep copying characters from rear of original string to fill position*/
    i = length - 1;
    while ( i >= 0) {
        if (str1[i] == ' ') {
            /*If we get a space, then place "%20" at fill position*/
            str1[fill_pos] = '0';
            str1[fill_pos - 1] = '2';
            str1[fill_pos - 2] = '%';
            fill_pos = fill_pos - 3;
        } else {
            /*Copy the character to fill position*/
            str1[fill_pos] = str1[i];
            fill_pos--;
        }
        --i;
    }
}



void test(char str1[], char expected_result[])
{
    printf("%s ", str1);

    replace_space(str1);

    if (strcmp(str1, expected_result) != 0)
        handle_error();

    printf("=>  %s\n", str1);
}









int main()
{
    char str1[MAX_STRING_LENGTH];

    str1[0] = 0;    
    test(str1, "");

    strcpy(str1, "a");
    test(str1, "a");

    strcpy(str1, " Hello  how are you ");
    test(str1, "%20Hello%20%20how%20are%20you%20");


    printf("Test passed\n");
    return 0;
}

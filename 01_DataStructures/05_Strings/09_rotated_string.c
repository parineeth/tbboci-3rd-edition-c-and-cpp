/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


/*
str1 and str2 are the two strings which need to be checked
Return value: 1 if the two strings are rotations of each other, 0 otherwise
*/
int is_string_rotation(char *str1, char *str2)
{
    char *str3;
    int is_rotation;
    int length1, length2;

    if (!str1 || !str2)
        return 0;

    length1 = strlen(str1);
    length2 = strlen(str2);

    /*If lengths of two strings are not equal, then they can't be rotations*/
    if (length1 != length2)
        return 0;

    str3 = (char*) malloc(2*length1 + 1);

    strcpy(str3, str1);
    strcat(str3, str1);

    is_rotation = 0;

    /*
    strstr(str3, str2) returns the pointer to first occurence of str2 in str3.
    So if strstr returns a non-null pointer, then str2 is a substring of str3
    */
    if (strstr(str3, str2))
        is_rotation = 1;

    free(str3);

    return is_rotation;
}


void test(char *str1, char *str2, int expected_result)
{
    int result;

    result = is_string_rotation(str1, str2);

    printf("%s and %s are ", str1, str2);
    if (result)
        printf("rotations of each other\n");
    else 
        printf("NOT rotations of each other\n");


    if (result != expected_result)
        handle_error();
}


int main()
{

    test("ABCDE", "CDEAB", 1);
    test("ABCDE", "EABCD", 1);
    test("AAA", "BBB", 0);

    printf("Test passed \n");
    return 0;
}

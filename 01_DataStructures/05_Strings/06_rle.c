/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH (100)

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


/*Performs run length encoding on a string
str1: input string (example: "aaabb")
str2: output string (example: "a3b2")
*/
void run_length_encode(char *str1, char *str2) 
{
    char c;
    int pos1, pos2, count;

    if (str1 == NULL || str2 == NULL)
        return;

    pos1 = pos2 = 0;
    while (1) {
        c = str1[pos1];
        if (c == '\0')  /*If we have reached end of string, then break*/
            break;
    
        /*Count the number of consecutive occurences of character c*/
        count = 0;
        while (c == str1[pos1]) {
            count++;
            pos1++;
        }

        /*Store character c in the output string*/
        str2[pos2] = c;
        pos2++;

        /*Store the count in the output string. sprintf returns the 
        number of characters appended to str2. So add it to pos2 */
        pos2 += sprintf(&str2[pos2], "%d", count);
    }
    str2[pos2] = '\0';  
}


void test(char *str1, char *expected_result)
{
    char *result = (char*) malloc(MAX_STRING_LENGTH);
    
    run_length_encode(str1, result);
    printf("%s => %s\n", str1, result);

    if (strcmp(result, expected_result) != 0)
        handle_error();
    
    free(result);
}

int main()
{
    test("", "");
    test("a", "a1");
    test("abcde", "a1b1c1d1e1");
    test("aaabcccbba", "a3b1c3b2a1");
    
    printf("Test passed\n");

    return 0;
}

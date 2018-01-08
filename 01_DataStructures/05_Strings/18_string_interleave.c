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


/*
str1, str2: two non-NULL input strings that have to be interleaved
buffer: string that contain the result of interleaving 
pos: current position in the buffer
*/
void string_interleave(char *str1, char *str2, char *buffer, int pos) 
{
    /*If we have finished processing both strings, print the buffer and
    terminate the recursion*/
    if (!str1[0] && !str2[0]) {
        buffer[pos] = '\0';
        printf("%s\n", buffer);
        return;
    }

    /*If we have finished processing str2, concatenate str1 to the buffer,
    print the buffer and terminate the recursion*/
    if (!str2[0]) {
        buffer[pos] = '\0';
        strcat(&buffer[pos], str1);
        printf("%s\n", buffer);
        return;
    }

    /*If we have finished processing str1, concatenate str2 to the buffer,
    print the buffer and terminate the recursion*/
    if (!str1[0]) {
        buffer[pos] = '\0';
        strcat(&buffer[pos], str2);
        printf("%s\n", buffer);
        return;
    }


    /*Include the next character of str1 into the buffer*/
    buffer[pos] = *str1;
    string_interleave(str1+1, str2, buffer, pos + 1);

    /*Include the next character of str2 into the buffer*/
    buffer[pos] = *str2;
    string_interleave(str1, str2+1, buffer, pos + 1);   
}



int main() 
{
    char buffer[MAX_STRING_LENGTH];

    string_interleave("abcde", "123", buffer, 0);

    printf("Test passed\n");
    return 0;
}

/*
Copyright (C) 2017 Interview Druid, Parineeth M. R.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"




/*
str1: valid input string whose permutations have to be formed
buf: array for storing the current permutation
pos: current position in the buf array
visited: indicates if character in input string has already been visited
length: length of the input string
*/
void generate_permutations(char *str1, char *buf, unsigned int pos,
            int *visited, unsigned int length)
{
    unsigned int i;

    /*Recursion termination condition*/
    if (pos == length) {
        buf[pos] = 0;
        printf("%s\n", buf);
        return ;
    }

    for (i = 0; i < length; ++i) {
        if (visited[i] == 0) {
            buf[pos] = str1[i];
            visited[i] = 1;
            generate_permutations(str1, buf, pos+1, visited, length);
            visited[i] = 0;
        }
    }
}







void test(char *str1)
{
    unsigned int length = strlen(str1);

    char *buf = (char*) malloc(length + 1);

    int *visited = (int*) calloc(length, sizeof(int));

    printf("Input: %s\n", str1);

    generate_permutations(str1, buf, 0, visited, length);

    free(visited);

    free(buf);

    printf("______________________________\n\n");
}


int main()
{
    test("");
    test("A");
    test("ABCDE");

    printf("Test passed\n");
    return 0;
}




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
str: valid input string from which words have to be generated
buf: array for storing the current word that has been generated
pos: current position in the buf array
visited: indicates if character in input string has already been visited
length: length of the input string
*/
void generate_words(char *str, char *buf, unsigned int pos,
            int *visited, unsigned int length)
{
    unsigned int i;

    /*Output all strings that we generate*/
    buf[pos] = 0;
    printf("%s\n", buf);

    /*Recursion termination condition*/
    if (pos >= length) {
        return;
    }

    for (i = 0; i < length; ++i) {
        if (visited[i] == 0) {
            buf[pos] = str[i];
            visited[i] = 1;
            generate_words(str, buf, pos+1, visited, length);
            visited[i] = 0;
        }
    }
}







void test(char *str)
{
    unsigned int length = strlen(str);

    char *buf = (char*) malloc(length + 1);

    int *visited = (int*) calloc(length, sizeof(int));

    generate_words(str, buf, 0, visited, length);

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




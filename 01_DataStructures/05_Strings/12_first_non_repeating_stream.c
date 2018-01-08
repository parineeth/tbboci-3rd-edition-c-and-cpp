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
#define MAX_POS 1000000
#define MAX_NUM_CHARS 256

void handle_error(void)
{
    printf("Test failed\n");
    exit(1);
}


struct stream_param {
    /*If we have seen the character 2 or more times in the stream,
    then is_repeated[character] = 1*/
    char is_repeated[MAX_NUM_CHARS]; 

    /*For every character, we maintain the position of its first
    occurence. If the character has not yet occured in stream, we store -1 */
    int first_pos[MAX_NUM_CHARS]; 

    char first_unique; /*the first unique character in the stream*/
    int cur_pos;    /*the current position in the stream*/
};

/*
stream_param: contains the parameters for processing the stream 
cur_char: indicates the current character in the stream
Returns: first unique character in the stream if it exists, # otherwise
*/
char first_unique_in_stream(struct stream_param *p, char cur_char)
{
    if (p->first_pos[(int)cur_char] == -1) {
        /*We are seeing the character for the first time in the stream. So
        update its first position*/
        p->first_pos[(int)cur_char] = p->cur_pos;

        /*If there are no unique characters in the stream, then make this
        the first unique character*/
        if (p->first_unique == '#') {
            p->first_unique = cur_char;
        }

        p->cur_pos = p->cur_pos + 1;
        return p->first_unique;
    }

    /*We have already seen this character before*/
    p->is_repeated[(int)cur_char] = 1;

    /*If the current character is the first unique character in the stream, 
    then we need to replace it with next unique character*/
    if (p->first_unique == cur_char) {
        int i, smallest_pos; 
        
        /*Find the first character that occurs only once in stream*/
        smallest_pos = MAX_POS;
        p->first_unique = '#';
        for (i = 0; i < MAX_NUM_CHARS; ++i) {
            if (p->is_repeated[i] == 0 && p->first_pos[i] != -1
               && p->first_pos[i] < smallest_pos) {
                smallest_pos = p->first_pos[i];
                p->first_unique = i;
            }
        }
    }

    p->cur_pos = p->cur_pos + 1;
    return p->first_unique;
}


void test(char str[], char expected_result[])
{
    int i, length;
    char result;
    struct stream_param p;

    printf("%s ", str);

    printf("=> ");

    for (i = 0; i < MAX_NUM_CHARS; ++i) {
        p.is_repeated[i] = 0;
        p.first_pos[i] = -1;
        p.first_unique = '#';
        p.cur_pos = 0;
    }

    length = strlen(str);
    for (i = 0; i < length; ++i) {
        result = first_unique_in_stream(&p, str[i]);

        if (result != expected_result[i])
            handle_error();

        if (result == 0) 
            printf(" ");
        else        
            printf("%c", result);
    }

    printf("\n");
}









int main()
{

    test("", "");

    test("a", "a");

    test("aaabcdeb", "a##bbbbc");


    printf("Test passed\n");
    return 0;
}

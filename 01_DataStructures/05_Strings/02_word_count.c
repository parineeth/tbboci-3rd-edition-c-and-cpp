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

/*Helper function which checks if a character is an alphabet(a-zA-Z)*/
int is_alphabet(char c)
{
    if (c >= 'A' && c <= 'Z')
        return 1;

    if (c >= 'a' && c <= 'z')
        return 1;

    return 0;       
}

/*
str1: string in which the number of words have to be counted
Return value: number of words in the string
*/
int count_words(char *str1) 
{
    int num_words, pos;
    char cur_char, is_prev_char_alphabet;

    if (!str1)
        return 0;

    num_words = 0;
    pos = 0;
    cur_char = str1[pos];
    is_prev_char_alphabet = 0;
    while (cur_char != '\0') {
        int is_cur_char_alphabet = is_alphabet(cur_char);

        /*If previous character is not an alphabet and current character
        is an alphabet then we have found a new word*/
        if (!is_prev_char_alphabet && is_cur_char_alphabet) {
            ++num_words;
        }

        is_prev_char_alphabet = is_cur_char_alphabet;
        
        pos++;
        cur_char = str1[pos];       
    }

    return num_words;
}


void test(char *str1, int expected_result)
{
    int result;

    result = count_words(str1);

    if (result != expected_result)
        handle_error();

    printf("Word count = %d, for string: %s\n", result, str1);
}


int main()
{
    int expected_word_count;

    expected_word_count = 1;
    test("hello", expected_word_count);

    expected_word_count = 0;
    test("", expected_word_count);
    

    expected_word_count = 5;
    test("   hello,how are    you doing?", expected_word_count);

    printf("Test passed\n");
    return 0;
}

